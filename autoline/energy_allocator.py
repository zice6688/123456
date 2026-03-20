"""
Description :   Energy Allocation Layer (Layer 4)
                - Adaptive Resource Scheduling
                - Dynamic energy distribution based on function point importance
Author      :   CGA Enhancement Project
Time        :   2026/03/11
"""

import logging
from typing import List, Dict, Optional, Any, Tuple
from dataclasses import dataclass, field
from enum import Enum

logger = logging.getLogger(__name__)


# ============================================================================
# 数据结构定义
# ============================================================================

class EnergyState(Enum):
    """能量状态枚举"""
    ACTIVE = "active"           # 活跃，有剩余能量
    DEPLETED = "depleted"       # 能量耗尽
    COMPLETED = "completed"     # 已完成覆盖
    SUSPENDED = "suspended"     # 暂停（连续失败过多）


@dataclass
class EnergyAllocation:
    """
    能量分配记录
    
    Attributes:
        function_point: 功能点名称
        importance: 重要性评分 (0.0 - 1.0)
        allocated: 分配的总能量
        consumed: 已消耗的能量
        remaining: 剩余能量
        consecutive_failures: 连续失败次数
        state: 当前能量状态
    """
    function_point: str
    importance: float
    allocated: float = 0.0
    consumed: float = 0.0
    remaining: float = 0.0
    consecutive_failures: int = 0
    state: EnergyState = EnergyState.ACTIVE
    total_attempts: int = 0
    successful_attempts: int = 0


@dataclass
class GenerationResult:
    """
    生成结果记录
    
    Attributes:
        function_point: 目标功能点
        success: 是否成功覆盖
        coverage_delta: 覆盖率变化
        energy_cost: 消耗的能量
        code_generated: 生成的代码
        quality_score: 代码质量分数
    """
    function_point: str
    success: bool
    coverage_delta: float = 0.0
    energy_cost: float = 1.0
    code_generated: str = ""
    quality_score: float = 0.0


# ============================================================================
# 能量初始化器
# ============================================================================

class EnergyInitializer:
    """
    能量初始化器
    
    根据总能量预算和功能点重要性评分，初始化各功能点的能量分配
    """
    
    # 默认配置
    DEFAULT_TOTAL_ENERGY = 10.0       # 默认总能量（对应最大迭代次数）
    MIN_ENERGY_PER_FP = 1.0           # 每个功能点最小能量
    ENERGY_BUFFER_RATIO = 0.1         # 能量缓冲比例（保留用于重分配）
    
    def __init__(self, 
                 total_energy: float = None,
                 min_energy: float = None,
                 buffer_ratio: float = None):
        """
        Args:
            total_energy: 总能量预算（默认为 max_iter）
            min_energy: 每个功能点最小能量
            buffer_ratio: 能量缓冲比例
        """
        self.total_energy = total_energy or self.DEFAULT_TOTAL_ENERGY
        self.min_energy = min_energy or self.MIN_ENERGY_PER_FP
        self.buffer_ratio = buffer_ratio or self.ENERGY_BUFFER_RATIO
        
    def initialize(self, 
                   function_points: List[Dict],
                   max_iterations: int = None) -> Dict[str, EnergyAllocation]:
        """
        初始化能量分配
        
        Args:
            function_points: 功能点列表，每个元素包含 name, importance, covered 等
            max_iterations: 最大迭代次数（用于设置总能量）
            
        Returns:
            功能点名称 -> 能量分配记录 的字典
        """
        # 如果提供了最大迭代次数，使用它作为总能量
        if max_iterations:
            self.total_energy = float(max_iterations)
        
        # 过滤出未覆盖的功能点
        uncovered_fps = [fp for fp in function_points if not fp.get('covered', False)]
        
        if not uncovered_fps:
            logger.info("All function points are covered. No energy allocation needed.")
            return {}
        
        # 计算总重要性
        total_importance = sum(fp.get('importance', 0.5) for fp in uncovered_fps)
        
        # 预留缓冲能量
        buffer_energy = self.total_energy * self.buffer_ratio
        available_energy = self.total_energy - buffer_energy
        
        # 按重要性比例分配能量
        allocations = {}
        
        for fp in uncovered_fps:
            name = fp.get('name', 'unknown')
            importance = fp.get('importance', 0.5)
            
            # 按比例计算分配能量，但不少于最小值
            if total_importance > 0:
                proportional_energy = (importance / total_importance) * available_energy
            else:
                proportional_energy = available_energy / len(uncovered_fps)
            
            allocated = max(self.min_energy, proportional_energy)
            
            allocations[name] = EnergyAllocation(
                function_point=name,
                importance=importance,
                allocated=allocated,
                consumed=0.0,
                remaining=allocated,
                consecutive_failures=0,
                state=EnergyState.ACTIVE,
                total_attempts=0,
                successful_attempts=0
            )
        
        # 记录分配情况
        logger.info(f"Energy initialized: total={self.total_energy:.1f}, "
                   f"allocated={sum(a.allocated for a in allocations.values()):.1f}, "
                   f"buffer={buffer_energy:.1f}, "
                   f"targets={len(allocations)}")
        
        return allocations


