"""
Description :   Diversity Constraint Injector (Layer 1)
                - Analyze existing test sequences
                - Detect overused patterns
                - Generate diversity constraints for Prompt
                - Recommend new test scenarios
Author      :   CGA Enhancement Project
Time        :   2026/03/16
"""

import logging
import re
from typing import List, Dict, Optional, Any, Tuple, Set
from dataclasses import dataclass, field
from enum import Enum

# 支持两种导入方式：包导入和直接加载
try:
    from .test_history import (
        TestHistoryManager, 
        TestRecord, 
        InputSequence, 
        SequencePattern
    )

except ImportError:
    from test_history import (
        TestHistoryManager, 
        TestRecord, 
        InputSequence, 
        SequencePattern
    )

logger = logging.getLogger(__name__)


# ============================================================================
# 配置常量
# ============================================================================

class DiversityConfig:
    """多样性约束配置"""
    
    # 编辑距离阈值
    MIN_EDIT_DISTANCE = 3
    
    # 模式过度使用阈值
    OVERUSE_THRESHOLD = 3
    
    # 新场景推荐数量
    NEW_SCENARIO_COUNT = 3
    
    # 序列长度限制（用于约束生成）
    MAX_SEQUENCE_LENGTH = 10
    
    # 多样性得分权重
    PATTERN_WEIGHT = 0.4
    EDIT_DISTANCE_WEIGHT = 0.3
    COVERAGE_WEIGHT = 0.3


# ============================================================================
# 约束类型定义
# ============================================================================

class ConstraintType(Enum):
    """约束类型枚举"""
    FORBID_SEQUENCE = "forbid_sequence"       # 禁止特定序列
    MIN_EDIT_DISTANCE = "min_edit_distance"   # 最小编辑距离
    AVOID_PATTERN = "avoid_pattern"           # 革免模式
    TRY_SCENARIO = "try_scenario"             # 尝试新场景
    EXPLORE_RANGE = "explore_range"           # 探索范围


# ============================================================================
# 约束数据结构
# ============================================================================

@dataclass
class DiversityConstraint:
    """
    多样性约束
    
    Attributes:
        constraint_type: 约束类型
        description: 约束描述
        details: 详细信息
        priority: 优先级 (1-5, 5最高)
    """
    constraint_type: ConstraintType
    description: str
    details: Dict[str, Any] = field(default_factory=dict)
    priority: int = 3
    
    def to_prompt_text(self) -> str:
        """转换为Prompt文本"""
        if self.constraint_type == ConstraintType.FORBID_SEQUENCE:
            return f"- AVOID using this sequence pattern: {self.details.get('pattern', 'unknown')}"
        
        elif self.constraint_type == ConstraintType.MIN_EDIT_DISTANCE:
            return f"- Your test sequence MUST differ from previous tests (edit distance >= {self.details.get('min_distance', 3)})"
        
        elif self.constraint_type == ConstraintType.AVOID_PATTERN:
            signal = self.details.get('signal', '')
            pattern = self.details.get('pattern', '')
            return f"- AVOID the pattern '{pattern}' for signal '{signal}' (already used {self.details.get('count', 0)} times)"
        
        elif self.constraint_type == ConstraintType.TRY_SCENARIO:
            return f"- TRY this new approach: {self.details.get('scenario', 'unknown')}"
        
        elif self.constraint_type == ConstraintType.EXPLORE_RANGE:
            return f"- EXPLORE values in range [{self.details.get('min', 0)}, {self.details.get('max', 255)}] for {self.details.get('signal', 'signal')}"
        
        return f"- {self.description}"
# ============================================================================
# 序列分析器
# ============================================================================

