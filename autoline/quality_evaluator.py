"""
Description :   Quality Evaluation Layer (Layer 3)
                - Diversity Evaluator (4-dimension)
                - Semantic Coverage Calculator
                - Test Case Quality Scorer
Author      :   CGA Enhancement Project
Time        :   2026/03/16
"""

import re
import logging
import hashlib
import json
from typing import List, Dict, Optional, Any, Tuple, Set
from dataclasses import dataclass, field
from enum import Enum
from collections import defaultdict

logger = logging.getLogger(__name__)


# ============================================================================
# 配置常量
# ============================================================================

class QualityConfig:
    """质量评估配置"""
    
    # 多样性评估权重
    SEQUENCE_DIVERSITY_WEIGHT = 0.30      # 输入序列多样性权重
    SEMANTIC_VECTOR_WEIGHT = 0.25         # 语义向量多样性权重
    EXECUTION_PATH_WEIGHT = 0.25          # 执行路径多样性权重
    FUNCTION_COVERAGE_WEIGHT = 0.20       # 功能覆盖多样性权重
    
    # 多样性阈值
    MIN_DIVERSITY_THRESHOLD = 0.1         # 最低多样性阈值
    HIGH_DIVERSITY_THRESHOLD = 0.7        # 高多样性阈值
    
    # 语义覆盖率阈值
    SEMANTIC_COVERAGE_TARGET = 0.85       # 目标语义覆盖率
    
    # 编辑距离配置
    MIN_EDIT_DISTANCE = 3                 # 最小编辑距离要求
    
    # 相似度阈值
    SIMILARITY_THRESHOLD = 0.8            # 相似度阈值（超过此值认为相似）


# ============================================================================
# 数据结构定义
# ============================================================================

class DiversityDimension(Enum):
    """多样性维度枚举"""
    SEQUENCE = "sequence"           # 输入序列多样性
    SEMANTIC_VECTOR = "semantic"    # 语义向量多样性
    EXECUTION_PATH = "path"         # 执行路径多样性
    FUNCTION_COVERAGE = "function"  # 功能覆盖多样性


@dataclass
class DiversityScore:
    """
    多样性评分
    
    Attributes:
        sequence_diversity: 输入序列多样性得分
        semantic_diversity: 语义向量多样性得分
        path_diversity: 执行路径多样性得分
        function_diversity: 功能覆盖多样性得分
        overall_score: 综合多样性得分
        details: 详细信息
    """
    sequence_diversity: float = 0.0
    semantic_diversity: float = 0.0
    path_diversity: float = 0.0
    function_diversity: float = 0.0
    overall_score: float = 0.0
    details: Dict[str, Any] = field(default_factory=dict)
    
    def calculate_overall(self) -> float:
        """计算综合多样性得分"""
        self.overall_score = (
            QualityConfig.SEQUENCE_DIVERSITY_WEIGHT * self.sequence_diversity +
            QualityConfig.SEMANTIC_VECTOR_WEIGHT * self.semantic_diversity +
            QualityConfig.EXECUTION_PATH_WEIGHT * self.path_diversity +
            QualityConfig.FUNCTION_COVERAGE_WEIGHT * self.function_diversity
        )
        return self.overall_score
    
    def to_dict(self) -> Dict[str, Any]:
        """转换为字典"""
        return {
            'sequence_diversity': round(self.sequence_diversity, 4),
            'semantic_diversity': round(self.semantic_diversity, 4),
            'path_diversity': round(self.path_diversity, 4),
            'function_diversity': round(self.function_diversity, 4),
            'overall_score': round(self.overall_score, 4),
            'details': self.details
        }


