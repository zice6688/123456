"""
Description :   Test History Manager (Layer 1 Support Module)
                - Store and manage test case history
                - Support sequence pattern analysis
                - Provide diversity statistics
Author      :   CGA Enhancement Project
Time        :   2026/03/16
"""

import json
import os
import logging
from typing import List, Dict, Optional, Any, Tuple, Set
from dataclasses import dataclass, field, asdict
from datetime import datetime
from collections import defaultdict
import hashlib
import re

logger = logging.getLogger(__name__)


# ============================================================================
# 数据结构定义
# ============================================================================

@dataclass
class InputSequence:
    """
    输入序列记录
    
    Attributes:
        signal_name: 信号名称
        values: 赋值序列 [(time, value), ...]
    """
    signal_name: str
    values: List[Tuple[int, Any]] = field(default_factory=list)
    
    def to_pattern_string(self) -> str:
        """转换为模式字符串（仅包含值）"""
        return "->".join(str(v[1]) for v in self.values)
    
    def get_hash(self) -> str:
        """获取序列哈希值"""
        return hashlib.md5(self.to_pattern_string().encode()).hexdigest()[:8]


@dataclass
class TestRecord:
    """
    测试用例记录
    
    Attributes:
        test_id: 测试ID
        code: 生成的测试代码
        input_sequences: 输入信号序列列表
        target_function: 目标功能点
        covered_lines: 覆盖的代码行
        covered_functions: 覆盖的功能点
        coverage_score: 覆盖率分数
        diversity_scores: 多样性得分字典
        iteration: 迭代次数
        timestamp: 时间戳
        success: 是否成功
    """
    test_id: str
    code: str = ""
    input_sequences: List[InputSequence] = field(default_factory=list)
    target_function: str = ""
    covered_lines: List[int] = field(default_factory=list)
    covered_functions: List[str] = field(default_factory=list)
    coverage_score: float = 0.0
    diversity_scores: Dict[str, float] = field(default_factory=dict)
    iteration: int = 0
    timestamp: str = field(default_factory=lambda: datetime.now().isoformat())
    success: bool = False
    
    def get_sequence_patterns(self) -> Dict[str, str]:
        """获取所有输入序列的模式"""
        return {seq.signal_name: seq.to_pattern_string() for seq in self.input_sequences}


@dataclass
class SequencePattern:
    """
    序列模式统计
    
    Attributes:
        pattern: 模式字符串
        count: 出现次数
        signal_name: 所属信号
        test_ids: 关联的测试ID列表
    """
    pattern: str
    count: int = 0
    signal_name: str = ""
    test_ids: List[str] = field(default_factory=list)
    
    def is_overused(self, threshold: int = 3) -> bool:
        """判断是否过度使用"""
        return self.count >= threshold


# ============================================================================
# 序列提取器
# ============================================================================

class SequenceExtractor:
    """
    从测试代码中提取输入序列
    
    解析Verilog测试代码，提取信号赋值序列
    """
    
    # 匹配信号赋值语句
    ASSIGNMENT_PATTERNS = [
        # 阻塞赋值: signal = value;
        r'(\w+)\s*=\s*([0-9]+\'[bdh][0-9a-fA-FxXzZ_]+|\d+|x|z)\s*;',
        # 非阻塞赋值: signal <= value;
        r'(\w+)\s*<=\s*([0-9]+\'[bdh][0-9a-fA-FxXzZ_]+|\d+|x|z)\s*;',
        # 简单赋值（无位宽）
        r'(\w+)\s*=\s*(\d+)\s*;',
    ]
    
    # 匹配延时
    DELAY_PATTERN = r'#\s*(\d+)\s*;'
    
    # 匹配时钟周期等待
    CLOCK_WAIT_PATTERN = r'repeat\s*\(\s*(\d+)\s*\)\s*@\s*\(\s*posedge\s+(\w+)\s*\)'
    
    def __init__(self):
        self.known_signals: Set[str] = set()
        
    def set_known_signals(self, signals: List[str]):
        """设置已知信号列表（用于过滤）"""
        self.known_signals = set(signals)
    
    def extract(self, code: str) -> List[InputSequence]:
        """
        从代码中提取输入序列
        
        Args:
            code: Verilog测试代码
            
        Returns:
            输入序列列表
        """
        sequences = {}
        current_time = 0
        
        # 按行处理代码
        lines = code.split('\n')
        
        for line in lines:
            line = line.strip()
            
            # 跳过注释和空行
            if not line or line.startswith('//'):
                continue
            
            # 检测延时，更新时间
            delay_match = re.search(self.DELAY_PATTERN, line)
            if delay_match:
                current_time += int(delay_match.group(1))
                continue
            
            # 检测时钟周期等待
            clock_match = re.search(self.CLOCK_WAIT_PATTERN, line, re.IGNORECASE)
            if clock_match:
                cycles = int(clock_match.group(1))
                current_time += cycles * 10  # 假设每周期10时间单位
                continue
            
            # 检测赋值语句
            for pattern in self.ASSIGNMENT_PATTERNS:
                matches = re.finditer(pattern, line, re.IGNORECASE)
                for match in matches:
                    signal = match.group(1)
                    value = match.group(2)
                    
                    # 过滤非目标信号
                    if self.known_signals and signal not in self.known_signals:
                        continue
                    
                    # 跳过明显的非输入信号
                    if signal.lower() in ['i', 'j', 'k', 'cnt', 'count', 'temp']:
                        continue
                    
                    if signal not in sequences:
                        sequences[signal] = InputSequence(signal_name=signal)
                    
                    sequences[signal].values.append((current_time, value))
                    current_time += 1  # 赋值语句本身占用1时间单位
        
        return list(sequences.values())