class SequenceAnalyzer:
    """
    序列分析器
    
    分析输入序列的特征和模式
    """
    
    @staticmethod
    def extract_value_range(values: List[Tuple[int, Any]]) -> Tuple[Any, Any]:
        """提取值范围"""
        if not values:
            return (0, 0)
        
        numeric_values = []
        for _, v in values:
            # 尝试转换为数值
            if isinstance(v, (int, float)):
                numeric_values.append(v)
            elif isinstance(v, str):
                # 处理 '0, '1, 'x 等
                if v in ['0', '1', 'x', 'z']:
                    numeric_values.append(int(v) if v.isdigit() else 0)
                # 处理带位宽的值
                match = re.match(r"(\d+)'[bdh]([0-9a-fA-fA-FxXzZ_]+)", v)
                if match:
                    try:
                        numeric_values.append(int(match.group(2), 16))
                    except:
                        pass
        
        if numeric_values:
            return (min(numeric_values), max(numeric_values))
        return (0, 0)
    
    @staticmethod
    def detect_transition_pattern(values: List[Tuple[int, Any]]) -> str:
        """检测转换模式"""
        if len(values) < 2:
            return "single"
        
        # 提取值序列
        val_seq = [v for _, v in values]
        
        # 检测递增
        if all(str(val_seq[i]) <= str(val_seq[i+1]) for i in range(len(val_seq)-1)):
            return "incremental"
        
        # 检测递减
        if all(str(val_seq[i]) >= str(val_seq[i+1]) for i in range(len(val_seq)-1)):
            return "decremental"
        
        # 检测交替
        if len(val_seq) >= 4:
            if val_seq[0] == val_seq[2] and val_seq[1] == val_seq[3]:
                return "alternating"
        
        # 检测脉冲（单个变化后恢复）
        if len(val_seq) == 3 and val_seq[0] == val_seq[2] != val_seq[1]:
            return "pulse"
        
        return "random"
    
    @staticmethod
    def calculate_sequence_length(code: str) -> int:
        """计算代码中的操作序列长度"""
        # 统计赋值语句数量
        assignments = len(re.findall(r'\w+\s*=\s*\S+\s*;', code))
        # 统计repeat语句
        repeats = re.findall(r'repeat\s*\(\s*(\d+)\s*\)', code)
        repeat_cycles = sum(int(r) for r in repeats)
        
        return assignments + repeat_cycles


# ============================================================================
# 场景推荐器
# ============================================================================

class ScenarioRecommender:
    """
    场景推荐器
    
    根据历史记录和未覆盖功能点推荐新测试场景
    """
    
    # 场景模板
    SCENARIO_TEMPLATES = {
        'fsm': [
            "Test state transition from {state_a} to {state_b}",
            "Test illegal state transition handling",
            "Test state machine reset behavior",
            "Test state holding under stable inputs"
        ],
        'counter': [
            "Test counter overflow behavior (count to max value)",
            "Test counter underflow (if applicable)",
            "Test counter reset during counting",
            "Test counter enable/disable control"
        ],
        'branch': [
            "Test boundary condition: {condition} at threshold",
            "Test all branches of nested if-else",
            "Test case statement with all possible values"
        ],
        'protocol': [
            "Test handshake timeout scenario",
            "Test back-to-back transactions",
            "Test protocol violation handling"
        ],
        'general': [
            "Apply random input patterns for extended duration",
            "Test with boundary values (all 0s, all 1s)",
            "Test rapid signal transitions",
            "Test power-on/reset sequence variations"
        ]
    }
    
    def __init__(self, history_manager: TestHistoryManager):
        self.history = history_manager
    
    def recommend_scenarios(self, 
                           uncovered_functions: List[Dict],
                           covered_patterns: Set[str] = None) -> List[str]:
        """
        推荐新的测试场景
        
        Args:
            uncovered_functions: 未覆盖的功能点列表
            covered_patterns: 已覆盖的模式集合
            
        Returns:
            推荐场景列表
        """
        recommendations = []
        covered_patterns = covered_patterns or set()
        
        # 基于未覆盖功能点推荐
        for func in uncovered_functions[:3]:
            func_type = func.get('type', 'general')
            func_name = func.get('name', '')
            
            templates = self.SCENARIO_TEMPLATES.get(func_type, self.SCENARIO_TEMPLATES['general'])
            
            for template in templates[:1]:  # 每个功能点取一个模板
                scenario = self._fill_template(template, func)
                if scenario not in covered_patterns:
                    recommendations.append(scenario)
        
        # 基于历史分析推荐
        if self.history.records:
            # 分析已使用的场景类型
            used_patterns = set()
            for record in self.history.records:
                for seq in record.input_sequences:
                    pattern = SequenceAnalyzer.detect_transition_pattern(seq.values)
                    used_patterns.add(pattern)
            
            # 推荐未使用的场景类型
            all_patterns = {'incremental', 'decremental', 'alternating', 'pulse', 'random'}
            unused_patterns = all_patterns - used_patterns
            
            
            if unused_patterns:
                recommendations.append(f"Try {list(unused_patterns)[0]} input pattern (different from your usual approach)")
        
        # 确保有足够的推荐
        while len(recommendations) < DiversityConfig.NEW_SCENARIO_COUNT:
            recommendations.append("Explore a completely different input sequence than before")
        
        return recommendations[:DiversityConfig.NEW_SCENARIO_COUNT]
    
    def _fill_template(self, template: str, func: Dict) -> str:
        """填充场景模板"""
        result = template
        
        # 替换占位符
        if '{state_a}' in template or '{state_b}' in template:
            states = func.get('states', ['STATE_A', 'STATE_B'])
            if len(states) >= 2:
                result = result.replace('{state_a}', states[0])
                result = result.replace('{state_b}', states[1])
        
        if '{condition}' in template:
            condition = func.get('condition', 'signal')
            result = result.replace('{condition}', condition)
        
        return result