@dataclass
class SemanticCoverageResult:
    """
    语义覆盖率结果
    
    Attributes:
        total_function_points: 总功能点数
        covered_function_points: 已覆盖功能点数
        semantic_coverage: 语义覆盖率
        coverage_by_type: 按类型统计的覆盖率
        uncovered_important: 未覆盖的高重要性功能点
    """
    total_function_points: int = 0
    covered_function_points: int = 0
    semantic_coverage: float = 0.0
    coverage_by_type: Dict[str, float] = field(default_factory=dict)
    uncovered_important: List[Dict[str, Any]] = field(default_factory=list)
    
    def to_dict(self) -> Dict[str, Any]:
        """转换为字典"""
        return {
            'total_function_points': self.total_function_points,
            'covered_function_points': self.covered_function_points,
            'semantic_coverage': round(self.semantic_coverage, 4),
            'coverage_by_type': self.coverage_by_type,
            'uncovered_important': self.uncovered_important
        }


@dataclass
class FunctionCoverageState:
    """
    功能点覆盖状态
    
    Attributes:
        name: 功能点名称
        fp_type: 功能点类型
        importance: 重要性评分
        covered: 是否已覆盖
        covered_by: 覆盖该功能点的测试用例ID列表
        last_check_iteration: 最后检查的迭代次数
    """
    name: str
    fp_type: str
    importance: float
    covered: bool = False
    covered_by: List[str] = field(default_factory=list)
    last_check_iteration: int = 0


# ============================================================================
# 编辑距离计算器
# ============================================================================

class EditDistanceCalculator:
    """编辑距离计算器"""
    
    @staticmethod
    def levenshtein_distance(s1: str, s2: str) -> int:
        """
        计算Levenshtein编辑距离
        
        Args:
            s1: 字符串1
            s2: 字符串2
            
        Returns:
            编辑距离
        """
        if len(s1) < len(s2):
            return EditDistanceCalculator.levenshtein_distance(s2, s1)
        
        if len(s2) == 0:
            return len(s1)
        
        previous_row = range(len(s2) + 1)
        for i, c1 in enumerate(s1):
            current_row = [i + 1]
            for j, c2 in enumerate(s2):
                # 插入、删除、替换
                insertions = previous_row[j + 1] + 1
                deletions = current_row[j] + 1
                substitutions = previous_row[j] + (c1 != c2)
                current_row.append(min(insertions, deletions, substitutions))
            previous_row = current_row
        
        return previous_row[-1]
    
    @staticmethod
    def normalized_distance(s1: str, s2: str) -> float:
        """
        计算归一化的编辑距离 (0-1范围)
        
        Args:
            s1: 字符串1
            s2: 字符串2
            
        Returns:
            归一化编辑距离 (0表示相同，1表示完全不同)
        """
        if not s1 and not s2:
            return 0.0
        max_len = max(len(s1), len(s2))
        if max_len == 0:
            return 0.0
        distance = EditDistanceCalculator.levenshtein_distance(s1, s2)
        return distance / max_len
    
    @staticmethod
    def similarity(s1: str, s2: str) -> float:
        """
        计算相似度 (1 - 归一化编辑距离)
        
        Args:
            s1: 字符串1
            s2: 字符串2
            
        Returns:
            相似度 (1表示相同，0表示完全不同)
        """
        return 1.0 - EditDistanceCalculator.normalized_distance(s1, s2)


# ============================================================================
# 序列特征提取器
# ============================================================================