# ============================================================================
# 测试历史管理器
# ============================================================================

class TestHistoryManager:
    """
    测试历史管理器
    
    管理已生成测试用例的历史记录，支持：
    - 测试用例存储和检索
    - 序列模式统计分析
    - 多样性分布统计
    """
    
    def __init__(self, history_file: str = None):
        """
        Args:
            history_file: 历史记录文件路径（可选）
        """
        
        #必须先保存 history_file，否则 save() 方法无法找到文件路径
        self.history_file = history_file
        
        self.records: List[TestRecord] = []
        self.patterns: Dict[str, SequencePattern] = {}  # pattern_hash -> SequencePattern
        self.signal_patterns: Dict[str, List[str]] = defaultdict(list)  # signal_name -> [pattern_hashes]
        self.sequence_extractor = SequenceExtractor()
        
        # 统计信息
        self.stats = {
            'total_tests': 0,
            'successful_tests': 0,
            'total_coverage': 0.0,
            'avg_diversity': 0.0
        }
        
        if history_file and os.path.exists(history_file):
            self.load(history_file)
    
    # ==================== 记录管理 ====================
    
    def add_record(self, 
                   code: str,
                   test_id: str = None,
                   target_function: str = "",
                   covered_lines: List[int] = None,
                   covered_functions: List[str] = None,
                   coverage_score: float = 0.0,
                   iteration: int = 0,
                   success: bool = False,
                   known_signals: List[str] = None) -> TestRecord:
        """
        添加测试记录
        
        Args:
            code: 测试代码
            test_id: 测试ID（自动生成如果未提供）
            target_function: 目标功能点
            covered_lines: 覆盖的代码行
            covered_functions: 覆盖的功能点
            coverage_score: 覆盖率分数
            iteration: 迭代次数
            success: 是否成功
            known_signals: 已知信号列表
            
        Returns:
            创建的测试记录
        """
        if test_id is None:
            test_id = f"test_{len(self.records)}_{datetime.now().strftime('%H%M%S')}"
        
        # 提取输入序列
        if known_signals:
            self.sequence_extractor.set_known_signals(known_signals)
        input_sequences = self.sequence_extractor.extract(code)
        
        # 创建记录
        record = TestRecord(
            test_id=test_id,
            code=code,
            input_sequences=input_sequences,
            target_function=target_function,
            covered_lines=covered_lines or [],
            covered_functions=covered_functions or [],
            coverage_score=coverage_score,
            iteration=iteration,
            success=success
        )
        
        self.records.append(record)
        
        # 更新模式统计
        self._update_patterns(record)
        
        # 更新统计信息
        self._update_stats()
        
        logger.debug(f"Added test record: {test_id}, sequences: {len(input_sequences)}")
        
        return record
    
    def get_record(self, test_id: str) -> Optional[TestRecord]:
        """根据ID获取记录"""
        for record in self.records:
            if record.test_id == test_id:
                return record
        return None
    
    def get_recent_records(self, n: int = 10) -> List[TestRecord]:
        """获取最近的N条记录"""
        return self.records[-n:] if len(self.records) >= n else self.records
    
    def get_successful_records(self) -> List[TestRecord]:
        """获取所有成功的记录"""
        return [r for r in self.records if r.success]
    
    # ==================== 模式分析 ====================
    
    def _update_patterns(self, record: TestRecord):
        """更新序列模式统计"""
        for seq in record.input_sequences:
            pattern_str = seq.to_pattern_string()
            pattern_hash = seq.get_hash()
            
            if pattern_hash not in self.patterns:
                self.patterns[pattern_hash] = SequencePattern(
                    pattern=pattern_str,
                    count=1,
                    signal_name=seq.signal_name,
                    test_ids=[record.test_id]
                )
            else:
                self.patterns[pattern_hash].count += 1
                self.patterns[pattern_hash].test_ids.append(record.test_id)
            
            # 按信号索引
            if pattern_hash not in self.signal_patterns[seq.signal_name]:
                self.signal_patterns[seq.signal_name].append(pattern_hash)
    
    def get_overused_patterns(self, threshold: int = 3) -> List[SequencePattern]:
        """
        获取过度使用的模式
        
        Args:
            threshold: 过度使用阈值
            
        Returns:
            过度使用的模式列表
        """
        return [p for p in self.patterns.values() if p.is_overused(threshold)]
    
    def get_common_patterns(self, top_n: int = 5) -> List[Tuple[str, int]]:
        """
        获取最常见的模式
        
        Args:
            top_n: 返回数量
            
        Returns:
            [(pattern, count), ...]
        """
        sorted_patterns = sorted(
            self.patterns.items(), 
            key=lambda x: x[1].count, 
            reverse=True
        )
        return [(p[1].pattern, p[1].count) for p in sorted_patterns[:top_n]]
    
    def get_pattern_for_signal(self, signal_name: str) -> List[SequencePattern]:
        """获取特定信号的所有模式"""
        pattern_hashes = self.signal_patterns.get(signal_name, [])
        return [self.patterns[h] for h in pattern_hashes if h in self.patterns]
    
    # ==================== 多样性分析 ====================
    
    def calculate_sequence_diversity(self, new_sequences: List[InputSequence]) -> float:
        """
        计算新序列与历史记录的多样性得分
        
        Args:
            new_sequences: 新的输入序列列表
            
        Returns:
            多样性得分 (0.0 - 1.0)
        """
        if not self.records:
            return 1.0  # 没有历史记录时，认为完全多样
        
        if not new_sequences:
            return 0.0  # 没有序列时，多样性为0
        
        # 检查模式重复度
        new_patterns = {seq.get_hash() for seq in new_sequences}
        total_patterns = len(new_patterns)
        
        if total_patterns == 0:
            return 0.0
        
        # 计算新模式比例
        new_pattern_count = sum(1 for h in new_patterns if h not in self.patterns)
        pattern_diversity = new_pattern_count / total_patterns
        
        return pattern_diversity
    
    def calculate_edit_distance_diversity(self, new_code: str) -> float:
        """
        基于编辑距离计算多样性
        
        使用简化的编辑距离计算
        """
        if not self.records:
            return 1.0
        
        # 获取最近的记录作为参考
        recent_records = self.get_recent_records(5)
        
        min_distance = float('inf')
        for record in recent_records:
            distance = self._levenshtein_distance(new_code, record.code)
            min_distance = min(min_distance, distance)
        
        # 归一化到 [0, 1]
        max_len = max(len(new_code), max(len(r.code) for r in recent_records))
        if max_len == 0:
            return 0.0
        
        return min_distance / max_len
    
    def _levenshtein_distance(self, s1: str, s2: str) -> int:
        """计算Levenshtein编辑距离（简化版）"""
        if len(s1) < len(s2):
            return self._levenshtein_distance(s2, s1)
        
        if len(s2) == 0:
            return len(s1)
        
        # 使用简化的计算（抽样）
        if len(s1) > 500:
            s1 = s1[:500]
        if len(s2) > 500:
            s2 = s2[:500]
        
        previous_row = range(len(s2) + 1)
        for i, c1 in enumerate(s1):
            current_row = [i + 1]
            for j, c2 in enumerate(s2):
                insertions = previous_row[j + 1] + 1
                deletions = current_row[j] + 1
                substitutions = previous_row[j] + (c1 != c2)
                current_row.append(min(insertions, deletions, substitutions))
            previous_row = current_row
        
        return previous_row[-1]
    
    # ==================== 统计信息 ====================
    
    def _update_stats(self):
        """更新统计信息"""
        self.stats['total_tests'] = len(self.records)
        self.stats['successful_tests'] = sum(1 for r in self.records if r.success)
        
        if self.records:
            self.stats['total_coverage'] = sum(r.coverage_score for r in self.records)
            self.stats['avg_coverage'] = self.stats['total_coverage'] / len(self.records)
    
    def get_statistics(self) -> Dict[str, Any]:
        """获取统计信息"""
        return {
            **self.stats,
            'total_patterns': len(self.patterns),
            'overused_patterns': len(self.get_overused_patterns()),
            'unique_signals': len(self.signal_patterns)
        }
    
    def get_diversity_report(self) -> str:
        """生成多样性报告"""
        lines = []
        lines.append("=" * 50)
        lines.append("TEST HISTORY DIVERSITY REPORT")
        lines.append("=" * 50)
        lines.append(f"Total Tests: {self.stats['total_tests']}")
        lines.append(f"Successful Tests: {self.stats['successful_tests']}")
        lines.append(f"Total Patterns: {len(self.patterns)}")
        lines.append("")
        
        # 常见模式
        lines.append("TOP 5 COMMON PATTERNS:")
        common = self.get_common_patterns(5)
        for i, (pattern, count) in enumerate(common, 1):
            lines.append(f"  {i}. {pattern[:40]}... (x{count})")
        
        # 过度使用的模式
        overused = self.get_overused_patterns()
        if overused:
            lines.append("")
            lines.append("OVERUSED PATTERNS (need diversification):")
            for p in overused[:5]:
                lines.append(f"  - {p.signal_name}: {p.pattern[:30]}... (used {p.count} times)")
        
        lines.append("=" * 50)
        return "\n".join(lines)
    
    # ==================== 持久化 ====================
    
    def save(self, filepath: str = None):
        """保存历史记录到文件"""
        filepath = filepath or self.history_file
        if not filepath:
            return
        
        # 手动构建可序列化的数据结构
        records_data = []
        for r in self.records:
            record_dict = {
                'test_id': r.test_id,
                'code': r.code,
                'input_sequences': [],
                'target_function': r.target_function,
                'covered_lines': r.covered_lines,
                'covered_functions': r.covered_functions,
                'coverage_score': r.coverage_score,
                'diversity_scores': r.diversity_scores,
                'iteration': r.iteration,
                'timestamp': r.timestamp,
                'success': r.success
            }
            # 手动转换 InputSequence 对象
            for seq in r.input_sequences:
                record_dict['input_sequences'].append({
                    'signal_name': seq.signal_name,
                    'values': seq.values
                })
            records_data.append(record_dict)
        
        data = {
            'records': records_data,
            'stats': self.stats
        }
        
        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        
        logger.info(f"Test history saved to {filepath}")
    
    def load(self, filepath: str):
        """从文件加载历史记录"""
        if not os.path.exists(filepath):
            return
        
        with open(filepath, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        self.records = []
        for r in data.get('records', []):
            sequences = [
                InputSequence(**s) for s in r.get('input_sequences', [])
            ]
            record = TestRecord(
                test_id=r['test_id'],
                code=r['code'],
                input_sequences=sequences,
                target_function=r.get('target_function', ''),
                covered_lines=r.get('covered_lines', []),
                covered_functions=r.get('covered_functions', []),
                coverage_score=r.get('coverage_score', 0.0),
                iteration=r.get('iteration', 0),
                timestamp=r.get('timestamp', ''),
                success=r.get('success', False)
            )
            self.records.append(record)
            self._update_patterns(record)
        
        self.stats = data.get('stats', self.stats)
        logger.info(f"Loaded {len(self.records)} test records from {filepath}")


# ============================================================================
# 便捷函数
# ============================================================================

def create_test_history(history_file: str = None) -> TestHistoryManager:
    """创建测试历史管理器"""
    return TestHistoryManager(history_file=history_file)