# ============================================================================
# 目标选择器
# ============================================================================

class TargetSelector:
    """
    目标选择器
    
    选择下一个需要生成测试的目标功能点
    采用优先级策略：重要性 × (剩余能量/分配能量)
    """
    
    # 连续失败阈值
    MAX_CONSECUTIVE_FAILURES = 3
    
    def __init__(self, allocations: Dict[str, EnergyAllocation]):
        """
        Args:
            allocations: 能量分配字典
        """
        self.allocations = allocations
        
    def select_next_target(self) -> Optional[EnergyAllocation]:
        """
        选择下一个目标功能点
        
        优先级计算：importance × (remaining / allocated) × (1 / (1 + consecutive_failures))
        
        Returns:
            选中的能量分配记录，如果没有可用目标则返回 None
        """
        # 筛选候选：未覆盖、有剩余能量、非暂停状态
        candidates = [
            alloc for alloc in self.allocations.values()
            if alloc.state == EnergyState.ACTIVE 
            and alloc.remaining > 0
        ]
        
        if not candidates:
            logger.info("No active targets with remaining energy.")
            return None
        
        # 计算优先级并排序
        def calculate_priority(alloc: EnergyAllocation) -> float:
            # 重要性权重
            importance_weight = alloc.importance
            
            # 能量剩余比例
            energy_ratio = alloc.remaining / alloc.allocated if alloc.allocated > 0 else 0
            
            # 失败惩罚因子
            failure_penalty = 1.0 / (1.0 + alloc.consecutive_failures * 0.5)
            
            # 综合优先级
            priority = importance_weight * energy_ratio * failure_penalty
            return priority
        
        candidates.sort(key=calculate_priority, reverse=True)
        
        selected = candidates[0]
        logger.debug(f"Selected target: {selected.function_point} "
                    f"(importance={selected.importance:.2f}, "
                    f"remaining={selected.remaining:.1f}, "
                    f"failures={selected.consecutive_failures})")
        
        return selected
    
    def get_candidates_count(self) -> int:
        """获取候选目标数量"""
        return len([a for a in self.allocations.values() 
                   if a.state == EnergyState.ACTIVE and a.remaining > 0])
    
    def get_top_candidates(self, n: int = 3) -> List[EnergyAllocation]:
        """获取优先级最高的 N 个候选目标"""
        candidates = [
            alloc for alloc in self.allocations.values()
            if alloc.state == EnergyState.ACTIVE and alloc.remaining > 0
        ]
        
        def calculate_priority(alloc: EnergyAllocation) -> float:
            importance_weight = alloc.importance
            energy_ratio = alloc.remaining / alloc.allocated if alloc.allocated > 0 else 0
            failure_penalty = 1.0 / (1.0 + alloc.consecutive_failures * 0.5)
            return importance_weight * energy_ratio * failure_penalty
        
        candidates.sort(key=calculate_priority, reverse=True)
        return candidates[:n]


# ============================================================================
# 能量消耗跟踪器
# ============================================================================