class SequenceFeatureExtractor:
    """序列特征提取器"""
    
    @staticmethod
    def extract_features(code: str) -> Dict[str, Any]:
        """
        从代码中提取序列特征
        
        Args:
            code: 测试代码
            
        Returns:
            特征字典
        """
        features = {
            'signal_assignments': [],      # 信号赋值序列
            'delay_patterns': [],          # 延时模式
            'control_structures': [],      # 控制结构
            'signal_values': {},           # 信号值映射
            'operation_sequence': [],      # 操作序列
            'code_hash': ''                # 代码哈希
        }
        
        # 提取信号赋值
        assign_pattern = r'(\w+)\s*=\s*([^;]+);'
        for match in re.finditer(assign_pattern, code):
            signal = match.group(1)
            value = match.group(2).strip()
            features['signal_assignments'].append((signal, value))
            if signal not in features['signal_values']:
                features['signal_values'][signal] = []
            features['signal_values'][signal].append(value)
        
        # 提取延时模式
        delay_pattern = r'#(\d+)'
        delays = [int(d) for d in re.findall(delay_pattern, code)]
        features['delay_patterns'] = delays
        
        # 提取repeat循环
        repeat_pattern = r'repeat\s*\(\s*(\d+)\s*\)'
        repeats = [int(r) for r in re.findall(repeat_pattern, code)]
        features['control_structures'].extend([('repeat', r) for r in repeats])
        
        # 提取posedge/negedge
        edge_pattern = r'@(?:posedge|negedge)\s+(\w+)'
        edges = re.findall(edge_pattern, code)
        features['control_structures'].extend([('edge', e) for e in edges])
        
        # 构建操作序列
        all_operations = []
        
        # 按位置排序的所有操作
        for match in re.finditer(r'((?:\w+\s*=\s*[^;]+;)|(?:#\d+;)|(?:repeat\s*\(\d+\)[^;]+;)|(?:@\([^)]+\)))', code):
            all_operations.append(match.group(1).strip())
        
        features['operation_sequence'] = all_operations
        
        # 计算代码哈希
        normalized_code = re.sub(r'\s+', ' ', code).strip()
        features['code_hash'] = hashlib.md5(normalized_code.encode()).hexdigest()[:16]
        
        return features
    
    @staticmethod
    def extract_signal_sequence(code: str, signals: List[str] = None) -> List[Tuple[str, str, str]]:
        """
        提取信号赋值序列
        
        Args:
            code: 测试代码
            signals: 关注的信号列表（可选）
            
        Returns:
            (信号名, 值, 上下文) 元组列表
        """
        sequences = []
        
        # 按行处理，保持上下文
        lines = code.split('\n')
        context = ""
        
        for line in lines:
            stripped = line.strip()
            
            # 更新上下文
            if stripped.startswith('//'):
                context = stripped
                continue
            
            # 提取赋值
            assign_match = re.match(r'(\w+)\s*=\s*([^;]+);', stripped)
            if assign_match:
                signal = assign_match.group(1)
                value = assign_match.group(2).strip()
                
                # 如果指定了信号列表，只提取关注的信号
                if signals is None or signal in signals:
                    sequences.append((signal, value, context))
        
        return sequences


# ============================================================================
# 多样性评估器
# ============================================================================

