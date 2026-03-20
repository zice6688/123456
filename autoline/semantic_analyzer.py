"""
Description :   Semantic Analysis Layer (Layer 0)
                - RTL Structure Parser
                - Function Point Recognizer  
                - Importance Scorer
                - Test Scenario Generator
Author      :   CGA Enhancement Project
Time        :   2026/03/08
"""

import re
import logging
from typing import List, Dict, Tuple, Optional, Any
from dataclasses import dataclass, field
from enum import Enum

logger = logging.getLogger(__name__)


# ============================================================================
# 数据结构定义
# ============================================================================

class FunctionPointType(Enum):
    """功能点类型枚举"""
    FSM = "fsm"              # 状态机
    COUNTER = "counter"      # 计数器
    CONDITION = "condition"  # 条件分支
    PROTOCOL = "protocol"    # 协议接口
    EXCEPTION = "exception"  # 异常处理


@dataclass
class Port:
    """端口信息"""
    name: str
    direction: str  # input, output, inout
    width: int = 1
    msb: int = 0
    lsb: int = 0


@dataclass
class Signal:
    """信号信息"""
    name: str
    signal_type: str  # wire, reg, logic
    width: int = 1
    msb: int = 0
    lsb: int = 0


@dataclass
class Parameter:
    """参数信息"""
    name: str
    value: str
    param_type: str = "parameter"  # parameter, localparam


@dataclass
class CodeRegion:
    """代码区域"""
    start_line: int
    end_line: int
    region_type: str  # always, assign, instance, etc.
    content: str


@dataclass
class FunctionPoint:
    """功能点"""
    name: str
    fp_type: FunctionPointType
    location: Tuple[int, int]  # (start_line, end_line)
    code_region: str
    importance_score: float = 0.0
    covered: bool = False
    attributes: Dict[str, Any] = field(default_factory=dict)


@dataclass
class TestScenario:
    """测试场景建议"""
    name: str
    target_function: str
    description: str
    priority: float
    scenario_type: str  # transition, boundary, exception, etc.


@dataclass
class RTLStructure:
    """RTL结构信息"""
    module_name: str = ""
    ports: List[Port] = field(default_factory=list)
    signals: List[Signal] = field(default_factory=list)
    parameters: List[Parameter] = field(default_factory=list)
    code_regions: List[CodeRegion] = field(default_factory=list)
    signal_dependencies: Dict[str, List[str]] = field(default_factory=dict)


# ============================================================================
# RTL 结构解析器
# ============================================================================