class EnergyConsumptionTracker:
    """
    能量消耗跟踪器
    
    跟踪每次生成尝试的能量消耗，根据结果更新状态
    """
    
    # 能量衰减因子（连续失败时）
    ENERGY_DECAY_FACTOR = 0.7
    
    def __init__(self, allocations: Dict[str, EnergyAllocation]):
        """
        Args:
            allocations: 能量分配字典
        """
        self.allocations = allocations
        self.history: List[GenerationResult] = []
        
    def record_generation(self, result: GenerationResult) -> Dict[str, Any]:
        """
        记录一次生成尝试
        
        Args:
            result: 生成结果
            
        Returns:
            更新后的状态信息
        """
        self.history.append(result)
        
        fp_name = result.function_point
        if fp_name not in self.allocations:
            logger.warning(f"Unknown function point: {fp_name}")
            return {'status': 'unknown', 'message': 'Unknown function point'}
        
        alloc = self.allocations[fp_name]
        alloc.total_attempts += 1
        
        # 消耗能量
        energy_cost = result.energy_cost
        alloc.consumed += energy_cost
        alloc.remaining = max(0, alloc.remaining - energy_cost)
        
        if result.success:
            # 成功：重置失败计数，标记完成
            alloc.consecutive_failures = 0
            alloc.successful_attempts += 1
            alloc.state = EnergyState.COMPLETED
            
            logger.info(f"[SUCCESS] Target covered: {fp_name} (attempts={alloc.total_attempts}, "
                          f"energy_used={alloc.consumed:.1f})")
            
            return {
                'status': 'completed',
                'function_point': fp_name,
                'attempts': alloc.total_attempts,
                'energy_used': alloc.consumed
            }
        else:
            # 失败：增加失败计数
            alloc.consecutive_failures += 1
            
            # 检查是否需要降低能量或暂停
            if alloc.consecutive_failures >= 3:
                # 能量减半
                old_remaining = alloc.remaining
                alloc.remaining *= self.ENERGY_DECAY_FACTOR
                
                logger.warning(f"Consecutive failures for {fp_name}: {alloc.consecutive_failures}. "
                              f"Energy reduced: {old_remaining:.1f} -> {alloc.remaining:.1f}")
                
                # 如果剩余能量过低，暂停
                if alloc.remaining < 0.5:
                    alloc.state = EnergyState.SUSPENDED
                    logger.warning(f"Target suspended due to low energy: {fp_name}")
                    
                    return {
                        'status': 'suspended',
                        'function_point': fp_name,
                        'consecutive_failures': alloc.consecutive_failures,
                        'remaining_energy': alloc.remaining
                    }
            
            # 检查能量是否耗尽
            if alloc.remaining <= 0:
                alloc.state = EnergyState.DEPLETED
                logger.warning(f"Target depleted: {fp_name}")
                
                return {
                    'status': 'depleted',
                    'function_point': fp_name,
                    'total_attempts': alloc.total_attempts
                }
            
            return {
                'status': 'failed',
                'function_point': fp_name,
                'consecutive_failures': alloc.consecutive_failures,
                'remaining_energy': alloc.remaining
            }
    
    def get_statistics(self) -> Dict[str, Any]:
        """获取统计信息"""
        total = len(self.history)
        successful = sum(1 for r in self.history if r.success)
        
        energy_by_fp = {}
        for result in self.history:
            fp = result.function_point
            if fp not in energy_by_fp:
                energy_by_fp[fp] = {'consumed': 0, 'attempts': 0, 'success': False}
            energy_by_fp[fp]['consumed'] += result.energy_cost
            energy_by_fp[fp]['attempts'] += 1
            if result.success:
                energy_by_fp[fp]['success'] = True
        
        return {
            'total_attempts': total,
            'successful_attempts': successful,
            'success_rate': successful / total if total > 0 else 0,
            'energy_by_function_point': energy_by_fp
        }


# ============================================================================
# 能量重分配器
# ============================================================================