class DiversityEvaluator:
    """
    多样性评估器
    
    四维度多样性评估：
    1. 输入序列多样性：计算与已有序列的编辑距离
    2. 语义向量多样性：计算代码特征向量的相似度
    3. 执行路径多样性：计算新覆盖代码行的比例
    4. 功能覆盖多样性：计算新覆盖功能点的比例
    """
    
    def __init__(self):
        """初始化多样性评估器"""
        self.history: List[Dict[str, Any]] = []
        self.feature_extractor = SequenceFeatureExtractor()
        self.edit_distance_calc = EditDistanceCalculator()
        
    def add_to_history(self, 
                       code: str, 
                       covered_lines: Set[int] = None,
                       covered_functions: List[str] = None,
                       test_id: str = ""):
        """
        添加测试用例到历史记录
        
        Args:
            code: 测试代码
            covered_lines: 覆盖的代码行
            covered_functions: 覆盖的功能点列表
            test_id: 测试用例ID
        """
        features = self.feature_extractor.extract_features(code)
        
        record = {
            'test_id': test_id,
            'code': code,
            'features': features,
            'covered_lines': covered_lines or set(),
            'covered_functions': covered_functions or [],
            'code_hash': features['code_hash']
        }
        
        self.history.append(record)
    
    def evaluate(self, 
                 new_code: str,
                 new_covered_lines: Set[int] = None,
                 new_covered_functions: List[str] = None) -> DiversityScore:
        """
        评估新测试用例的多样性
        
        Args:
            new_code: 新测试代码
            new_covered_lines: 新覆盖的代码行
            new_covered_functions: 新覆盖的功能点列表
            
        Returns:
            多样性评分
        """
        score = DiversityScore()
        
        if not self.history:
            # 第一个测试用例，给予最高多样性
            score.sequence_diversity = 1.0
            score.semantic_diversity = 1.0
            score.path_diversity = 1.0
            score.function_diversity = 1.0
            score.calculate_overall()
            score.details = {'reason': 'first_test_case'}
            return score
        
        # 提取新代码特征
        new_features = self.feature_extractor.extract_features(new_code)
        new_covered_lines = new_covered_lines or set()
        new_covered_functions = new_covered_functions or []
        
        # 1. 计算输入序列多样性
        score.sequence_diversity = self._evaluate_sequence_diversity(new_code, new_features)
        
        # 2. 计算语义向量多样性
        score.semantic_diversity = self._evaluate_semantic_diversity(new_features)
        
        # 3. 计算执行路径多样性
        score.path_diversity = self._evaluate_path_diversity(new_covered_lines)
        
        # 4. 计算功能覆盖多样性
        score.function_diversity = self._evaluate_function_diversity(new_covered_functions)
        
        # 计算综合得分
        score.calculate_overall()
        
        # 添加详细信息
        score.details = {
            'history_size': len(self.history),
            'new_code_hash': new_features['code_hash'],
            'signal_count': len(new_features['signal_values']),
            'operation_count': len(new_features['operation_sequence'])
        }
        
        return score
    
    def _evaluate_sequence_diversity(self, new_code: str, new_features: Dict) -> float:
        """评估输入序列多样性"""
        if not self.history:
            return 1.0
        
        # 提取操作序列
        new_ops = new_features['operation_sequence']
        
        # 计算与历史中所有测试的最小相似度（即最大差异）
        max_distance = 0.0
        
        for record in self.history[-10:]:  # 只比较最近10个
            hist_ops = record['features']['operation_sequence']
            
            # 将操作序列转换为字符串计算编辑距离
            new_ops_str = ' '.join(new_ops)
            hist_ops_str = ' '.join(hist_ops)
            
            similarity = self.edit_distance_calc.similarity(new_ops_str, hist_ops_str)
            distance = 1.0 - similarity
            max_distance = max(max_distance, distance)
        
        return max_distance
    
    def _evaluate_semantic_diversity(self, new_features: Dict) -> float:
        """评估语义向量多样性"""
        if not self.history:
            return 1.0
        
        # 构建特征向量
        new_vector = self._build_feature_vector(new_features)
        
        # 计算与历史特征向量的最小相似度
        max_distance = 0.0
        
        for record in self.history[-10:]:
            hist_vector = self._build_feature_vector(record['features'])
            similarity = self._cosine_similarity(new_vector, hist_vector)
            distance = 1.0 - similarity
            max_distance = max(max_distance, distance)
        
        return max_distance
    
    def _evaluate_path_diversity(self, new_covered_lines: Set[int]) -> float:
        """评估执行路径多样性"""
        if not self.history:
            return 1.0
        
        if not new_covered_lines:
            return 0.0
        
        # 计算历史覆盖的并集
        all_covered = set()
        for record in self.history:
            all_covered.update(record['covered_lines'])
        
        # 计算新覆盖的行
        new_lines = new_covered_lines - all_covered
        
        if not new_covered_lines:
            return 0.0
        
        # 新覆盖比例
        novelty_ratio = len(new_lines) / len(new_covered_lines)
        return novelty_ratio
    
    def _evaluate_function_diversity(self, new_covered_functions: List[str]) -> float:
        """评估功能覆盖多样性"""
        if not self.history:
            return 1.0
        
        if not new_covered_functions:
            return 0.0
        
        # 计算历史覆盖的功能点并集
        all_covered = set()
        for record in self.history:
            all_covered.update(record['covered_functions'])
        
        # 计算新覆盖的功能点
        new_functions = set(new_covered_functions) - all_covered
        
        if not new_covered_functions:
            return 0.0
        
        # 新覆盖比例
        novelty_ratio = len(new_functions) / len(new_covered_functions)
        return novelty_ratio
    
    def _build_feature_vector(self, features: Dict) -> Dict[str, float]:
        """构建特征向量"""
        vector = {}
        
        # 信号数量
        vector['signal_count'] = len(features['signal_values'])
        
        # 操作数量
        vector['operation_count'] = len(features['operation_sequence'])
        
        # 延时数量
        vector['delay_count'] = len(features['delay_patterns'])
        
        # 延时总和
        vector['delay_sum'] = sum(features['delay_patterns'])
        
        # 控制结构数量
        vector['control_count'] = len(features['control_structures'])
        
        # repeat循环数量
        repeat_count = sum(1 for c in features['control_structures'] if c[0] == 'repeat')
        vector['repeat_count'] = repeat_count
        
        # 边沿等待数量
        edge_count = sum(1 for c in features['control_structures'] if c[0] == 'edge')
        vector['edge_count'] = edge_count
        
        # 赋值数量
        vector['assignment_count'] = len(features['signal_assignments'])
        
        return vector
    
    def _cosine_similarity(self, v1: Dict[str, float], v2: Dict[str, float]) -> float:
        """计算余弦相似度"""
        # 获取所有键
        all_keys = set(v1.keys()) | set(v2.keys())
        
        if not all_keys:
            return 0.0
        
        # 计算点积和模
        dot_product = 0.0
        norm1 = 0.0
        norm2 = 0.0
        
        for key in all_keys:
            val1 = v1.get(key, 0.0)
            val2 = v2.get(key, 0.0)
            dot_product += val1 * val2
            norm1 += val1 * val1
            norm2 += val2 * val2
        
        if norm1 == 0 or norm2 == 0:
            return 0.0
        
        return dot_product / (norm1 ** 0.5 * norm2 ** 0.5)
    
    def get_diversity_statistics(self) -> Dict[str, Any]:
        """获取多样性统计信息"""
        # if not self.history:
        #     return {
        #         'total_tests': 0,
        #         'unique_hashes': 0,
        #         'avg_diversity': 0.0
        #     }
        if not self.history:
            return {
            'total_tests': 0,
            'unique_hashes': 0,
            'avg_diversity': 0.0,
            'duplicate_ratio': 0.0  # ✅ 添加缺失的键
            }
        
        unique_hashes = len(set(r['code_hash'] for r in self.history))
        
        return {
            'total_tests': len(self.history),
            'unique_hashes': unique_hashes,
            'duplicate_ratio': 1.0 - (unique_hashes / len(self.history)) if self.history else 0.0
        }