class RTLStructureParser:
    """
    RTL结构解析器
    解析RTL代码的基础结构信息，为后续分析提供结构化数据
    """
    
    def __init__(self, rtl_code: str):
        """
        Args:
            rtl_code: RTL源代码字符串
        """
        self.code = rtl_code
        self.lines = rtl_code.split('\n')
        self.structure = RTLStructure()
        
    def parse(self) -> RTLStructure:
        """执行完整解析"""
        self._parse_module_header()
        self._parse_ports()
        self._parse_signals()
        self._parse_parameters()
        self._parse_code_regions()
        self._build_signal_dependencies()
        return self.structure
    
    def _parse_module_header(self):
        """解析模块头"""
        # 匹配 module name (...) 或 module name;
        pattern = r'module\s+(\w+)\s*(?:#\s*\([^)]*\))?\s*(?:\(([^)]*)\))?'
        match = re.search(pattern, self.code, re.DOTALL)
        if match:
            self.structure.module_name = match.group(1)
    
    def _parse_ports(self):
        """解析端口定义"""
        # 从模块声明中提取端口
        port_patterns = [
            r'(input|output|inout)\s+(?:wire\s+|reg\s+)?(?:\[(\d+):(\d+)\]\s+)?(\w+)',
            r'(input|output|inout)\s+(?:\[(\d+):(\d+)\]\s+)?(\w+)',
        ]
        
        for pattern in port_patterns:
            for match in re.finditer(pattern, self.code):
                direction = match.group(1)
                msb = int(match.group(2)) if match.group(2) else 0
                lsb = int(match.group(3)) if match.group(3) else 0
                name = match.group(4)
                width = abs(msb - lsb) + 1
                
                # 避免重复添加
                if not any(p.name == name for p in self.structure.ports):
                    self.structure.ports.append(Port(
                        name=name,
                        direction=direction,
                        width=width,
                        msb=msb,
                        lsb=lsb
                    ))
    
    def _parse_signals(self):
        """解析内部信号定义"""
        patterns = [
            r'(wire|reg|logic)\s+(?:\[(\d+):(\d+)\]\s+)?(\w+)\s*;',
            r'(wire|reg|logic)\s+\[(\d+):(\d+)\]\s+(\w+)\s*;',
        ]
        
        for pattern in patterns:
            for match in re.finditer(pattern, self.code):
                signal_type = match.group(1)
                msb = int(match.group(2)) if match.group(2) else 0
                lsb = int(match.group(3)) if match.group(3) else 0
                name = match.group(4)
                width = abs(msb - lsb) + 1
                
                if not any(s.name == name for s in self.structure.signals):
                    self.structure.signals.append(Signal(
                        name=name,
                        signal_type=signal_type,
                        width=width,
                        msb=msb,
                        lsb=lsb
                    ))
    
    def _parse_parameters(self):
        """解析参数定义"""
        # parameter 定义
        param_pattern = r'parameter\s+(?:\[(\d+):(\d+)\]\s+)?(\w+)\s*=\s*([^;]+)'
        for match in re.finditer(param_pattern, self.code):
            name = match.group(3)
            value = match.group(4).strip()
            self.structure.parameters.append(Parameter(
                name=name,
                value=value,
                param_type="parameter"
            ))
        
        # localparam 定义
        localparam_pattern = r'localparam\s+(?:\[(\d+):(\d+)\]\s+)?(\w+)\s*=\s*([^;]+)'
        for match in re.finditer(localparam_pattern, self.code):
            name = match.group(3)
            value = match.group(4).strip()
            self.structure.parameters.append(Parameter(
                name=name,
                value=value,
                param_type="localparam"
            ))
    
    def _parse_code_regions(self):
        """解析代码区域"""
        # always 块
        always_pattern = r'(always\s*@\s*\([^)]*\)\s*begin.*?end)'
        for i, match in enumerate(re.finditer(always_pattern, self.code, re.DOTALL)):
            start = self.code[:match.start()].count('\n') + 1
            end = self.code[:match.end()].count('\n') + 1
            self.structure.code_regions.append(CodeRegion(
                start_line=start,
                end_line=end,
                region_type="always",
                content=match.group(1)
            ))
        
        # assign 语句
        assign_pattern = r'(assign\s+\w+\s*=\s*[^;]+;)'
        for i, match in enumerate(re.finditer(assign_pattern, self.code)):
            start = self.code[:match.start()].count('\n') + 1
            end = start
            self.structure.code_regions.append(CodeRegion(
                start_line=start,
                end_line=end,
                region_type="assign",
                content=match.group(1)
            ))
    
    def _build_signal_dependencies(self):
        """构建信号依赖图"""
        # 分析 assign 语句中的依赖
        assign_pattern = r'assign\s+(\w+)\s*=\s*([^;]+);'
        for match in re.finditer(assign_pattern, self.code):
            target = match.group(1)
            source = match.group(2)
            # 提取源表达式中的信号名
            deps = re.findall(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\b', source)
            self.structure.signal_dependencies[target] = deps
        
        # 分析 always 块中的依赖
        always_pattern = r'always\s*@\s*\([^)]*\)\s*begin(.*?)end'
        for match in re.finditer(always_pattern, self.code, re.DOTALL):
            block = match.group(1)
            # 查找赋值语句
            assigns = re.findall(r'(\w+)\s*(?:<=|=)\s*([^;]+);', block)
            for target, source in assigns:
                deps = re.findall(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\b', source)
                if target not in self.structure.signal_dependencies:
                    self.structure.signal_dependencies[target] = []
                self.structure.signal_dependencies[target].extend(deps)
    
    def get_input_ports(self) -> List[str]:
        """获取输入端口名列表"""
        return [p.name for p in self.structure.ports if p.direction == 'input']
    
    def get_output_ports(self) -> List[str]:
        """获取输出端口名列表"""
        return [p.name for p in self.structure.ports if p.direction == 'output']


# ============================================================================
# 功能点识别器
# ============================================================================

class FunctionPointRecognizer:
    """
    功能点识别器
    自动识别RTL代码中的关键功能点
    """
    
    def __init__(self, rtl_code: str, structure: RTLStructure):
        """
        Args:
            rtl_code: RTL源代码
            structure: 已解析的结构信息
        """
        self.code = rtl_code
        self.structure = structure
        self.function_points: List[FunctionPoint] = []
        
    def recognize(self) -> List[FunctionPoint]:
        """执行完整识别"""
        self._recognize_fsm()
        self._recognize_counters()
        self._recognize_conditions()
        self._recognize_protocols()
        self._recognize_exceptions()
        return self.function_points
    
    def _recognize_fsm(self):
        """识别状态机"""
        # 查找状态参数定义
        state_params = []
        param_pattern = r'(?:parameter|localparam)\s+([^;]+);'
        for match in re.finditer(param_pattern, self.code):
            params_str = match.group(1)
            # 解析状态定义，如 WL=0, WR=1, ...
            state_defs = re.findall(r'([A-Z][A-Z0-9_]*)\s*=\s*(\d+)', params_str)
            if state_defs:
                state_params.extend([s[0] for s in state_defs])
        
        if not state_params:
            return
        
        # 查找 case 语句（状态转换逻辑）
        case_pattern = r'case\s*\(\s*(\w+)\s*\)(.*?)(?:endcase|$)'
        for match in re.finditer(case_pattern, self.code, re.DOTALL):
            state_var = match.group(1)
            case_body = match.group(2)
            
            # 提取状态转换信息
            transitions = self._extract_fsm_transitions(case_body, state_params)
            
            start_line = self.code[:match.start()].count('\n') + 1
            end_line = self.code[:match.end()].count('\n') + 1
            
            fp = FunctionPoint(
                name=f"FSM_{state_var}",
                fp_type=FunctionPointType.FSM,
                location=(start_line, end_line),
                code_region=match.group(0),
                attributes={
                    'state_variable': state_var,
                    'states': state_params,
                    'transitions': transitions
                }
            )
            self.function_points.append(fp)
    
    def _extract_fsm_transitions(self, case_body: str, states: List[str]) -> Dict[str, List[Dict]]:
        """提取 FSM 状态转换信息"""
        transitions = {}
        
        # 匹配每个状态分支
        branch_pattern = r'([A-Z][A-Z0-9_]*)\s*:(.*?)(?=[A-Z][A-Z0-9_]*\s*:|endcase|default:)'
        for match in re.finditer(branch_pattern, case_body, re.DOTALL):
            current_state = match.group(1)
            branch_code = match.group(2)
            
            if current_state not in states:
                continue
            
            transitions[current_state] = []
            
            # 提取条件转换
            cond_pattern = r'(?:if|else\s*if)\s*\(([^)]+)\)\s*(?:next\s*=?|state\s*<=)\s*(\w+)'
            for cond_match in re.finditer(cond_pattern, branch_code):
                condition = cond_match.group(1).strip()
                next_state = cond_match.group(2).strip()
                transitions[current_state].append({
                    'condition': condition,
                    'next_state': next_state
                })
            
            # 提取 default 转换
            default_pattern = r'else\s*(?:next\s*=?|state\s*<=)\s*(\w+)'
            default_match = re.search(default_pattern, branch_code)
            if default_match:
                transitions[current_state].append({
                    'condition': 'default',
                    'next_state': default_match.group(1)
                })
        
        return transitions
    
    def _recognize_counters(self):
        """识别计数器"""
        # 查找自增/自减操作
        counter_patterns = [
            r'(\w+)\s*<=\s*\1\s*\+\s*1',   # counter <= counter + 1
            r'(\w+)\s*<=\s*\1\s*-\s*1',   # counter <= counter - 1
            r'(\w+)\s*=\s*\1\s*\+\s*1',   # counter = counter + 1
            r'(\w+)\s*=\s*\1\s*-\s*1',    # counter = counter - 1
        ]
        
        counter_candidates = set()
        for pattern in counter_patterns:
            for match in re.finditer(pattern, self.code):
                counter_candidates.add(match.group(1))
        
        for counter_name in counter_candidates:
            # 查找计数器的边界条件
            boundary_pattern = rf'{counter_name}\s*(>=|<=|==|>|<)\s*(\d+)'
            boundaries = []
            for match in re.finditer(boundary_pattern, self.code):
                op = match.group(1)
                value = int(match.group(2))
                boundaries.append({'operator': op, 'value': value})
            
            # 查找计数器位宽
            width = 1
            for signal in self.structure.signals:
                if signal.name == counter_name:
                    width = signal.width
                    break
            
            # 查找计数器位置
            pattern = rf'{counter_name}\s*<='
            match = re.search(pattern, self.code)
            if match:
                start_line = self.code[:match.start()].count('\n') + 1
                end_line = start_line
            else:
                start_line, end_line = 0, 0
            
            fp = FunctionPoint(
                name=f"Counter_{counter_name}",
                fp_type=FunctionPointType.COUNTER,
                location=(start_line, end_line),
                code_region="",
                attributes={
                    'counter_name': counter_name,
                    'width': width,
                    'boundaries': boundaries
                }
            )
            self.function_points.append(fp)
    
    def _recognize_conditions(self):
        """识别条件分支"""
        # 查找 if-else 嵌套
        if_pattern = r'(if\s*\([^)]+\)(?:\s*begin)?(?:[^;]*?)(?:end)?(?:\s*else\s*(?:if\s*\([^)]+\))?(?:\s*begin)?(?:[^;]*?)(?:end)?)*)'
        
        # 简化：查找独立的 if 语句
        simple_if_pattern = r'if\s*\(([^)]+)\)'
        for i, match in enumerate(re.finditer(simple_if_pattern, self.code)):
            condition = match.group(1).strip()
            
            start_line = self.code[:match.start()].count('\n') + 1
            end_line = start_line
            
            # 分析条件中的边界值
            boundary_values = re.findall(r'(>=|<=|==|>|<)\s*(\d+)', condition)
            
            fp = FunctionPoint(
                name=f"Condition_{i+1}",
                fp_type=FunctionPointType.CONDITION,
                location=(start_line, end_line),
                code_region=match.group(0),
                attributes={
                    'condition': condition,
                    'boundary_values': boundary_values
                }
            )
            self.function_points.append(fp)
    
    def _recognize_protocols(self):
        """识别协议接口"""
        # 查找握手信号
        handshake_patterns = [
            (r'\b(valid|vld)\b', 'valid'),
            (r'\b(ready|rdy)\b', 'ready'),
            (r'\b(ack|acknowledge)\b', 'ack'),
        ]
        
        handshake_signals = {}
        for pattern, signal_type in handshake_patterns:
            for match in re.finditer(pattern, self.code, re.IGNORECASE):
                signal_name = match.group(1)
                if signal_type not in handshake_signals:
                    handshake_signals[signal_type] = []
                handshake_signals[signal_type].append(signal_name)
        
        if len(handshake_signals) >= 2:
            fp = FunctionPoint(
                name="Protocol_Handshake",
                fp_type=FunctionPointType.PROTOCOL,
                location=(0, 0),
                code_region="",
                attributes={
                    'protocol_type': 'handshake',
                    'signals': handshake_signals
                }
            )
            self.function_points.append(fp)
    
    def _recognize_exceptions(self):
        """识别异常处理"""
        # 查找 error 信号
        error_pattern = r'(?:output|wire)\s+(?:\[[\d:]+\]\s+)?(\w*error\w*)'
        for match in re.finditer(error_pattern, self.code, re.IGNORECASE):
            error_signal = match.group(1)
            fp = FunctionPoint(
                name=f"Exception_{error_signal}",
                fp_type=FunctionPointType.EXCEPTION,
                location=(0, 0),
                code_region="",
                attributes={
                    'error_signal': error_signal
                }
            )
            self.function_points.append(fp)
        
        # 查找 default 分支（case 语句的异常处理）
        default_pattern = r'default\s*:'
        if re.search(default_pattern, self.code):
            fp = FunctionPoint(
                name="Exception_DefaultCase",
                fp_type=FunctionPointType.EXCEPTION,
                location=(0, 0),
                code_region="",
                attributes={
                    'type': 'default_case'
                }
            )
            self.function_points.append(fp)


# ============================================================================
# 重要性评分器
# ============================================================================

class ImportanceScorer:
    """
    重要性评分器
    为每个功能点计算语义重要性评分
    """
    
    # 类型权重
    TYPE_WEIGHTS = {
        FunctionPointType.FSM: 0.30,
        FunctionPointType.COUNTER: 0.20,
        FunctionPointType.PROTOCOL: 0.20,
        FunctionPointType.CONDITION: 0.15,
        FunctionPointType.EXCEPTION: 0.15,
    }
    
    def __init__(self, function_points: List[FunctionPoint], structure: RTLStructure):
        """
        Args:
            function_points: 功能点列表
            structure: RTL结构信息
        """
        self.function_points = function_points
        self.structure = structure
    
    def score(self) -> List[FunctionPoint]:
        """计算所有功能点的重要性评分"""
        for fp in self.function_points:
            fp.importance_score = self._calculate_score(fp)
        
        # 按评分排序
        self.function_points.sort(key=lambda x: x.importance_score, reverse=True)
        return self.function_points
    
    def _calculate_score(self, fp: FunctionPoint) -> float:
        """计算单个功能点的评分"""
        # 基础类型权重
        base_score = self.TYPE_WEIGHTS.get(fp.fp_type, 0.10)
        
        # 边界条件得分
        boundary_score = self._get_boundary_score(fp)
        
        # 异常路径得分
        exception_score = self._get_exception_score(fp)
        
        # 依赖深度得分
        dependency_score = self._get_dependency_score(fp)
        
        # 复杂度得分
        complexity_score = self._get_complexity_score(fp)
        
        # 综合评分
        total_score = (
            base_score + 
            0.30 * boundary_score + 
            0.25 * exception_score + 
            0.20 * dependency_score + 
            0.25 * complexity_score
        )
        
        return min(1.0, total_score)  # 归一化到 [0, 1]
    
    def _get_boundary_score(self, fp: FunctionPoint) -> float:
        """获取边界条件得分"""
        if fp.fp_type == FunctionPointType.COUNTER:
            boundaries = fp.attributes.get('boundaries', [])
            if boundaries:
                # 有边界值的计数器更重要
                return min(1.0, len(boundaries) * 0.3)
        
        if fp.fp_type == FunctionPointType.CONDITION:
            boundary_values = fp.attributes.get('boundary_values', [])
            if boundary_values:
                return min(1.0, len(boundary_values) * 0.2)
        
        if fp.fp_type == FunctionPointType.FSM:
            states = fp.attributes.get('states', [])
            # 状态越多，边界条件越重要
            return min(1.0, len(states) * 0.1)
        
        return 0.0
    
    def _get_exception_score(self, fp: FunctionPoint) -> float:
        """获取异常路径得分"""
        if fp.fp_type == FunctionPointType.EXCEPTION:
            return 1.0
        
        if fp.fp_type == FunctionPointType.FSM:
            transitions = fp.attributes.get('transitions', {})
            # 检查是否有异常状态转换
            for state, trans_list in transitions.items():
                for trans in trans_list:
                    if 'error' in trans.get('next_state', '').lower():
                        return 0.5
        
        return 0.0
    
    def _get_dependency_score(self, fp: FunctionPoint) -> float:
        """获取依赖深度得分"""
        # 分析功能点在信号依赖图中的深度
        if fp.fp_type == FunctionPointType.FSM:
            state_var = fp.attributes.get('state_variable', '')
            if state_var in self.structure.signal_dependencies:
                depth = self._calculate_dependency_depth(state_var, set())
                return min(1.0, depth * 0.1)
        
        return 0.0
    
    def _calculate_dependency_depth(self, signal: str, visited: set) -> int:
        """递归计算依赖深度"""
        if signal in visited:
            return 0
        visited.add(signal)
        
        deps = self.structure.signal_dependencies.get(signal, [])
        if not deps:
            return 0
        
        max_depth = 0
        for dep in deps:
            depth = self._calculate_dependency_depth(dep, visited)
            max_depth = max(max_depth, depth)
        
        return max_depth + 1
    
    def _get_complexity_score(self, fp: FunctionPoint) -> float:
        """获取复杂度得分"""
        if fp.fp_type == FunctionPointType.FSM:
            transitions = fp.attributes.get('transitions', {})
            # 状态转换越多，复杂度越高
            total_transitions = sum(len(t) for t in transitions.values())
            return min(1.0, total_transitions * 0.05)
        
        if fp.fp_type == FunctionPointType.CONDITION:
            condition = fp.attributes.get('condition', '')
            # 条件越复杂（包含的逻辑运算符越多），复杂度越高
            operators = len(re.findall(r'(&&|\|\|)', condition))
            return min(1.0, operators * 0.2)
        
        return 0.0


# ============================================================================
# 测试场景生成器
# ============================================================================

class TestScenarioGenerator:
    """
    测试场景生成器
    基于识别的功能点生成测试场景建议
    """
    
    SCENARIO_TEMPLATES = {
        FunctionPointType.FSM: [
            ("state_transition", "测试所有状态转换路径"),
            ("illegal_transition", "测试非法状态转换"),
            ("state_loop", "测试状态循环"),
        ],
        FunctionPointType.COUNTER: [
            ("boundary_zero", "测试计数器归零"),
            ("boundary_max", "测试计数器最大值"),
            ("overflow", "测试计数器溢出"),
        ],
        FunctionPointType.CONDITION: [
            ("branch_path", "测试各分支路径"),
            ("boundary_condition", "测试边界条件"),
            ("combination", "测试组合条件"),
        ],
        FunctionPointType.PROTOCOL: [
            ("handshake_timing", "测试握手时序"),
            ("concurrent", "测试并发操作"),
            ("timeout", "测试协议超时"),
        ],
        FunctionPointType.EXCEPTION: [
            ("trigger", "测试异常触发"),
            ("recovery", "测试异常恢复"),
            ("fault_tolerance", "测试容错处理"),
        ],
    }
    
    def __init__(self, function_points: List[FunctionPoint]):
        """
        Args:
            function_points: 带评分的功能点列表
        """
        self.function_points = function_points
    
    def generate(self) -> List[TestScenario]:
        """生成测试场景建议"""
        scenarios = []
        
        for fp in self.function_points:
            templates = self.SCENARIO_TEMPLATES.get(fp.fp_type, [])
            for template_name, description in templates:
                # 根据重要性评分计算优先级
                priority = fp.importance_score
                
                # 生成具体的场景描述
                specific_desc = self._customize_description(fp, template_name, description)
                
                scenario = TestScenario(
                    name=f"{fp.name}_{template_name}",
                    target_function=fp.name,
                    description=specific_desc,
                    priority=priority,
                    scenario_type=template_name
                )
                scenarios.append(scenario)
        
        # 按优先级排序
        scenarios.sort(key=lambda x: x.priority, reverse=True)
        return scenarios
    
    def _customize_description(self, fp: FunctionPoint, template_name: str, base_desc: str) -> str:
        """根据功能点属性定制描述"""
        if fp.fp_type == FunctionPointType.FSM:
            states = fp.attributes.get('states', [])
            transitions = fp.attributes.get('transitions', {})
            
            if template_name == "state_transition":
                return f"测试 {fp.name} 的所有状态转换（共 {len(states)} 个状态，{sum(len(t) for t in transitions.values())} 个转换）"
            elif template_name == "illegal_transition":
                return f"测试 {fp.name} 的非法状态转换处理"
            elif template_name == "state_loop":
                return f"测试 {fp.name} 的状态循环场景"
        
        elif fp.fp_type == FunctionPointType.COUNTER:
            counter_name = fp.attributes.get('counter_name', '')
            boundaries = fp.attributes.get('boundaries', [])
            
            if template_name == "boundary_zero":
                return f"测试计数器 {counter_name} 归零场景"
            elif template_name == "boundary_max":
                max_boundary = next((b for b in boundaries if b['operator'] in ['>=', '>']), None)
                if max_boundary:
                    return f"测试计数器 {counter_name} 达到最大值 {max_boundary['value']}"
                return f"测试计数器 {counter_name} 最大值边界"
            elif template_name == "overflow":
                return f"测试计数器 {counter_name} 溢出场景"
        
        elif fp.fp_type == FunctionPointType.CONDITION:
            condition = fp.attributes.get('condition', '')
            
            if template_name == "branch_path":
                return f"测试条件分支: {condition}"
            elif template_name == "boundary_condition":
                boundary_values = fp.attributes.get('boundary_values', [])
                if boundary_values:
                    values_str = ', '.join([f"{b[0]}{b[1]}" for b in boundary_values])
                    return f"测试边界条件: {values_str}"
                return f"测试条件边界: {condition}"
        
        return base_desc


# ============================================================================
# 语义分析器 (主入口)
# ============================================================================

class SemanticAnalyzer:
    """
    语义分析器 - 第0层主入口
    整合所有子模块，提供统一的语义分析接口
    """
    
    def __init__(self, rtl_code: str):
        """
        Args:
            rtl_code: RTL源代码字符串
        """
        self.rtl_code = rtl_code
        self.structure: Optional[RTLStructure] = None
        self.function_points: List[FunctionPoint] = []
        self.test_scenarios: List[TestScenario] = []
    
    def analyze(self) -> Dict[str, Any]:
        """
        执行完整的语义分析
        
        Returns:
            包含所有分析结果的字典
        """
        # Step 1: 解析RTL结构
        parser = RTLStructureParser(self.rtl_code)
        self.structure = parser.parse()
        
        # Step 2: 识别功能点
        recognizer = FunctionPointRecognizer(self.rtl_code, self.structure)
        self.function_points = recognizer.recognize()
        
        # Step 3: 计算重要性评分
        scorer = ImportanceScorer(self.function_points, self.structure)
        self.function_points = scorer.score()
        
        # Step 4: 生成测试场景
        generator = TestScenarioGenerator(self.function_points)
        self.test_scenarios = generator.generate()
        
        return self.get_analysis_result()
    
    # def get_analysis_result(self) -> Dict[str, Any]:
    #     """获取分析结果"""
    #     return {
    #         'module_name': self.structure.module_name if self.structure else '',
    #         'inputs': self.structure.get_input_ports() if self.structure else [],
    #         'outputs': self.structure.get_output_ports() if self.structure else [],
    #         'function_points': [
    #             {
    #                 'name': fp.name,
    #                 'type': fp.fp_type.value,
    #                 'importance': fp.importance_score,
    #                 'covered': fp.covered,
    #                 'attributes': fp.attributes
    #             }
    #             for fp in self.function_points
    #         ],
    #         'test_scenarios': [
    #             {
    #                 'name': ts.name,
    #                 'target': ts.target_function,
    #                 'description': ts.description,
    #                 'priority': ts.priority
    #             }
    #             for ts in self.test_scenarios
    #         ]
    #     }
    
    def get_analysis_result(self) -> Dict[str, Any]:
        """获取分析结果"""
        # 从 structure.ports 中获取输入输出端口
        inputs = [p.name for p in self.structure.ports if p.direction == 'input'] if self.structure else []
        outputs = [p.name for p in self.structure.ports if p.direction == 'output'] if self.structure else []
        
        return {
            'module_name': self.structure.module_name if self.structure else '',
            'inputs': inputs,
            'outputs': outputs,
            'function_points': [
                {
                    'name': fp.name,
                    'type': fp.fp_type.value,
                    'importance': fp.importance_score,
                    'covered': fp.covered,
                    'attributes': fp.attributes
                }
                for fp in self.function_points
            ],
            'test_scenarios': [
                {
                    'name': ts.name,
                    'target': ts.target_function,
                    'description': ts.description,
                    'priority': ts.priority
                }
                for ts in self.test_scenarios
            ]
        }

    def get_function_points_by_type(self, fp_type: FunctionPointType) -> List[FunctionPoint]:
        """按类型获取功能点"""
        return [fp for fp in self.function_points if fp.fp_type == fp_type]
    
    def get_top_priority_scenarios(self, n: int = 5) -> List[TestScenario]:
        """获取优先级最高的N个测试场景"""
        return self.test_scenarios[:n]
    
    def get_fsm_info(self) -> Optional[Dict[str, Any]]:
        """获取FSM相关信息（如果有）"""
        fsm_fps = self.get_function_points_by_type(FunctionPointType.FSM)
        if fsm_fps:
            fp = fsm_fps[0]
            return {
                'name': fp.name,
                'state_variable': fp.attributes.get('state_variable', ''),
                'states': fp.attributes.get('states', []),
                'transitions': fp.attributes.get('transitions', {})
            }
        return None
    
    # def generate_prompt_context(self) -> str:
    #     """生成用于 Prompt 的上下文信息"""
    #     context = []
        
    #     # 端口信息
    #     if self.structure:
    #         context.append("[MODULE INFO]")
    #         context.append(f"Module: {self.structure.module_name}")
    #         # context.append(f"Inputs: {', '.join(self.structure.get_input_ports())}")
    #         context.append(f"inputs = [p.name for p in self.structure.ports if p.direction == 'input']")
    #         context.append(f"Outputs: {', '.join(self.structure.get_output_ports())}")
    #         context.append("")
        
    #     # 功能点信息
    #     if self.function_points:
    #         context.append("[FUNCTION POINTS - Ranked by Importance]")
    #         for i, fp in enumerate(self.function_points[:10]):  # Top 10
    #             context.append(f"{i+1}. {fp.name} ({fp.fp_type.value}): importance={fp.importance_score:.2f}")
    #         context.append("")
        
    #     # FSM 详细信息
    #     fsm_info = self.get_fsm_info()
    #     if fsm_info:
    #         context.append("[FSM DETAILS]")
    #         context.append(f"State Variable: {fsm_info['state_variable']}")
    #         context.append(f"States: {', '.join(fsm_info['states'])}")
    #         context.append("Transitions:")
    #         for state, trans_list in fsm_info['transitions'].items():
    #             for trans in trans_list:
    #                 context.append(f"  {state} --[{trans['condition']}]--> {trans['next_state']}")
    #         context.append("")
        
    #     # 测试场景建议
    #     if self.test_scenarios:
    #         context.append("[RECOMMENDED TEST SCENARIOS]")
    #         for i, ts in enumerate(self.test_scenarios[:5]):
    #             context.append(f"{i+1}. {ts.name}: {ts.description} (priority={ts.priority:.2f})")
        
    #     return "\n".join(context)


    def generate_prompt_context(self) -> str:
        """生成用于 Prompt 的上下文信息"""
        context = []
        
        # 端口信息
        if self.structure:
            inputs = [p.name for p in self.structure.ports if p.direction == 'input']
            outputs = [p.name for p in self.structure.ports if p.direction == 'output']
            context.append("[MODULE INFO]")
            context.append(f"Module: {self.structure.module_name}")
            context.append(f"Inputs: {', '.join(inputs)}")
            context.append(f"Outputs: {', '.join(outputs)}")
            context.append("")
        
        # 功能点信息
        if self.function_points:
            context.append("[FUNCTION POINTS - Ranked by Importance]")
            for i, fp in enumerate(self.function_points[:10]):  # Top 10
                context.append(f"{i+1}. {fp.name} ({fp.fp_type.value}): importance={fp.importance_score:.2f}")
            context.append("")
        
        # FSM 详细信息
        fsm_info = self.get_fsm_info()
        if fsm_info:
            context.append("[FSM DETAILS]")
            context.append(f"State Variable: {fsm_info['state_variable']}")
            context.append(f"States: {', '.join(fsm_info['states'])}")
            context.append("Transitions:")
            for state, trans_list in fsm_info['transitions'].items():
                for trans in trans_list:
                    context.append(f"  {state} --[{trans['condition']}]--> {trans['next_state']}")
            context.append("")
        
        # 测试场景建议
        if self.test_scenarios:
            context.append("[RECOMMENDED TEST SCENARIOS]")
            for i, ts in enumerate(self.test_scenarios[:5]):
                context.append(f"{i+1}. {ts.name}: {ts.description} (priority={ts.priority:.2f})")
        
        return "\n".join(context)

# ============================================================================
# 便捷函数
# ============================================================================

def analyze_rtl(rtl_code: str) -> Dict[str, Any]:
    """
    便捷函数：分析 RTL 代码
    
    Args:
        rtl_code: RTL源代码字符串
        
    Returns:
        分析结果字典
    """
    analyzer = SemanticAnalyzer(rtl_code)
    return analyzer.analyze()


def get_fsm_states(rtl_code: str) -> List[str]:
    """
    便捷函数：获取 FSM 状态列表
    
    Args:
        rtl_code: RTL源代码字符串
        
    Returns:
        状态名列表
    """
    analyzer = SemanticAnalyzer(rtl_code)
    analyzer.analyze()
    fsm_info = analyzer.get_fsm_info()
    return fsm_info['states'] if fsm_info else []