class EnergyRedistributor:
    """
    能量重分配器
    
    当某个功能点被覆盖后，将其剩余能量重新分配给其他未覆盖功能点
    """
    
    def __init__(self, allocations: Dict[str, EnergyAllocation]):
        """
        Args:
            allocations: 能量分配字典
        """
        self.allocations = allocations
        
    def redistribute(self, completed_fp: str) -> Dict[str, float]:
        """
        重分配已完成功能点的剩余能量
        
        Args:
            completed_fp: 已完成的功能点名称
            
        Returns:
            重分配详情 {target_fp: gained_energy}
        """
        if completed_fp not in self.allocations:
            return {}
        
        completed_alloc = self.allocations[completed_fp]
        
        # 回收剩余能量
        recovered_energy = completed_alloc.remaining
        
        if recovered_energy <= 0:
            logger.debug(f"No remaining energy to recover from {completed_fp}")
            return {}
        
        # 找出活跃的未完成目标
        active_targets = [
            alloc for alloc in self.allocations.values()
            if alloc.state == EnergyState.ACTIVE and alloc.function_point != completed_fp
        ]
        
        if not active_targets:
            logger.info(f"No active targets to redistribute energy to.")
            return {}
        
        # 按重要性比例分配
        total_importance = sum(a.importance for a in active_targets)
        redistribution = {}
        
        for alloc in active_targets:
            if total_importance > 0:
                gain = (alloc.importance / total_importance) * recovered_energy
            else:
                gain = recovered_energy / len(active_targets)
            
            alloc.allocated += gain
            alloc.remaining += gain
            redistribution[alloc.function_point] = gain
        
        # 清零已完成目标的剩余能量
        completed_alloc.remaining = 0
        
        logger.info(f"Redistributed {recovered_energy:.1f} energy from {completed_fp} "
                   f"to {len(redistribution)} targets")
        
        return redistribution
    
    def redistribute_all(self) -> Dict[str, Dict[str, float]]:
        """
        重分配所有已完成/暂停目标的剩余能量
        
        Returns:
            完整的重分配详情
        """
        all_redistributions = {}
        
        # 收集所有可回收能量
        completed_fps = [
            name for name, alloc in self.allocations.items()
            if alloc.state in [EnergyState.COMPLETED, EnergyState.SUSPENDED]
            and alloc.remaining > 0
        ]
        
        for fp in completed_fps:
            redistribution = self.redistribute(fp)
            if redistribution:
                all_redistributions[fp] = redistribution
        
        return all_redistributions
    
    def revive_suspended(self, min_energy: float = 1.0) -> List[str]:
        """
        尝试复活暂停的目标（如果有足够的回收能量）
        
        Args:
            min_energy: 复活所需的最小能量
            
        Returns:
            复活的目标列表
        """
        revived = []
        
        # 计算可用能量（来自已完成目标）
        available_energy = sum(
            alloc.remaining for alloc in self.allocations.values()
            if alloc.state == EnergyState.COMPLETED and alloc.remaining > 0
        )
        
        # 找出暂停的目标
        suspended = [
            alloc for alloc in self.allocations.values()
            if alloc.state == EnergyState.SUSPENDED
        ]
        
        for alloc in suspended:
            if available_energy >= min_energy:
                # 复活
                alloc.state = EnergyState.ACTIVE
                alloc.remaining = min_energy
                alloc.allocated += min_energy
                alloc.consecutive_failures = 0
                available_energy -= min_energy
                revived.append(alloc.function_point)
                
                logger.info(f"Revived suspended target: {alloc.function_point}")
        
        return revived


# ============================================================================
# 能量分配器（主入口）
# ============================================================================