# ============================================================================
# 语义覆盖率计算器
# ============================================================================

class SemanticCoverageCalculator:
    """
    语义覆盖率计算器
    
    计算基于功能点重要性的语义覆盖率：
    语义覆盖率 = Σ(已覆盖功能点重要性) / Σ(所有功能点重要性)
    """
    
    def __init__(self, function_points: List[Dict[str, Any]] = None):
        """
        初始化语义覆盖率计算器
        
        Args:
            function_points: 功能点列表
        """
        self.function_points: Dict[str, FunctionCoverageState] = {}
        self.total_importance = 0.0
        self.covered_importance = 0.0
        
        if function_points:
            self.initialize(function_points)
    
    def initialize(self, function_points: List[Dict[str, Any]]) -> Dict[str, Any]:
        """
        初始化功能点覆盖状态
        
        Args:
            function_points: 功能点列表
            
        Returns:
            初始化结果
        """
        self.function_points.clear()
        self.total_importance = 0.0
        self.covered_importance = 0.0
        
        for fp in function_points:
            name = fp.get('name', '')
            fp_type = fp.get('type', 'unknown')
            importance = fp.get('importance', 0.0)
            
            self.function_points[name] = FunctionCoverageState(
                name=name,
                fp_type=fp_type,
                importance=importance,
                covered=False,
                covered_by=[],
                last_check_iteration=0
            )
            
            self.total_importance += importance
        
        return {
            'total_function_points': len(self.function_points),
            'total_importance': self.total_importance
        }
    
    def update_coverage(self, 
                        covered_lines: Set[int] = None,
                        covered_functions: List[str] = None,
                        test_id: str = "",
                        iteration: int = 0) -> SemanticCoverageResult:
        """
        更新功能点覆盖状态
        
        Args:
            covered_lines: 覆盖的代码行
            covered_functions: 覆盖的功能点名称列表
            test_id: 测试用例ID
            iteration: 当前迭代次数
            
        Returns:
            语义覆盖率结果
        """
        # 更新覆盖状态
        if covered_functions:
            for func_name in covered_functions:
                if func_name in self.function_points:
                    fp = self.function_points[func_name]
                    if not fp.covered:
                        fp.covered = True
                        fp.covered_by.append(test_id)
                        fp.last_check_iteration = iteration
                        self.covered_importance += fp.importance
        
        return self.calculate_coverage()
    
    def calculate_coverage(self) -> SemanticCoverageResult:
        """
        计算当前语义覆盖率
        
        Returns:
            语义覆盖率结果
        """
        result = SemanticCoverageResult()
        
        result.total_function_points = len(self.function_points)
        result.covered_function_points = sum(1 for fp in self.function_points.values() if fp.covered)
        
        # 计算语义覆盖率
        if self.total_importance > 0:
            result.semantic_coverage = self.covered_importance / self.total_importance
        
        # 按类型统计
        type_stats = defaultdict(lambda: {'total': 0, 'covered': 0, 'importance': 0.0, 'covered_importance': 0.0})
        
        for fp in self.function_points.values():
            type_stats[fp.fp_type]['total'] += 1
            type_stats[fp.fp_type]['importance'] += fp.importance
            if fp.covered:
                type_stats[fp.fp_type]['covered'] += 1
                type_stats[fp.fp_type]['covered_importance'] += fp.importance
        
        for fp_type, stats in type_stats.items():
            if stats['importance'] > 0:
                result.coverage_by_type[fp_type] = stats['covered_importance'] / stats['importance']
            else:
                result.coverage_by_type[fp_type] = 0.0
        
        # 找出未覆盖的高重要性功能点
        uncovered_important = [
            {
                'name': fp.name,
                'type': fp.fp_type,
                'importance': fp.importance
            }
            for fp in self.function_points.values()
            if not fp.covered and fp.importance >= 0.5
        ]
        uncovered_important.sort(key=lambda x: x['importance'], reverse=True)
        result.uncovered_important = uncovered_important[:5]  # 只返回前5个
        
        return result
    
    def get_function_point_status(self, name: str) -> Optional[FunctionCoverageState]:
        """获取指定功能点的覆盖状态"""
        return self.function_points.get(name)
    
    def get_uncovered_function_points(self, 
                                      min_importance: float = 0.0,
                                      fp_type: str = None) -> List[FunctionCoverageState]:
        """
        获取未覆盖的功能点
        
        Args:
            min_importance: 最小重要性阈值
            fp_type: 功能点类型过滤（可选）
            
        Returns:
            未覆盖的功能点列表
        """
        uncovered = []
        
        for fp in self.function_points.values():
            if fp.covered:
                continue
            if fp.importance < min_importance:
                continue
            if fp_type and fp.fp_type != fp_type:
                continue
            uncovered.append(fp)
        
        # 按重要性排序
        uncovered.sort(key=lambda x: x.importance, reverse=True)
        return uncovered
    
    def get_coverage_report(self) -> str:
        """生成覆盖率报告"""
        result = self.calculate_coverage()
        
        lines = []
        lines.append("=" * 60)
        lines.append("SEMANTIC COVERAGE REPORT")
        lines.append("=" * 60)
        lines.append("")
        lines.append(f"Total Function Points: {result.total_function_points}")
        lines.append(f"Covered Function Points: {result.covered_function_points}")
        lines.append(f"Semantic Coverage: {result.semantic_coverage:.2%}")
        lines.append("")
        lines.append("Coverage by Type:")
        for fp_type, coverage in result.coverage_by_type.items():
            lines.append(f"  - {fp_type}: {coverage:.2%}")
        lines.append("")
        
        if result.uncovered_important:
            lines.append("Uncovered High-Importance Function Points:")
            for fp in result.uncovered_important:
                lines.append(f"  - {fp['name']} ({fp['type']}): importance={fp['importance']:.2f}")
        
        lines.append("")
        lines.append("=" * 60)
        
        return "\n".join(lines)
    
    def to_dict(self) -> Dict[str, Any]:
        """转换为字典"""
        return {
            'total_importance': self.total_importance,
            'covered_importance': self.covered_importance,
            'function_points': {
                name: {
                    'type': fp.fp_type,
                    'importance': fp.importance,
                    'covered': fp.covered,
                    'covered_by': fp.covered_by
                }
                for name, fp in self.function_points.items()
            }
        }