# ============================================================================
# 约束生成器
# ============================================================================

class ConstraintGenerator:
    """
    约束生成器
    
    根据历史分析生成多样性约束
    """
    
    def __init__(self, history_manager: TestHistoryManager):
        self.history = history_manager
        self.analyzer = SequenceAnalyzer()
    
    def generate_constraints(self, 
                            target_function: str = None,
                            uncovered_functions: List[Dict] = None) -> List[DiversityConstraint]:
        """
        生成多样性约束
        
        Args:
            target_function: 当前目标功能点
            uncovered_functions: 未覆盖功能点列表
            
        Returns:
            约束列表
        """
        constraints = []
        
        if not self.history.records:
            return constraints
        
        # 1. 生成过度使用模式约束
        overused = self.history.get_overused_patterns(DiversityConfig.OVERUSE_THRESHOLD)
        for pattern in overused[:3]:  # 最多3个
            constraints.append(DiversityConstraint(
                constraint_type=ConstraintType.AVOID_PATTERN,
                description=f"Avoid overused pattern for {pattern.signal_name}",
                details={
                    'signal': pattern.signal_name,
                    'pattern': pattern.pattern,
                    'count': pattern.count
                },
                priority=5
            ))
        
        # 2. 生成编辑距离约束
        recent_count = min(5, len(self.history.records))
        if recent_count > 00:
            constraints.append(DiversityConstraint(
                constraint_type=ConstraintType.MIN_EDIT_DISTANCE,
                description="Maintain minimum edit distance from recent tests",
                details={
                    'min_distance': DiversityConfig.MIN_EDIT_DISTANCE,
                    'reference_count': recent_count
                },
                priority=4
            ))
        
        # 3. 生成值范围探索约束
        if uncovered_functions:
            for func in uncovered_functions[:2]:
                # 根据功能点类型生成范围约束
                if func.get('type') == 'counter':
                    max_val = func.get('max_value', 255)
                    constraints.append(DiversityConstraint(
                        constraint_type=ConstraintType.EXPLORE_RANGE,
                        description=f"Explore counter boundary values",
                        details={
                            'signal': func.get('name', 'counter'),
                            'min': 0,
                            'max': max_val
                        },
                        priority=3
                    ))
        
        # 按优先级排序
        constraints.sort(key=lambda c: c.priority, reverse=True)
        
        return constraints
    
    def generate_forbidden_sequence_prompt(self) -> str:
        """生成禁止序列提示"""
        overused = self.history.get_overused_patterns(DiversityConfig.OVERUSE_THRESHOLD)
        
        if not overused:
            return ""
        
        lines = ["[DIVERSITY CONSTRAINTS - AVOID THESE OVERUSED PATTERNS]"]
        
        for i, pattern in enumerate(overused[:5], 1):
            lines.append(f"{i}. Signal '{pattern.signal_name}': {pattern.pattern[:50]}")
            lines.append(f"   (This pattern has been used {pattern.count} times already)")
        
        lines.append("\nPlease create a DIFFERENT input sequence to improve test diversity.")
        
        return "\n".join(lines)


# ============================================================================
# 多样性约束注入器（主入口）
# ============================================================================