class EnergyAllocator:
    """
    能量分配器 - 第4层主入口
    
    整合所有子模块，提供统一的能量管理接口
    """
    
    def __init__(self, 
                 max_iterations: int = 5,
                 total_energy: float = None):
        """
        Args:
            max_iterations: 最大迭代次数
            total_energy: 总能量预算（默认使用 max_iterations）
        """
        self.max_iterations = max_iterations
        self.total_energy = total_energy or float(max_iterations)
        
        # 子模块
        self.initializer = EnergyInitializer(total_energy=self.total_energy)
        self.allocations: Dict[str, EnergyAllocation] = {}
        self.selector: Optional[TargetSelector] = None
        self.tracker: Optional[EnergyConsumptionTracker] = None
        self.redistributor: Optional[EnergyRedistributor] = None
        
        # 状态
        self.initialized = False
        self.current_target: Optional[EnergyAllocation] = None
        
    def initialize(self, function_points: List[Dict]) -> Dict[str, Any]:
        """
        初始化能量分配
        
        Args:
            function_points: 功能点列表
            
        Returns:
            初始化结果摘要
        """
        self.allocations = self.initializer.initialize(
            function_points, 
            max_iterations=self.max_iterations
        )
        
        self.selector = TargetSelector(self.allocations)
        self.tracker = EnergyConsumptionTracker(self.allocations)
        self.redistributor = EnergyRedistributor(self.allocations)
        self.initialized = True
        
        return {
            'total_energy': self.total_energy,
            'targets': len(self.allocations),
            'allocation_details': {
                name: {
                    'importance': alloc.importance,
                    'allocated': alloc.allocated,
                    'state': alloc.state.value
                }
                for name, alloc in self.allocations.items()
            }
        }
    
    def select_next_target(self) -> Optional[str]:
        """
        选择下一个生成目标
        
        Returns:
            目标功能点名称，如果没有可用目标则返回 None
        """
        if not self.initialized:
            logger.warning("Energy allocator not initialized.")
            return None
        
        self.current_target = self.selector.select_next_target()
        return self.current_target.function_point if self.current_target else None
    
    def record_generation(self, 
                          success: bool,
                          coverage_delta: float = 0.0,
                          energy_cost: float = 1.0,
                          quality_score: float = 0.0) -> Dict[str, Any]:
        """
        记录一次生成尝试
        
        Args:
            success: 是否成功覆盖目标
            coverage_delta: 覆盖率变化
            energy_cost: 消耗的能量
            quality_score: 代码质量分数
            
        Returns:
            更新结果
        """
        if not self.current_target:
            return {'status': 'error', 'message': 'No current target'}
        
        result = GenerationResult(
            function_point=self.current_target.function_point,
            success=success,
            coverage_delta=coverage_delta,
            energy_cost=energy_cost,
            quality_score=quality_score
        )
        
        update_result = self.tracker.record_generation(result)
        
        # 如果成功，触发重分配
        if success:
            self.redistributor.redistribute(self.current_target.function_point)
        
        return update_result
    
    def get_status(self) -> Dict[str, Any]:
        """获取当前状态"""
        if not self.initialized:
            return {'initialized': False}
        
        active_count = sum(1 for a in self.allocations.values() 
                          if a.state == EnergyState.ACTIVE and a.remaining > 0)
        completed_count = sum(1 for a in self.allocations.values() 
                             if a.state == EnergyState.COMPLETED)
        
        return {
            'initialized': True,
            'total_energy': self.total_energy,
            'total_targets': len(self.allocations),
            'active_targets': active_count,
            'completed_targets': completed_count,
            'current_target': self.current_target.function_point if self.current_target else None,
            'statistics': self.tracker.get_statistics() if self.tracker else None
        }
    
    def get_target_context(self, target_name: str = None) -> str:
        """
        获取目标功能的上下文信息（用于 Prompt）
        
        Args:
            target_name: 目标名称（默认使用当前目标）
            
        Returns:
            上下文字符串
        """
        if not target_name and self.current_target:
            target_name = self.current_target.function_point
        
        if not target_name or target_name not in self.allocations:
            return ""
        
        alloc = self.allocations[target_name]
        
        context = []
        context.append(f"[TARGET: {target_name}]")
        context.append(f"Importance: {alloc.importance:.2f}")
        context.append(f"Remaining Energy: {alloc.remaining:.1f} / {alloc.allocated:.1f}")
        context.append(f"Previous Attempts: {alloc.total_attempts}")
        
        if alloc.consecutive_failures > 0:
            context.append(f"Warning: {alloc.consecutive_failures} consecutive failures")
            context.append("Consider a different approach or sequence")
        
        return "\n".join(context)
    
    def generate_report(self) -> str:
        """生成能量分配报告"""
        if not self.initialized:
            return "Energy allocator not initialized."
        
        lines = []
        lines.append("=" * 60)
        lines.append("ENERGY ALLOCATION REPORT")
        lines.append("=" * 60)
        lines.append(f"Total Energy: {self.total_energy:.1f}")
        lines.append(f"Max Iterations: {self.max_iterations}")
        lines.append("")
        
        lines.append("FUNCTION POINT STATUS:")
        lines.append("-" * 60)
        
        for name, alloc in sorted(self.allocations.items(), 
                                  key=lambda x: x[1].importance, reverse=True):
            status_icon = {
                EnergyState.ACTIVE: "🔄",
                EnergyState.COMPLETED: "✅",
                EnergyState.DEPLETED: "❌",
                EnergyState.SUSPENDED: "⏸️"
            }.get(alloc.state, "❓")
            
            efficiency = (alloc.successful_attempts / alloc.total_attempts * 100 
                         if alloc.total_attempts > 0 else 0)
            
            lines.append(f"{status_icon} {name}")
            lines.append(f"   Importance: {alloc.importance:.2f} | "
                        f"Energy: {alloc.remaining:.1f}/{alloc.allocated:.1f} | "
                        f"Efficiency: {efficiency:.0f}%")
            lines.append(f"   Attempts: {alloc.total_attempts} | "
                        f"Consecutive Failures: {alloc.consecutive_failures}")
        
        lines.append("")
        lines.append("SUMMARY:")
        lines.append("-" * 60)
        stats = self.tracker.get_statistics()
        lines.append(f"Total Attempts: {stats['total_attempts']}")
        lines.append(f"Successful: {stats['successful_attempts']}")
        lines.append(f"Success Rate: {stats['success_rate']*100:.1f}%")
        
        completed = sum(1 for a in self.allocations.values() 
                       if a.state == EnergyState.COMPLETED)
        lines.append(f"Targets Covered: {completed} / {len(self.allocations)}")
        
        lines.append("=" * 60)
        
        return "\n".join(lines)


# ============================================================================
# 便捷函数
# ============================================================================

def create_energy_allocator(function_points: List[Dict],
                           max_iterations: int = 5) -> EnergyAllocator:
    """
    便捷函数：创建并初始化能量分配器
    
    Args:
        function_points: 功能点列表
        max_iterations: 最大迭代次数
        
    Returns:
        初始化完成的能量分配器
    """
    allocator = EnergyAllocator(max_iterations=max_iterations)
    allocator.initialize(function_points)
    return allocator