# ============================================================================
# 质量评估器（主入口）
# ============================================================================

class QualityEvaluator:
    """
    质量评估器 - 第3层主入口
    
    整合多样性评估和语义覆盖率计算，提供统一的质量评估接口
    """
    
    def __init__(self, function_points: List[Dict[str, Any]] = None):
        """
        初始化质量评估器
        
        Args:
            function_points: 功能点列表
        """
        self.diversity_evaluator = DiversityEvaluator()
        self.semantic_coverage = SemanticCoverageCalculator(function_points)
        self.evaluation_history: List[Dict[str, Any]] = []
    
    def initialize(self, function_points: List[Dict[str, Any]]) -> Dict[str, Any]:
        """
        初始化质量评估器
        
        Args:
            function_points: 功能点列表
            
        Returns:
            初始化结果
        """
        result = self.semantic_coverage.initialize(function_points)
        self.evaluation_history.clear()
        return result
    
    def evaluate_test_case(self,
                          code: str,
                          covered_lines: Set[int] = None,
                          covered_functions: List[str] = None,
                          test_id: str = "",
                          iteration: int = 0) -> Dict[str, Any]:
        """
        评估测试用例质量
        
        Args:
            code: 测试代码
            covered_lines: 覆盖的代码行
            covered_functions: 覆盖的功能点列表
            test_id: 测试用例ID
            iteration: 当前迭代次数
            
        Returns:
            评估结果字典
        """
        # 1. 多样性评估
        diversity_score = self.diversity_evaluator.evaluate(
            new_code=code,
            new_covered_lines=covered_lines,
            new_covered_functions=covered_functions
        )
        
        # 2. 更新语义覆盖率
        coverage_result = self.semantic_coverage.update_coverage(
            covered_lines=covered_lines,
            covered_functions=covered_functions,
            test_id=test_id,
            iteration=iteration
        )
        
        # 3. 计算质量得分
        quality_score = self._calculate_quality_score(diversity_score, coverage_result)
        
        # 4. 记录评估历史
        evaluation_result = {
            'test_id': test_id,
            'iteration': iteration,
            'diversity': diversity_score.to_dict(),
            'coverage': coverage_result.to_dict(),
            'quality_score': quality_score
        }
        self.evaluation_history.append(evaluation_result)
        
        # 5. 添加到多样性历史
        self.diversity_evaluator.add_to_history(
            code=code,
            covered_lines=covered_lines,
            covered_functions=covered_functions,
            test_id=test_id
        )
        
        return evaluation_result
    
    def _calculate_quality_score(self, 
                                 diversity: DiversityScore,
                                 coverage: SemanticCoverageResult) -> float:
        """
        计算综合质量得分
        
        Args:
            diversity: 多样性评分
            coverage: 语义覆盖率结果
            
        Returns:
            质量得分 (0-1)
        """
        # 多样性权重
        diversity_weight = 0.4
        
        # 覆盖率增量权重
        coverage_weight = 0.6
        
        # 综合得分
        score = (
            diversity_weight * diversity.overall_score +
            coverage_weight * coverage.semantic_coverage
        )
        
        return min(1.0, max(0.0, score))
    
    def should_accept(self, 
                      evaluation_result: Dict[str, Any],
                      min_diversity: float = QualityConfig.MIN_DIVERSITY_THRESHOLD) -> Tuple[bool, str]:
        """
        判断是否应该接受该测试用例
        
        Args:
            evaluation_result: 评估结果
            min_diversity: 最低多样性阈值
            
        Returns:
            (是否接受, 原因)
        """
        diversity = evaluation_result.get('diversity', {})
        overall_diversity = diversity.get('overall_score', 0.0)
        
        if overall_diversity < min_diversity:
            return False, f"Diversity too low: {overall_diversity:.2f} < {min_diversity}"
        
        return True, "Passed quality check"
    
    def get_statistics(self) -> Dict[str, Any]:
        """获取统计信息"""
        diversity_stats = self.diversity_evaluator.get_diversity_statistics()
        coverage_result = self.semantic_coverage.calculate_coverage()
        
        return {
            'diversity': diversity_stats,
            'coverage': coverage_result.to_dict(),
            'total_evaluations': len(self.evaluation_history)
        }
    
    def generate_report(self) -> str:
        """生成完整报告"""
        lines = []
        lines.append("=" * 70)
        lines.append("QUALITY EVALUATION REPORT - LAYER 3")
        lines.append("=" * 70)
        lines.append("")
        
        # 多样性统计
        stats = self.get_statistics()
        lines.append("[DIVERSITY STATISTICS]")
        lines.append(f"Total Tests: {stats['diversity']['total_tests']}")
        lines.append(f"Unique Tests: {stats['diversity']['unique_hashes']}")
        lines.append(f"Duplicate Ratio: {stats['diversity']['duplicate_ratio']:.2%}")
        lines.append("")
        
        # 语义覆盖率
        lines.append("[SEMANTIC COVERAGE]")
        lines.append(self.semantic_coverage.get_coverage_report())
        lines.append("")
        
        # 质量趋势
        if self.evaluation_history:
            lines.append("[QUALITY TREND]")
            avg_quality = sum(e['quality_score'] for e in self.evaluation_history) / len(self.evaluation_history)
            avg_diversity = sum(e['diversity']['overall_score'] for e in self.evaluation_history) / len(self.evaluation_history)
            lines.append(f"Average Quality Score: {avg_quality:.2f}")
            lines.append(f"Average Diversity Score: {avg_diversity:.2f}")
            lines.append("")
        
        lines.append("=" * 70)
        
        return "\n".join(lines)


# ============================================================================
# 便捷函数
# ============================================================================

def create_quality_evaluator(function_points: List[Dict[str, Any]] = None) -> QualityEvaluator:
    """
    创建质量评估器
    
    Args:
        function_points: 功能点列表
        
    Returns:
        初始化完成的质量评估器
    """
    return QualityEvaluator(function_points=function_points)


def evaluate_diversity(code1: str, code2: str) -> float:
    """
    快速评估两个代码的多样性
    
    Args:
        code1: 代码1
        code2: 代码2
        
    Returns:
        多样性得分 (0-1, 1表示完全不同)
    """
    calc = EditDistanceCalculator()
    return calc.normalized_distance(code1, code2)