class DiversityInjector:
    """
    多样性约束注入器 - 第1层主入口
    
    整合序列分析、模式检测、约束生成，提供统一的多样性约束接口
    """
    
    def __init__(self, history_manager: TestHistoryManager = None):
        """
        Args:
            history_manager: 测试历史管理器
        """
        self.history = history_manager or TestHistoryManager()
        self.constraint_generator = ConstraintGenerator(self.history)
        self.scenario_recommender = ScenarioRecommender(self.history)
    
    def inject_diversity_constraints(self, 
                                     prompt: str,
                                     target_function: str = None,
                                     uncovered_functions: List[Dict] = None) -> str:
        """
        将多样性约束注入到Prompt中
        
        Args:
            prompt: 废始Prompt
            target_function: 当前目标功能点
            uncovered_functions: 未覆盖功能点列表
            
        Returns:
            注入约束后的Prompt
        """
        if not self.history.records:
            return prompt  # 没有历史记录时不注入
        
        # 生成约束
        constraints = self.constraint_generator.generate_constraints(
            target_function=target_function,
            uncovered_functions=uncovered_functions
        )
        
        # 生成推荐场景
        recommendations = self.scenario_recommender.recommend_scenarios(
            uncovered_functions=uncovered_functions or []
        )
        
        # 构建约束文本
        constraint_text = self._build_constraint_section(constraints, recommendations)
        
        # 找到插入点（在 [OUTPUT REQUIREMENTS] 之前插入）
        insert_marker = "[OUTPUT REQUIREMENTS"
        if insert_marker in prompt:
            parts = prompt.split(insert_marker, 1)
            enhanced_prompt = parts[0] + constraint_text + "\n\n" + insert_marker + parts[1]
        else:
            # 如果找不到标记，追加到末尾
            enhanced_prompt = prompt + "\n\n" + constraint_text
        
        return enhanced_prompt
    
    def _build_constraint_section(self, 
                                  constraints: List[DiversityConstraint],
                                  recommendations: List[str]) -> str:
        """构建约束章节"""
        lines = []
        lines.append("[DIVERSITY CONSTRAINTS - CRITICAL]")
        lines.append("To improve test effectiveness, follow these diversity requirements:")
        lines.append("")
        
        # 添加约束
        for constraint in constraints:
            lines.append(constraint.to_prompt_text())
        
        lines.append("")
        
        # 添加推荐场景
        if recommendations:
            lines.append("[RECOMMENDED NEW APPROACHES]")
            for i, rec in enumerate(recommendations, 1):
                lines.append(f"{i}. {rec}")
        
        lines.append("")
        lines.append("IMPORTANT: Repeated test patterns reduce coverage improvement efficiency.")
        lines.append("Generate a DISTINCTLY DIFFERENT test sequence from previous attempts.")
        
        return "\n".join(lines)
    
    def get_diversity_context(self) -> str:
        """获取多样性上下文信息（用于Prompt）"""
        if not self.history.records:
            return ""
        
        stats = self.history.get_statistics()
        overused = self.history.get_overused_patterns(DiversityConfig.OVERUSE_THRESHOLD)
        
        context_lines = []
        context_lines.append(f"Test History: {stats['total_tests']} tests generated")
        context_lines.append(f"Unique Patterns: {stats['total_patterns']}")
        
        if overused:
            context_lines.append(f"Overused Patterns: {len(overused)} (avoid these)")
        
        return "\n".join(context_lines)
    
    def evaluate_diversity(self, 
                          new_code: str,
                          known_signals: List[str] = None) -> Dict[str, float]:
        """
        评估新代码的多样性
        
        Args:
            new_code: 新生成的测试代码
            known_signals: 已知信号列表
            
        Returns:
            多样性评估结果
        """
        results = {}
        
        # 1. 序列多样性
        if known_signals:
            self.history.sequence_extractor.set_known_signals(known_signals)
        new_sequences = self.history.sequence_extractor.extract(new_code)
        results['sequence_diversity'] = self.history.calculate_sequence_diversity(new_sequences)
        
        # 2. 编辑距离多样性
        results['edit_distance_diversity'] = self.history.calculate_edit_distance_diversity(new_code)
        
        # 3. 综合得分
        results['overall_diversity'] = (
            DiversityConfig.PATTERN_WEIGHT * results['sequence_diversity'] +
            DiversityConfig.EDIT_DISTANCE_WEIGHT * results['edit_distance_diversity']
        )
        
        return results
    
    def record_test(self, 
                   code: str,
                   target_function: str = "",
                   coverage_score: float = 0.0,
                   success: bool = False,
                   iteration: int = 0,
                   known_signals: List[str] = None) -> TestRecord:
        """
        记录新的测试用例
        
        Args:
            code: 测试代码
            target_function: 目标功能点
            coverage_score: 覆盖率分数
            success: 是否成功
            iteration: 迭代次数
            known_signals: 已知信号列表
            
        Returns:
            测试记录
        """
        return self.history.add_record(
            code=code,
            target_function=target_function,
            coverage_score=coverage_score,
            success=success,
            iteration=iteration,
            known_signals=known_signals
        )
    
    def get_statistics(self) -> Dict[str, Any]:
        """获取统计信息"""
        return self.history.get_statistics()
    
    def generate_diversity_report(self) -> str:
        """生成多样性报告"""
        return self.history.get_diversity_report()


# ============================================================================
# 便捷函数
# ============================================================================

def create_diversity_injector(history_file: str = None) -> DiversityInjector:
    """
    创建多样性约束注入器
    
    Args:
        history_file: 屆史记录文件路径
        
    Returns:
        初始化完成的多样性约束注入器
    """
    history_manager = TestHistoryManager(history_file=history_file)
    return DiversityInjector(history_manager=history_manager)
