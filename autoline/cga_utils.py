# #第四版

# """
# Description :   Utils for CGA (CoverageParser & TBInjector)
#                 - Features: Sticky Mode, Smart Noise Filtering (No assign/decls)
#                 - Enhanced: Three-layer protection for black-box constraints
#                   * Layer 1: Enhanced Prompt constraints (prevention)
#                   * Layer 2: Smart code transformation (conversion)
#                   * Layer 3: Quality assessment & retry (fallback)
#                 - Integrated: Diversity Constraint Injector (Layer 1)
# Author      :   CorrectBench Integration
# """
# import re
# import os
# import logging
# from typing import Tuple, List, Optional, Dict, TYPE_CHECKING

# # [新增] 导入多样性约束注入器
# if TYPE_CHECKING:
#     from autoline.diversity_injector import DiversityInjector

# # 配置日志
# logger = logging.getLogger(__name__)

# # ============================================================================
# # 三层防护策略说明
# # ============================================================================
# # Layer 1 - Prompt约束: 动态提取允许信号列表，明确约束，正反面示例
# # Layer 2 - 智能转换: 检测违规意图，尝试转换为合法形式
# # Layer 3 - 质量评估: 违规比例过高时返回质量分数，触发重新生成
# # ============================================================================


# # ============================================================================
# # 黑盒约束检查器 - 三层防护策略实现
# # ============================================================================
# class BlackBoxValidator:
#     """
#     黑盒约束验证器 - 三层防护策略
    
#     Layer 1: 增强Prompt约束（预防）
#         - 动态提取允许信号列表
#         - 生成明确的约束提示
    
#     Layer 2: 智能代码转换（转换）
#         - 检测违规意图
#         - 尝试转换为合法的等价形式
#         - 转换失败时才注释
    
#     Layer 3: 质量评估（重试）
#         - 计算代码质量分数
#         - 违规比例过高时建议重试
#     """
    
#     # 常见的内部信号命名模式（按严重程度分类）
#     INTERNAL_SIGNAL_PATTERNS = {
#         # 高风险：FSM状态相关（绝对不能修改）
#         'critical': [
#             (r'\bstate\b', 'FSM状态寄存器'),
#             (r'\bnext_state\b', 'FSM下一状态'),
#             (r'\bcurrent_state\b', 'FSM当前状态'),
#             (r'\bnext\b(?!\s*[,@])', '下一状态简写'),
#         ],
#         # 中风险：计数器和内部寄存器
#         'warning': [
#             (r'\bcounter\b', '内部计数器'),
#             (r'\bcount\b', '计数寄存器'),
#             (r'\bcnt\b', '计数简写'),
#             (r'\bfall_counter\b', '下落计数器'),
#             (r'\breg_\w+', '内部寄存器'),
#         ],
#         # 低风险：可疑信号（需要确认）
#         'info': [
#             (r'\binternal_\w+', '内部信号'),
#             (r'\btemp_\w+', '临时信号'),
#             (r'\bprev_\w+', '前一状态'),
#         ]
#     }
    
#     # 非法语句模式
#     FORBIDDEN_STATEMENTS = [
#         (r'\bforce\s+(\w+)', 'force语句', 'critical'),
#         (r'\bassign\s+(\w+)\s*=', '连续赋值', 'critical'),
#         (r'\bdeassign\s+', 'deassign语句', 'critical'),
#         (r'\brelease\s+', 'release语句', 'critical'),
#     ]
    
#     # 层次化访问模式（如 DUT.state）
#     HIERARCHICAL_ACCESS = r'(\w+)\s*\.\s*(\w+)'
    
#     def __init__(self, dut_inputs: List[str] = None, dut_outputs: List[str] = None):
#         """
#         Args:
#             dut_inputs: DUT模块的输入端口列表
#             dut_outputs: DUT模块的输出端口列表
#         """
#         self.dut_inputs = dut_inputs or []
#         self.dut_outputs = dut_outputs or []
#         self.violations = {'critical': [], 'warning': [], 'info': []}
#         self.transformations = []
        
#     def validate_and_transform(self, code: str, tb_code: str = None) -> Tuple[str, Dict]:
#         """验证并转换代码 - 主入口"""
#         self.violations = {'critical': [], 'warning': [], 'info': []}
#         self.transformations = []
        
#         if tb_code:
#             self._extract_signals_from_tb(tb_code)
        
#         original_lines = code.strip().split('\n')
#         total_lines = len([l for l in original_lines if l.strip() and not l.strip().startswith('//')])
        
#         # Step 1: 移除非法语句
#         code = self._transform_forbidden_statements(code)
        
#         # Step 2: 转换层次化访问
#         code = self._transform_hierarchical_access(code)
        
#         # Step 3: 智能转换内部信号访问
#         code = self._smart_transform_internal_signals(code)
        
#         # Step 4: 最后清理
#         code = self._final_cleanup(code)
        
#         # 计算质量分数
#         quality_score = self._calculate_quality_score(total_lines)
        
#         # 决定是否需要重试
#         should_retry = quality_score < 50 or len(self.violations['critical']) > 3
        
#         result = {
#             'quality_score': quality_score,
#             'is_valid': len(self.violations['critical']) == 0,
#             'violations': self.violations,
#             'transformations': self.transformations,
#             'should_retry': should_retry,
#             'allowed_signals': self._get_allowed_signals_info()
#         }
        
#         return code.strip(), result
    
#     def _extract_signals_from_tb(self, tb_code: str):
#         """从测试平台代码中提取DUT输入输出信号"""
#         dut_match = re.search(r'(\w+)\s+(?:DUT|dut|uut|UUT)\s*\(', tb_code, re.IGNORECASE)
#         if dut_match:
#             start = dut_match.start()
#             bracket_count = 0
#             end = start
#             for i, char in enumerate(tb_code[start:]):
#                 if char == '(':
#                     bracket_count += 1
#                 elif char == ')':
#                     bracket_count -= 1
#                     if bracket_count == 0:
#                         end = start + i + 1
#                         break
            
#             dut_instance = tb_code[start:end]
#             port_pattern = r'\.(\w+)\s*\(\s*(\w+)\s*\)'
            
#             for match in re.finditer(port_pattern, dut_instance):
#                 signal_name = match.group(2)
                
#                 is_input = re.search(rf'\breg\s+(?:\[[\d:]+\]\s*)?{re.escape(signal_name)}\s*[;,\n]', tb_code)
#                 is_output = re.search(rf'\bwire\s+(?:\[[\d:]+\]\s*)?{re.escape(signal_name)}\s*[;,\n]', tb_code)
                
#                 if is_input and signal_name not in self.dut_inputs:
#                     self.dut_inputs.append(signal_name)
#                 if is_output and signal_name not in self.dut_outputs:
#                     self.dut_outputs.append(signal_name)
        
#         # 备用方案：通过reg/wire声明推断
#         if not self.dut_inputs and not self.dut_outputs:
#             for match in re.finditer(r'\breg\s+(?:\[[\d:]+\]\s*)?(\w+)\s*[;,\n]', tb_code):
#                 signal = match.group(1)
#                 if signal.lower() not in ['file', 'scenario', 'i', 'j', 'k', 'cnt']:
#                     if signal not in self.dut_inputs:
#                         self.dut_inputs.append(signal)
            
#             for match in re.finditer(r'\bwire\s+(?:\[[\d:]+\]\s*)?(\w+)\s*[;,\n]', tb_code):
#                 signal = match.group(1)
#                 if signal not in self.dut_outputs:
#                     self.dut_outputs.append(signal)
    
#     def _transform_forbidden_statements(self, code: str) -> str:
#         """转换非法语句"""
#         for pattern, desc, severity in self.FORBIDDEN_STATEMENTS:
#             matches = list(re.finditer(pattern, code, re.IGNORECASE))
#             for match in reversed(matches):
#                 signal = match.group(1) if match.groups() else 'unknown'
#                 self.violations[severity].append(f"{desc}: {signal}")
                
#                 line_start = code.rfind('\n', 0, match.start()) + 1
#                 line_end = code.find('\n', match.end())
#                 if line_end == -1:
#                     line_end = len(code)
#                 original_line = code[line_start:line_end]
                
#                 # 尝试转换 force -> 直接赋值（仅对输入信号）
#                 if 'force' in match.group(0).lower() and signal in self.dut_inputs:
#                     new_line = re.sub(r'\bforce\s+', '', original_line, flags=re.IGNORECASE)
#                     code = code[:line_start] + new_line + code[line_end:]
#                     self.transformations.append({
#                         'type': 'force_to_assign',
#                         'original': original_line.strip(),
#                         'transformed': new_line.strip()
#                     })
#                     continue
                
#                 code = code[:line_start] + '// [BLOCKED] ' + original_line.lstrip() + code[line_end:]
#                 self.transformations.append({
#                     'type': 'blocked',
#                     'original': original_line.strip(),
#                     'reason': desc
#                 })
        
#         return code
    
#     def _transform_hierarchical_access(self, code: str) -> str:
#         """转换层次化访问（如 DUT.state）"""
#         for match in re.finditer(self.HIERARCHICAL_ACCESS, code):
#             prefix = match.group(1)
#             signal = match.group(2)
            
#             if prefix.upper() in ['DUT', 'UUT', 'TOP', 'TB']:
#                 if signal not in self.dut_outputs:
#                     self.violations['critical'].append(f"层次化访问内部信号: {prefix}.{signal}")
                    
#                     line_start = code.rfind('\n', 0, match.start()) + 1
#                     line_end = code.find('\n', match.end())
#                     if line_end == -1:
#                         line_end = len(code)
#                     original_line = code[line_start:line_end]
#                     code = code[:line_start] + '// [HIERARCHY] ' + original_line.lstrip() + code[line_end:]
        
#         return code
    
#     def _smart_transform_internal_signals(self, code: str) -> str:
#         """智能转换内部信号访问"""
#         lines = code.split('\n')
#         transformed_lines = []
        
#         for line in lines:
#             stripped = line.strip()
            
#             if stripped.startswith('//') or not stripped:
#                 transformed_lines.append(line)
#                 continue
            
#             if (stripped.startswith('#') or stripped.startswith('$') or 
#                 stripped.startswith('repeat(') or stripped.startswith('@(')):
#                 transformed_lines.append(line)
#                 continue
            
#             detected_signals = self._detect_internal_signals_in_line(stripped)
#             has_critical = detected_signals.get('critical', [])
#             has_warning = detected_signals.get('warning', [])
            
#             if not has_critical and not has_warning:
#                 transformed_lines.append(line)
#                 continue
            
#             context = self._analyze_signal_context(stripped, detected_signals)
            
#             if context['type'] == 'assignment':
#                 transformed_lines.append(f"// [INTERNAL_ASSIGN] Cannot modify internal signal")
#                 transformed_lines.append(f"// Original: {stripped}")
#                 self.violations['critical'].append(f"尝试修改内部信号: {context['signals']}")
#             elif context['type'] == 'condition':
#                 transformed = self._transform_condition(stripped, context)
#                 transformed_lines.append(transformed)
#                 self.transformations.append({
#                     'type': 'condition_transform',
#                     'original': stripped,
#                     'transformed': transformed
#                 })
#             elif context['type'] == 'wait_for_state':
#                 transformed = self._transform_state_wait(stripped, context)
#                 transformed_lines.append(transformed)
#                 self.transformations.append({
#                     'type': 'wait_transform',
#                     'original': stripped,
#                     'transformed': transformed
#                 })
#             else:
#                 if has_critical:
#                     transformed_lines.append(f"// [WARNING] Contains internal signal reference: {has_critical}")
#                     transformed_lines.append(f"// Original: {stripped}")
#                     for sig in has_critical:
#                         self.violations['warning'].append(f"可疑的内部信号访问: {sig}")
#                 else:
#                     transformed_lines.append(line)
        
#         return '\n'.join(transformed_lines)
    
#     def _detect_internal_signals_in_line(self, line: str) -> Dict[str, List[str]]:
#         """检测行中的内部信号"""
#         detected = {'critical': [], 'warning': [], 'info': []}
        
#         LEGAL_KEYWORDS = {
#             'repeat', 'posedge', 'negedge', 'begin', 'end', 'if', 'else', 
#             'while', 'for', 'case', 'default', 'always', 'initial', 
#             'assign', 'wire', 'reg', 'input', 'output', 'inout',
#             'parameter', 'localparam', 'integer', 'real', 'time',
#             'clk', 'clock', 'reset', 'rst', 'areset', 'rst_n',
#             'enable', 'ena', 'valid', 'ready', 'data', 'addr', 'address',
#             'true', 'false', 'idle', 'wait'
#         }
        
#         SYSTEM_FUNCTIONS = {'$display', '$write', '$monitor', '$fopen', '$fclose', 
#                            '$fdisplay', '$fwrite', '$readmemh', '$readmemb',
#                            '$finish', '$stop', '$random', '$time', '$stime'}
        
#         for severity, patterns in self.INTERNAL_SIGNAL_PATTERNS.items():
#             for pattern, name in patterns:
#                 matches = re.findall(pattern, line, re.IGNORECASE)
#                 if matches:
#                     for match in matches:
#                         if isinstance(match, tuple):
#                             match = match[0] if match[0] else match[1]
                        
#                         match_lower = match.lower() if match else ''
                        
#                         if match_lower in LEGAL_KEYWORDS:
#                             continue
#                         if match in SYSTEM_FUNCTIONS:
#                             continue
#                         if match in self.dut_inputs or match in self.dut_outputs:
#                             continue
#                         if match.startswith('$'):
#                             continue
                        
#                         if match and match not in detected[severity]:
#                             detected[severity].append(match)
        
#         return detected
    
#     def _analyze_signal_context(self, line: str, signals: Dict) -> Dict:
#         """分析信号使用上下文"""
#         assign_match = re.search(r'(\w+)\s*(?:=|<=)\s*', line)
#         if assign_match:
#             target = assign_match.group(1)
#             if target in signals.get('critical', []) or target in signals.get('warning', []):
#                 return {'type': 'assignment', 'signals': [target], 'line': line}
        
#         if re.search(r'wait\s*\([^)]*state', line, re.IGNORECASE):
#             return {'type': 'wait_for_state', 'signals': signals.get('critical', []), 'line': line}
        
#         if re.search(r'if\s*\(|while\s*\(|@\s*\(', line):
#             return {'type': 'condition', 'signals': signals.get('critical', []) + signals.get('warning', []), 'line': line}
        
#         return {'type': 'other', 'signals': signals.get('critical', []) + signals.get('warning', []), 'line': line}
    
#     def _transform_condition(self, line: str, context: Dict) -> str:
#         """转换条件判断语句"""
#         original = line
        
#         if 'state' in str(context['signals']):
#             indent = len(line) - len(line.lstrip())
#             spaces = ' ' * indent
            
#             transformed = f"// [TRANSFORMED] Original: {original.strip()}\n"
#             transformed += f"{spaces}// Cannot directly check internal state\n"
#             transformed += f"{spaces}// Alternative: Wait for expected clock cycles\n"
#             transformed += f"{spaces}repeat(5) @(posedge clk);  // Adjust cycles as needed"
            
#             self.violations['warning'].append(f"条件判断转换: {original.strip()}")
#             return transformed
        
#         return f"// [TRANSFORMED] {original}"
    
#     def _transform_state_wait(self, line: str, context: Dict) -> str:
#         """转换状态等待语句"""
#         indent = len(line) - len(line.lstrip())
#         spaces = ' ' * indent
        
#         transformed = f"// [TRANSFORMED] Original: {line.strip()}\n"
#         transformed += f"{spaces}// Cannot wait for internal state directly\n"
#         transformed += f"{spaces}// Alternative: Drive inputs and wait for expected cycles\n"
#         transformed += f"{spaces}repeat(10) @(posedge clk);  // Adjust based on FSM design"
        
#         self.violations['info'].append(f"状态等待转换: {line.strip()}")
#         return transformed
    
#     def _final_cleanup(self, code: str) -> str:
#         """最终清理"""
#         lines = code.split('\n')
#         cleaned = []
        
#         for line in lines:
#             stripped = line.strip()
            
#             if stripped in ['begin', 'end'] and cleaned:
#                 last = cleaned[-1].strip()
#                 if last.startswith('// [TRANSFORMED]') or last.startswith('// [INTERNAL'):
#                     continue
            
#             cleaned.append(line)
        
#         result = '\n'.join(cleaned)
#         result = re.sub(r'\n\s*\n\s*\n', '\n\n', result)
        
#         return result
    
#     def _calculate_quality_score(self, total_lines: int) -> int:
#         """计算代码质量分数"""
#         if total_lines == 0:
#             return 0
        
#         score = 100
#         score -= len(self.violations['critical']) * 20
#         score -= len(self.violations['warning']) * 5
#         score += len([t for t in self.transformations if 'blocked' not in t.get('type', '')]) * 5
        
#         return max(0, min(100, score))
    
#     def _get_allowed_signals_info(self) -> Dict:
#         """获取允许的信号信息"""
#         return {
#             'inputs': self.dut_inputs,
#             'outputs': self.dut_outputs,
#             'all_allowed': self.dut_inputs + self.dut_outputs
#         }
    
#     def generate_constraint_prompt(self) -> str:
#         """生成动态约束提示 - 使用实际信号名"""
#         prompt = "\n[SIGNAL CONSTRAINTS - DERIVED FROM YOUR DUT]\n"
        
#         # 提取复位信号名（优先使用实际的）
#         reset_signal = self._find_reset_signal()
        
#         if self.dut_inputs:
#             prompt += "ALLOWED INPUTS (you CAN drive these):\n"
#             for sig in self.dut_inputs:
#                 prompt += f"  - {sig}\n"
#         else:
#             prompt += "ALLOWED INPUTS: Check the testbench for actual signal names\n"
        
#         if self.dut_outputs:
#             prompt += "\nOUTPUTS (you can READ but NOT write):\n"
#             for sig in self.dut_outputs:
#                 prompt += f"  - {sig}\n"
        
#         prompt += f"""
# FORBIDDEN ACTIONS:
# 1. NEVER assign values to internal signals (state, counter, etc.)
# 2. NEVER use 'force' or 'assign' statements
# 3. NEVER access signals like DUT.state (hierarchical access)

# CORRECT APPROACH:
# - To reach a specific FSM state: drive inputs and WAIT for natural transition
# - Example: Instead of "state = IDLE", use "{reset_signal} = 1; repeat(2) @(posedge clk); {reset_signal} = 0;"
# """
#         return prompt
    
#     def _find_reset_signal(self) -> str:
#         """查找复位信号名"""
#         # 按优先级查找常见的复位信号名
#         reset_candidates = ['areset', 'rst_n', 'rst', 'reset', 'rst_b']
#         for sig in reset_candidates:
#             if sig in self.dut_inputs:
#                 return sig
#         # 如果没找到，检查输入列表中是否有类似名称
#         for sig in self.dut_inputs:
#             sig_lower = sig.lower()
#             if 'reset' in sig_lower or 'rst' in sig_lower:
#                 return sig
#         # 默认返回第一个输入信号（排除 clk）
#         for sig in self.dut_inputs:
#             if 'clk' not in sig.lower():
#                 return sig
#         return "reset"  # 兜底


# # ============================================================================
# # CoverageParser - 覆盖率解析器
# # ============================================================================
# class CoverageParser:
#     """覆盖率解析器 - 从带注释的Verilog文件中提取未覆盖的代码块
    
#     [增强] 集成语义分析结果，提供更精准的 FSM 状态路径指导
#     [新增] 集成能量分配层，提供目标功能点优先级信息
#     [新增] 集成多样性约束注入器，避免测试用例同质化
#     """
    
#     def __init__(self, annotated_file, tb_code=None, semantic_result=None, 
#                  energy_allocator=None, diversity_injector=None):
#         self.file_path = annotated_file
#         self.tb_code = tb_code
#         self.semantic_result = semantic_result  # [新增] 语义分析结果
#         self.energy_allocator = energy_allocator  # [新增] 能量分配器
#         self.diversity_injector = diversity_injector  # [新增] 多样性约束注入器
#         # 修复：Verilator 覆盖率标记格式为 %NNNNNN 或 ~NNNNNN 或 ^NNNNNN
#         # %NNNNNN - 行覆盖计数（%000000 表示从未执行）
#         # ~NNNNNN - 分支/条件覆盖计数
#         # ^NNNNNN - 未覆盖的分支
#         self.line_pattern = re.compile(r'^%(\d+)\s+(.*)$')  # 匹配 %NNNNNN code
#         self.tilde_pattern = re.compile(r'^~(\d+)\s+(.*)$')  # 匹配 ~NNNNNN code
#         self.caret_pattern = re.compile(r'^\^(\d+)\s+(.*)$')  # 匹配 ^NNNNNN code
#         # 有些情况可能是纯数字开头（无前缀）
#         self.plain_pattern = re.compile(r'^\s*(\d+)\s+(.*)$')
#         self.decl_pattern = re.compile(r'^\s*(input|output|inout|wire|reg|logic|parameter|localparam|assign)\b')
        
#         self.validator = BlackBoxValidator()
#         if tb_code:
#             self.validator._extract_signals_from_tb(tb_code)

#     def generate_prompt(self, current_score):
#         """生成覆盖率驱动的Prompt"""
#         if not os.path.exists(self.file_path):
#             return None

#         try:
#             with open(self.file_path, 'r', encoding='utf-8', errors='ignore') as f:
#                 lines = f.readlines()
#         except Exception:
#             return None

#         missing_blocks = []
#         current_block = []
#         recording = False
#         context_buffer = []
#         CONTEXT_SIZE = 3
        
#         # 收集缺失行用于 FSM 分析
#         missing_lines = []

#         for i, line in enumerate(lines):
#             line = line.strip()
#             count = -1
#             clean_code = line
#             is_tilde = False
#             is_caret = False

#             # 尝试匹配各种覆盖率标记格式
#             match_pct = self.line_pattern.match(line)      # %NNNNNN code
#             match_tilde = self.tilde_pattern.match(line)   # ~NNNNNN code
#             match_caret = self.caret_pattern.match(line)   # ^NNNNNN code
#             match_plain = self.plain_pattern.match(line)    # NNNNNN code (无前缀)

#             if match_pct:
#                 count = int(match_pct.group(1))
#                 clean_code = match_pct.group(2).strip()
#             elif match_tilde:
#                 count = int(match_tilde.group(1))
#                 clean_code = match_tilde.group(2).strip()
#                 is_tilde = True
#             elif match_caret:
#                 count = int(match_caret.group(1))
#                 clean_code = match_caret.group(2).strip()
#                 is_caret = True
#             elif match_plain:
#                 # 纯数字格式（可能出现在某些 Verilator 版本）
#                 count = int(match_plain.group(1))
#                 clean_code = match_plain.group(2).strip()

#             if "//" in clean_code:
#                 clean_code = clean_code.split("//")[0].strip()

#             is_hard_noise = (self.decl_pattern.match(clean_code) or clean_code == "endmodule")
#             is_soft_noise = (len(clean_code) < 2 or clean_code in ["end", "begin", "else", ");", "endcase", "default:"] or
#                            clean_code.startswith("module ") or not any(c.isalnum() for c in clean_code))

#             # 覆盖状态判断：
#             # - %NNNNNN: count > 0 表示已覆盖，count == 0 表示未覆盖
#             # - ~NNNNNN: 分支覆盖标记，需要进一步检查
#             # - ^NNNNNN: 未覆盖分支标记
#             is_definitely_covered = (not is_tilde and not is_caret and count > 0)
#             is_definitely_missed = (not is_tilde and not is_caret and count == 0 and not is_hard_noise and not is_soft_noise) or \
#                                    (is_caret and not is_hard_noise and not is_soft_noise)

#             if recording:
#                 if is_definitely_covered:
#                     missing_blocks.append(current_block)
#                     missing_lines.extend(current_block)
#                     current_block = []
#                     recording = False
#                     if not is_hard_noise:
#                         context_buffer.append(clean_code)
#                 else:
#                     if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
#                         current_block.append(f"Line {i+1}: {clean_code}")
#             else:
#                 if is_definitely_missed:
#                     recording = True
#                     if context_buffer:
#                         current_block.append(f"... (Context)")
#                         for ctx in context_buffer:
#                             current_block.append(f"   {ctx}")
#                     current_block.append(f"Line {i+1}: {clean_code}  <--- MISSING START")
#                 else:
#                     if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
#                         context_buffer.append(clean_code)
#                         if len(context_buffer) > CONTEXT_SIZE:
#                             context_buffer.pop(0)

#         if recording and current_block:
#             missing_blocks.append(current_block)
#             missing_lines.extend(current_block)
#         if not missing_blocks:
#             return None

#         selected_blocks = missing_blocks[:50]

#         # 获取实际信号名用于示例
#         reset_signal = self.validator._find_reset_signal()
#         inputs_no_clk = [s for s in self.validator.dut_inputs if 'clk' not in s.lower()]
#         example_signal = inputs_no_clk[0] if inputs_no_clk else (reset_signal if reset_signal != "reset" else "ena")
        
#         # 分析 FSM 相关的缺失代码
#         fsm_analysis = self._analyze_fsm_missing(missing_lines)
        
#         # [新增] 从语义分析结果获取 FSM 和功能点信息
#         semantic_context = self._generate_semantic_context()

#         prompt = f"""
# [ROLE]
# You are a hardware verification expert. Your task is to write a test scenario to improve code coverage.

# [COVERAGE STATUS]
# Current testbench achieves {current_score:.2f}% coverage.
# The following logic blocks in the DUT are NEVER executed during simulation:

# """
#         for idx, block in enumerate(selected_blocks):
#             prompt += f"--- Missing Logic Block {idx+1} ---\n" + "\n".join(block) + "\n\n"
        
#         # [新增] 添加语义分析上下文
#         if semantic_context:
#             prompt += f"""
# [SEMANTIC ANALYSIS - MODULE UNDERSTANDING]
# {semantic_context}
# """
        
#         # === [新增] 添加能量分配目标上下文 ===
#         if self.energy_allocator:
#             energy_context = self.energy_allocator.get_target_context()
#             if energy_context:
#                 prompt += f"""
# [ENERGY-ALIGNED TARGET - PRIORITY]
# {energy_context}
# Focus your test scenario on covering this high-priority target first.
# """
#         # =====================================

#         prompt += self.validator.generate_constraint_prompt()
        
#         # 添加 FSM 分析提示
#         if fsm_analysis:
#             prompt += f"""
# [FSM STATE TRANSITION ANALYSIS - CRITICAL]
# {fsm_analysis}

# IMPORTANT: FSM transitions have PRIORITY ORDER!
# - 'if' conditions are evaluated TOP to BOTTOM
# - The FIRST matching condition determines the next state
# - To trigger a branch like "else if (condition)", you MUST ensure all higher-priority conditions are FALSE
# - Read the missing code's context carefully: what conditions precede it?

# """

#         prompt += f"""
# [OUTPUT REQUIREMENTS - CRITICAL]
# 1. Return ONLY Verilog test scenario code (NOT a task definition)
# 2. Your code will be inserted INTO an existing `initial begin ... end` block
# 3. DO NOT wrap your code in `task ... endtask` - just write the test sequence directly
# 4. DO NOT use `$finish` or `$stop` - the testbench handles simulation end

# [CODING STYLE]
# 1. Use blocking assignments for input signals: `signal = value;`
# 2. Use `#N;` for time delays: `#10;` means wait 10 time units
# 3. Use `repeat(N) @(posedge clk);` to wait for N clock cycles
# 4. Start with reset sequence if needed

# [BLACK-BOX CONSTRAINTS - CRITICAL]
# 1. You can ONLY control module INPUTS listed above
# 2. You CANNOT access internal signals (state, next_state, counters, etc.)
# 3. You CANNOT use `force` or `assign` on internal signals
# 4. To trigger a specific state: drive inputs and wait for the FSM to reach it naturally

# [STEP-BY-STEP APPROACH - REQUIRED]
# For each missing branch, think through:
# 1. What STATE must the FSM be in? (Look at the case statement)
# 2. What CONDITIONS must be true/false? (Check priority order!)
# 3. How to reach that state from reset? (Trace state transitions)
# 4. What inputs to apply and in what order?

# [POSITIVE EXAMPLE - CORRECT APPROACH]
# ```verilog
# // Reset sequence - use ACTUAL input signal names from above
# {reset_signal} = 1;
# repeat(2) @(posedge clk);
# {reset_signal} = 0;

# // Wait for FSM to reach desired state (estimate cycles)
# repeat(3) @(posedge clk);

# // Trigger missing branch by driving inputs
# {example_signal} = 1;
# repeat(5) @(posedge clk);
# {example_signal} = 0;
# repeat(10) @(posedge clk);
# ```

# [NEGATIVE EXAMPLE - DO NOT DO THIS]
# ```verilog
# // WRONG: Using wrong signal name (e.g., 'reset' instead of '{reset_signal}')
# reset = 1;  // ERROR: Signal 'reset' does not exist! Use '{reset_signal}' instead!

# // WRONG: Not considering condition priority in FSM
# // If missing code is "else if (condition_b)", you must make condition_a FALSE first!
# // Example: if FSM has "if (!signal_a) ... else if (signal_b) ..."
# // Then signal_a must be 1 (FALSE) for the else-if branch to execute
# signal_a = 0;  // WRONG: This blocks the else-if branch!
# signal_b = 1;  // This will NOT trigger because signal_a=0 took priority

# // CORRECT: Analyze priority, set higher-priority conditions to FALSE
# signal_a = 1;  // Now the first condition (!signal_a) is FALSE
# signal_b = 1;  // Now this else-if branch can execute

# // WRONG: Trying to assign internal state
# state = IDLE;  // ERROR: Cannot modify internal signal!

# // WRONG: Using force on internal signal
# force DUT.state = WL;  // ERROR: Cannot force internal signal!

# // WRONG: Checking internal state in condition
# if (state == WL) begin  // ERROR: Cannot read internal signal!
#     {example_signal} = 1;
# end

# // CORRECT ALTERNATIVE: Estimate timing instead
# repeat(5) @(posedge clk);  // Wait for FSM to reach expected state
# {example_signal} = 1;
# ```

# [SIGNAL NAME WARNING - CRITICAL]
# - DO NOT use 'reset' if the actual signal is '{reset_signal}'
# - DO NOT use 'rst' if the actual signal is '{reset_signal}'
# - ALWAYS use EXACT signal names from the ALLOWED INPUTS list above
# - Double-check every signal name before using it!

# Now write the test scenario code to cover the missing blocks:
# """
        
#         # === [新增] 注入多样性约束 ===
#         if self.diversity_injector:
#             # 获取未覆盖功能点
#             uncovered_functions = []
#             if self.semantic_result and self.semantic_result.get('function_points'):
#                 uncovered_functions = [
#                     fp for fp in self.semantic_result['function_points'] 
#                     if not fp.get('covered', False)
#                 ]
            
#             # 获取当前目标功能点
#             target_function = ""
#             if self.energy_allocator and self.energy_allocator.current_target:
#                 target_function = self.energy_allocator.current_target.function_point
            
#             # 注入多样性约束
#             prompt = self.diversity_injector.inject_diversity_constraints(
#                 prompt=prompt,
#                 target_function=target_function,
#                 uncovered_functions=uncovered_functions
#             )
#         # =================================
        
#         return prompt
    
#     def _analyze_fsm_missing(self, missing_lines: List[str]) -> str:
#         """分析 FSM 相关的缺失代码，生成具体的 FSM 状态转换指导"""
#         analysis = []
        
#         # 检查是否涉及 FSM 状态转换
#         has_state_case = any('case' in line.lower() and 'state' in line.lower() for line in missing_lines)
#         has_else_if = any('else if' in line.lower() for line in missing_lines)
#         has_if_condition = any(re.search(r'\bif\s*\(', line) for line in missing_lines)
        
#         if has_state_case or has_else_if:
#             analysis.append("- Missing code involves FSM state transitions or conditional branches")
        
#         if has_else_if or has_if_condition:
#             analysis.append("- Conditional branches have PRIORITY ORDER (top to bottom)")
#             analysis.append("- 'else if' branches require ALL previous conditions to be FALSE")
#             analysis.append("- Analyze the missing code's context: what conditions block this branch?")
        
#         if has_state_case:
#             analysis.append("- To trigger a state transition: first reach the source state, then drive inputs")
        
#         # === 新增：FSM 状态路径分析 ===
#         # 尝试从缺失代码中提取 FSM 状态信息
#         fsm_state_info = self._extract_fsm_state_from_missing(missing_lines)
#         if fsm_state_info:
#             analysis.append("")
#             analysis.append("[FSM STATE PATH ANALYSIS]")
#             analysis.extend(fsm_state_info)
        
#         return "\n".join(analysis) if analysis else ""
    
#     def _extract_fsm_state_from_missing(self, missing_lines: List[str]) -> List[str]:
#         """
#         从缺失代码中提取 FSM 状态信息，生成具体的状态转换指导
        
#         分析策略：
#         1. 从缺失代码的上下文识别 case 分支（FSM 状态）
#         2. 分析该状态下的条件分支优先级
#         3. 识别需要满足的输入条件
#         """
#         info = []
        
#         # 从 annotated 文件中读取完整的 DUT 代码以分析 FSM 结构
#         try:
#             with open(self.file_path, 'r', encoding='utf-8', errors='ignore') as f:
#                 full_content = f.read()
#         except:
#             return info
        
#         # 提取缺失代码所在的 FSM 状态
#         target_state = None
#         missing_condition = None
        
#         for line in missing_lines:
#             # 查找 case 分支标记（如 "WL:", "WR:", "FALLL:" 等）
#             # 格式可能是 "Line N: STATE:" 或 "STATE:"
#             state_match = re.search(r'\b([A-Z][A-Z0-9_]*)\s*:', line)
#             if state_match:
#                 potential_state = state_match.group(1)
#                 # 排除常见的非状态关键字
#                 if potential_state not in ['IF', 'ELSE', 'CASE', 'BEGIN', 'END', 'DEFAULT']:
#                     target_state = potential_state
#                     break
        
#         # 如果没找到，尝试从整个文件中分析
#         if not target_state:
#             # 查找缺失行附近的 case 分支
#             lines = full_content.split('\n')
#             for i, line in enumerate(lines):
#                 # 查找覆盖率标记为 0 的行
#                 if re.match(r'^%000000', line.strip()):
#                     # 向上查找最近的 case 分支（状态）
#                     for j in range(i-1, max(0, i-20), -1):
#                         state_match = re.search(r'^\s*([A-Z][A-Z0-9_]*)\s*:', lines[j])
#                         if state_match:
#                             target_state = state_match.group(1)
#                             break
#                     if target_state:
#                         break
        
#         # 分析缺失的条件分支
#         for line in missing_lines:
#             # 提取 else if 条件
#             else_if_match = re.search(r'else\s+if\s*\(([^)]+)\)', line)
#             if else_if_match:
#                 missing_condition = else_if_match.group(1)
#                 break
#             # 提取 if 条件
#             if_match = re.search(r'\bif\s*\(([^)]+)\)', line)
#             if if_match:
#                 missing_condition = if_match.group(1)
#                 break
        
#         # 生成具体的指导信息
#         if target_state:
#             info.append(f"- Target FSM state identified: {target_state}")
            
#             # 查找复位后的初始状态
#             reset_state = self._find_reset_state(full_content)
#             if reset_state:
#                 info.append(f"- After reset, FSM starts in state: {reset_state}")
                
#                 if reset_state != target_state:
#                     info.append(f"- CRITICAL: You must FIRST transition from {reset_state} to {target_state}!")
#                     info.append(f"- Do NOT assume FSM will automatically reach {target_state}!")
                    
#                     # 尝试找到状态转换路径
#                     transition_hint = self._find_state_transition_hint(full_content, reset_state, target_state)
#                     if transition_hint:
#                         info.append(f"- To reach {target_state}: {transition_hint}")
        
#         if missing_condition:
#             info.append(f"- Missing condition: \"{missing_condition}\"")
#             # 分析条件优先级
#             priority_info = self._analyze_condition_priority(full_content, target_state, missing_condition)
#             if priority_info:
#                 info.extend(priority_info)
        
#         return info
    
#     def _find_reset_state(self, content: str) -> Optional[str]:
#         """从 DUT 代码中找到复位后的初始状态"""
#         # 查找复位逻辑中的状态赋值
#         # 常见模式: if (reset) state <= IDLE; 或 state <= 0;
#         patterns = [
#             r'if\s*\([^)]*reset[^)]*\)\s*state\s*<=\s*([A-Z][A-Z0-9_]*);',
#             r'if\s*\([^)]*reset[^)]*\)\s*state\s*<=\s*(\d+);',
#             r'if\s*\([^)]*rst[^)]*\)\s*state\s*<=\s*([A-Z][A-Z0-9_]*);',
#         ]
        
#         for pattern in patterns:
#             match = re.search(pattern, content, re.IGNORECASE)
#             if match:
#                 state = match.group(1)
#                 # 如果是数字，尝试从参数中找对应的状态名
#                 if state.isdigit():
#                     # 查找参数定义
#                     param_match = re.search(r'parameter\s+([^;]+);', content)
#                     if param_match:
#                         params = param_match.group(1)
#                         # 解析参数列表
#                         for param in params.split(','):
#                             param = param.strip()
#                             if '=' in param:
#                                 name, value = param.split('=')
#                                 if value.strip() == state:
#                                     return name.strip()
#                 return state
        
#         return None
    
#     def _find_state_transition_hint(self, content: str, from_state: str, to_state: str) -> Optional[str]:
#         """找到从一个状态到另一个状态的转换条件"""
#         # 在 case 语句中查找 from_state 分支
#         # 提取该分支下到 to_state 的转换条件
        
#         # 简单策略：查找 "next = TO_STATE" 或 "next <= TO_STATE"
#         pattern = rf'{from_state}\s*:.*?next\s*=?\s*{to_state}'
#         match = re.search(pattern, content, re.DOTALL)
        
#         if match:
#             # 提取条件
#             branch_code = match.group(0)
#             # 查找 if 条件
#             if_match = re.search(r'if\s*\(([^)]+)\)\s*next\s*=?\s*' + to_state, branch_code)
#             if if_match:
#                 return f"set condition: {if_match.group(1)}"
            
#             # 查找 else if 条件
#             elif_match = re.search(r'else\s+if\s*\(([^)]+)\)\s*next\s*=?\s*' + to_state, branch_code)
#             if elif_match:
#                 return f"set condition: {elif_match.group(1)} (ensure earlier conditions are FALSE)"
        
#         # 尝试反向查找：什么条件下会转换到目标状态
#         trans_pattern = rf'(?:if|else\s+if)\s*\(([^)]+)\)\s*(?:next\s*=?\s*{to_state}|{to_state}\s*;)'
#         trans_match = re.search(trans_pattern, content)
#         if trans_match:
#             return f"set condition: {trans_match.group(1)}"
        
#         return None
    
#     def _analyze_condition_priority(self, content: str, state: str, missing_condition: str) -> List[str]:
#         """分析条件分支的优先级，找出需要排除的条件"""
#         info = []
        
#         if not state:
#             return info
        
#         # 查找该状态下的所有条件分支
#         # 提取 state: 后面的代码块
#         state_block_pattern = rf'{state}\s*:(.*?)(?=[A-Z][A-Z0-9_]*\s*:|endcase|default:)'
#         match = re.search(state_block_pattern, content, re.DOTALL)
        
#         if not match:
#             return info
        
#         state_block = match.group(1)
        
#         # 提取所有条件分支
#         conditions = []
#         for cond_match in re.finditer(r'(?:if|else\s+if)\s*\(([^)]+)\)', state_block):
#             conditions.append(cond_match.group(1).strip())
        
#         # 找到缺失条件在列表中的位置
#         missing_idx = -1
#         for i, cond in enumerate(conditions):
#             # 简化比较（去除空格）
#             if cond.replace(' ', '') in missing_condition.replace(' ', '') or \
#                missing_condition.replace(' ', '') in cond.replace(' ', ''):
#                 missing_idx = i
#                 break
        
#         if missing_idx > 0:
#             info.append(f"- This branch is condition #{missing_idx + 1} (lower priority)")
#             info.append(f"- You must make ALL earlier conditions FALSE:")
#             for i in range(missing_idx):
#                 cond = conditions[i]
#                 # 分析如何使条件为 FALSE
#                 false_hint = self._get_false_hint(cond)
#                 info.append(f"  * \"{cond}\" must be FALSE → {false_hint}")
        
#         return info
    
#     def _get_false_hint(self, condition: str) -> str:
#         """分析如何使条件为 FALSE"""
#         condition = condition.strip()
        
#         # 处理 !signal 形式
#         if condition.startswith('!'):
#             signal = condition[1:].strip()
#             return f"set {signal} = 1"
        
#         # 处理 signal 形式（布尔值）
#         if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', condition):
#             return f"set {condition} = 0"
        
#         # 处理比较运算符
#         if '==' in condition:
#             parts = condition.split('==')
#             if len(parts) == 2:
#                 signal = parts[0].strip()
#                 value = parts[1].strip()
#                 if value.isdigit():
#                     return f"set {signal} != {value}"
        
#         # 处理 >= 形式
#         if '>=' in condition:
#             parts = condition.split('>=')
#             if len(parts) == 2:
#                 signal = parts[0].strip()
#                 value = parts[1].strip()
#                 if value.isdigit():
#                     return f"set {signal} < {value}"
        
#         # 处理 > 形式
#         if '>' in condition and '>=' not in condition:
#             parts = condition.split('>')
#             if len(parts) == 2:
#                 signal = parts[0].strip()
#                 value = parts[1].strip()
#                 return f"set {signal} <= {value}"
        
#         return "analyze the condition logic"
    
#     def _generate_semantic_context(self) -> str:
#         """
#         [新增] 从语义分析结果生成 Prompt 上下文
        
#         整合语义分析层 (Layer 0) 的输出，为 LLM 提供更精准的指导：
#         - FSM 状态转换图
#         - 功能点重要性排序
#         - 测试场景建议
        
#         Returns:
#             语义上下文字符串，用于增强 Prompt
#         """
#         if not self.semantic_result:
#             return ""
        
#         context_parts = []
        
#         # 1. 模块基础信息
#         module_name = self.semantic_result.get('module_name', '')
#         inputs = self.semantic_result.get('inputs', [])
#         outputs = self.semantic_result.get('outputs', [])
        
#         if module_name:
#             context_parts.append(f"Module Name: {module_name}")
#         if inputs:
#             context_parts.append(f"Module Inputs: {', '.join(inputs)}")
#         if outputs:
#             context_parts.append(f"Module Outputs: {', '.join(outputs)}")
        
#         # 2. FSM 信息（最关键）
#         fsm_info = self.semantic_result.get('fsm_info')
#         if fsm_info:
#             context_parts.append("")
#             context_parts.append("=== FSM STATE MACHINE DETAILS ===")
#             context_parts.append(f"State Variable: {fsm_info.get('state_variable', 'unknown')}")
            
#             states = fsm_info.get('states', [])
#             if states:
#                 context_parts.append(f"All States ({len(states)}): {', '.join(states)}")
            
#             # 状态转换表
#             transitions = fsm_info.get('transitions', {})
#             if transitions:
#                 context_parts.append("")
#                 context_parts.append("=== STATE TRANSITION TABLE ===")
#                 context_parts.append("Format: CURRENT_STATE --[CONDITION]--> NEXT_STATE")
#                 context_parts.append("")
                
#                 for state, trans_list in transitions.items():
#                     for trans in trans_list:
#                         condition = trans.get('condition', 'default')
#                         next_state = trans.get('next_state', 'unknown')
#                         if condition == 'default':
#                             context_parts.append(f"  {state} --[default]--> {next_state}")
#                         else:
#                             context_parts.append(f"  {state} --[if ({condition})]--> {next_state}")
                
#                 # 添加状态转换路径分析
#                 context_parts.append("")
#                 context_parts.append("=== STATE TRANSITION PATH HINTS ===")
#                 reset_state = self._find_reset_state_from_fsm(fsm_info)
#                 if reset_state:
#                     context_parts.append(f"Initial State (after reset): {reset_state}")
#                     context_parts.append("")
#                     context_parts.append("IMPORTANT: To reach a target state, trace the path from reset:")
#                     context_parts.append("  1. Reset the DUT to initialize to the starting state")
#                     context_parts.append("  2. Apply inputs to trigger state transitions")
#                     context_parts.append("  3. Wait for the FSM to naturally reach the target state")
#                     context_parts.append("  4. THEN apply inputs to trigger the missing branch")
        
#         # 3. 功能点优先级
#         function_points = self.semantic_result.get('function_points', [])
#         if function_points:
#             context_parts.append("")
#             context_parts.append("=== FUNCTION POINTS (Ranked by Importance) ===")
            
#             for i, fp in enumerate(function_points[:10]):  # Top 10
#                 name = fp.get('name', 'unknown')
#                 fp_type = fp.get('type', 'unknown')
#                 importance = fp.get('importance', 0)
#                 covered = fp.get('covered', False)
#                 status = "✓ COVERED" if covered else "✗ NOT COVERED"
#                 context_parts.append(f"  {i+1}. [{status}] {name} ({fp_type}): importance={importance:.2f}")
        
#         # 4. 测试场景建议
#         test_scenarios = self.semantic_result.get('test_scenarios', [])
#         if test_scenarios:
#             context_parts.append("")
#             context_parts.append("=== RECOMMENDED TEST SCENARIOS ===")
            
#             for i, ts in enumerate(test_scenarios[:5]):  # Top 5
#                 name = ts.get('name', 'unknown')
#                 description = ts.get('description', '')
#                 priority = ts.get('priority', 0)
#                 context_parts.append(f"  {i+1}. {name}: {description} (priority={priority:.2f})")
        
#         if context_parts:
#             return "\n".join(context_parts)
#         return ""
    
#     def _find_reset_state_from_fsm(self, fsm_info: dict) -> Optional[str]:
#         """从 FSM 信息中推断复位后的初始状态"""
#         # 方法1：检查是否有明确的复位状态
#         transitions = fsm_info.get('transitions', {})
        
#         # 复位后通常进入第一个定义的状态或特定名称的状态
#         states = fsm_info.get('states', [])
        
#         # 常见的初始状态命名
#         initial_state_names = ['IDLE', 'INIT', 'RESET', 'START', 'BEGIN']
        
#         for name in initial_state_names:
#             if name in states:
#                 return name
        
#         # 如果没有找到，返回第一个状态
#         if states:
#             return states[0]
        
#         return None


# # ============================================================================
# # TBInjector - 场景注入器
# # ============================================================================
# class TBInjector:
#     """
#     场景注入器 - 将LLM生成的测试代码注入到现有测试平台
    
#     集成三层防护策略：
#     1. Layer 1: Prompt约束（由CoverageParser处理）
#     2. Layer 2: 智能代码转换
#     3. Layer 3: 质量评估和重试建议
#     """
    
#     def __init__(self, tb_code):
#         """
#         初始化注入器
        
#         Args:
#             tb_code: 原始测试平台代码字符串
#         """
#         self.content = tb_code
#         self.validator = BlackBoxValidator()
#         self.validator._extract_signals_from_tb(tb_code)
#         self.last_validation_result = None

#     def inject(self, new_code, iter_idx):
#         """
#         注入新的测试场景到测试平台
        
#         Args:
#             new_code: LLM生成的测试代码
#             iter_idx: 迭代序号
            
#         Returns:
#             修改后的测试平台代码
#         """
#         # Step 1: 预处理代码（包含三层防护）
#         scenario_code, result = self._preprocess_code(new_code, iter_idx)
        
#         self.last_validation_result = result
        
#         # 记录日志
#         if result['violations']['critical']:
#             logger.warning(f"[CGA-{iter_idx}] Critical violations detected:")
#             for v in result['violations']['critical']:
#                 logger.warning(f"  - {v}")
        
#         if result['violations']['warning']:
#             logger.info(f"[CGA-{iter_idx}] Warnings:")
#             for v in result['violations']['warning']:
#                 logger.info(f"  - {v}")
        
#         if result['transformations']:
#             logger.info(f"[CGA-{iter_idx}] Code transformations applied:")
#             for t in result['transformations']:
#                 logger.info(f"  - {t['type']}: {t.get('original', 'N/A')[:50]}...")
        
#         # Step 2: 构建场景块
#         scenario_block = self._build_scenario_block(scenario_code, iter_idx)
        
#         # Step 3: 注入到TB中
#         modified_tb = self._inject_scenario(scenario_block)
        
#         return modified_tb

#     def should_retry(self):
#         """是否应该重试"""
#         if self.last_validation_result is None:
#             return False
#         return self.last_validation_result.get('should_retry', False)

#     def get_quality_score(self):
#         """获取代码质量分数"""
#         if self.last_validation_result is None:
#             return 0
#         return self.last_validation_result.get('quality_score', 0)

#     def _preprocess_code(self, code, iter_idx):
#         """预处理LLM生成的代码"""
#         # 移除markdown标记
#         code = re.sub(r'```(?:verilog|systemverilog|sv)?\n?', '', code)
#         code = re.sub(r'```', '', code)
        
#         # 移除task包装
#         code = re.sub(r'task\s+\w+\s*(?:\([^)]*\))?\s*;', '', code)
#         code = re.sub(r'endtask', '', code)
        
#         # 移除$finish和$stop
#         code = re.sub(r'\$finish\s*;', '', code)
#         code = re.sub(r'\$stop\s*;', '', code)
        
#         # 移除多余空行
#         code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)
        
#         initial_pattern = re.compile(r'\binitial\s+begin\b.*?\bend\b', re.DOTALL | re.IGNORECASE)
#         # 检查并移除 initial begin ... end 块
#         initial_match = initial_pattern.search(code)
#         if initial_match:
#             logger.warning(f"[CGA-{iter_idx}] Detected 'initial begin...end' block in generated code - this should not be included")
#             logger.warning(f"[CGA-{iter_idx}] Removing 'initial begin...end' wrapper, keeping only the test content")
#             # 提取块内的内容
#             block_content = initial_match.group(0)
#             # 移除 initial begin 和 end 包装
#             # 保留块内的实际测试代码
#             inner_content = re.sub(r'^\s*initial\s+begin\s*', '', block_content)
#             inner_content = re.sub(r'\bend\s*$', '', inner_content)
#             # 替换整个块为内部内容
#             code = initial_pattern.sub(inner_content.strip(), code, count=1)

#         code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)
#         # 信号名自动修正（在验证之前）
#         code = self._auto_correct_signal_names(code)
        
#         # 三层防护：黑盒约束验证和转换
#         code, result = self.validator.validate_and_transform(code, self.content)
        
#         code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)
        
#         return code.strip(), result
    
#     def _auto_correct_signal_names(self, code: str) -> str:
#         """自动修正信号名错误"""
#         corrections = []
        
#         # 获取正确的复位信号名
#         reset_signal = self.validator._find_reset_signal()
        
#         # 如果正确的复位信号不是 'reset'，则修正所有 'reset' 引用
#         if reset_signal != "reset":
#             # 匹配独立的 'reset' 单词（不包括 'areset', 'rst_n' 等）
#             pattern = r'\breset\b(?!\w)'
#             matches = re.findall(pattern, code)
#             if matches:
#                 code = re.sub(pattern, reset_signal, code)
#                 corrections.append(f"reset -> {reset_signal} ({len(matches)} occurrences)")
        
#         # 检查是否有使用 'rst' 但正确信号是 'areset' 的情况
#         if reset_signal == "areset":
#             pattern = r'\brst\b(?!\w)'
#             matches = re.findall(pattern, code)
#             if matches:
#                 code = re.sub(pattern, reset_signal, code)
#                 corrections.append(f"rst -> {reset_signal} ({len(matches)} occurrences)")
        
#         # 检查是否使用了不存在的信号
#         for signal in re.findall(r'\b(\w+)\s*=', code):
#             signal = signal.strip()
#             # 跳过已知的合法信号
#             if signal in self.validator.dut_inputs:
#                 continue
#             # 检查是否是复位信号的别名
#             if signal.lower() in ['reset', 'rst', 'rst_n', 'rst_b'] and reset_signal != signal:
#                 code = re.sub(rf'\b{signal}\b', reset_signal, code)
#                 corrections.append(f"{signal} -> {reset_signal}")
        
#         if corrections:
#             logger.info(f"[Signal Correction] Applied corrections: {'; '.join(corrections)}")
        
#         return code

#     def _build_scenario_block(self, scenario_code, iter_idx):
#         """构建完整的场景代码块"""
#         # 格式化缩进
#         lines = scenario_code.split('\n')
#         formatted_lines = []
#         for line in lines:
#             stripped = line.strip()
#             if stripped:
#                 formatted_lines.append(f"    {stripped}")
#         formatted_code = '\n'.join(formatted_lines)
        
#         # 检测输出信号用于日志
#         output_signals = self._detect_output_signals()
#         output_log = self._generate_output_log(output_signals, iter_idx)
        
#         # 构建完整块
#         block = f'''
#     // ========== CGA Iteration {iter_idx} ==========
#     scenario = 100 + {iter_idx};
#     // Reset signals to safe state
# {self._generate_signal_reset()}
#     #5;
#     // CGA generated test sequence:
# {formatted_code}
#     // Log results
# {output_log}
#     // ==============================================
# '''
#         return block

#     def _detect_output_signals(self):
#         """检测DUT的输出信号"""
#         outputs = []
#         wire_pattern = re.compile(r'wire\s+(?:\[[\d:]+\]\s*)?(\w+)\s*;')
#         for match in wire_pattern.finditer(self.content):
#             signal = match.group(1)
#             if signal.lower() not in ['clk', 'clock', 'rst', 'reset', 'areset']:
#                 outputs.append(signal)
#         return outputs

#     def _generate_signal_reset(self):
#         """生成信号重置代码"""
#         inputs = []
#         reg_pattern = re.compile(r'reg\s+(?:\[[\d:]+\]\s*)?(\w+)\s*;')
#         for match in reg_pattern.finditer(self.content):
#             signal = match.group(1)
#             if signal.lower() not in ['clk', 'clock', 'file', 'scenario']:
#                 inputs.append(signal)
        
#         if inputs:
#             return "    " + "; ".join([f"{sig} = 0" for sig in inputs]) + ";"
#         return "    // No input signals to reset"

#     def _generate_output_log(self, signals, iter_idx):
#         """生成输出日志代码"""
#         if not signals:
#             return f'    $display("[CGA-{iter_idx}] Scenario executed");'
        
#         sig_names = ", ".join(signals)
#         format_str = ", ".join(["%b"] * len(signals))
        
#         return f'    $fdisplay(file, "[CGA-{iter_idx}] {sig_names} = {format_str}", {sig_names});'

#     def _inject_scenario(self, scenario_block):
#         """将场景块注入到测试平台"""
#         modified_tb = self.content
        
#         # 策略：如果有 $fclose，在其之前插入
#         if "$fclose" in modified_tb:
#             modified_tb = re.sub(
#                 r'(\s*)(\$fclose\s*\([^)]+\)\s*;)',
#                 scenario_block + r'\1\2',
#                 modified_tb,
#                 count=1
#             )
#         elif "$finish" in modified_tb:
#             # 否则在 $finish 之前插入
#             modified_tb = modified_tb.replace(
#                 "$finish;",
#                 scenario_block + "\n    $finish;"
#             )
#         else:
#             # 兜底：在最后一个 end 之前插入
#             last_end = modified_tb.rfind("end")
#             if last_end != -1:
#                 modified_tb = modified_tb[:last_end] + scenario_block + modified_tb[last_end:]
        
#         return modified_tb


"""
Description :   Utils for CGA (CoverageParser & TBInjector)
                - Features: Sticky Mode, Smart Noise Filtering (No assign/decls)
                - Enhanced: Three-layer protection for black-box constraints
                  * Layer 1: Enhanced Prompt constraints (prevention)
                  * Layer 2: Smart code transformation (conversion)
                  * Layer 3: Quality assessment & retry (fallback)
                - Integrated: Diversity Constraint Injector (Layer 1)
Author      :   CorrectBench Integration
"""
import re
import os
import logging
from typing import Tuple, List, Optional, Dict, TYPE_CHECKING

# [新增] 导入多样性约束注入器
if TYPE_CHECKING:
    from autoline.diversity_injector import DiversityInjector

# 配置日志
logger = logging.getLogger(__name__)

# ============================================================================
# 三层防护策略说明
# ============================================================================
# Layer 1 - Prompt约束: 动态提取允许信号列表，明确约束，正反面示例
# Layer 2 - 智能转换: 检测违规意图，尝试转换为合法形式
# Layer 3 - 质量评估: 违规比例过高时返回质量分数，触发重新生成
# ============================================================================


# ============================================================================
# 黑盒约束检查器 - 三层防护策略实现
# ============================================================================
class BlackBoxValidator:
    """
    黑盒约束验证器 - 三层防护策略
    
    Layer 1: 增强Prompt约束（预防）
        - 动态提取允许信号列表
        - 生成明确的约束提示
    
    Layer 2: 智能代码转换（转换）
        - 检测违规意图
        - 尝试转换为合法的等价形式
        - 转换失败时才注释
    
    Layer 3: 质量评估（重试）
        - 计算代码质量分数
        - 违规比例过高时建议重试
    """
    
    # 常见的内部信号命名模式（按严重程度分类）
    INTERNAL_SIGNAL_PATTERNS = {
        # 高风险：FSM状态相关（绝对不能修改）
        'critical': [
            (r'\bstate\b', 'FSM状态寄存器'),
            (r'\bnext_state\b', 'FSM下一状态'),
            (r'\bcurrent_state\b', 'FSM当前状态'),
            (r'\bnext\b(?!\s*[,@])', '下一状态简写'),
        ],
        # 中风险：计数器和内部寄存器
        'warning': [
            (r'\bcounter\b', '内部计数器'),
            (r'\bcount\b', '计数寄存器'),
            (r'\bcnt\b', '计数简写'),
            (r'\bfall_counter\b', '下落计数器'),
            (r'\breg_\w+', '内部寄存器'),
        ],
        # 低风险：可疑信号（需要确认）
        'info': [
            (r'\binternal_\w+', '内部信号'),
            (r'\btemp_\w+', '临时信号'),
            (r'\bprev_\w+', '前一状态'),
        ]
    }
    
    # 非法语句模式
    FORBIDDEN_STATEMENTS = [
        (r'\bforce\s+(\w+)', 'force语句', 'critical'),
        (r'\bassign\s+(\w+)\s*=', '连续赋值', 'critical'),
        (r'\bdeassign\s+', 'deassign语句', 'critical'),
        (r'\brelease\s+', 'release语句', 'critical'),
    ]
    
    # 层次化访问模式（如 DUT.state）
    HIERARCHICAL_ACCESS = r'(\w+)\s*\.\s*(\w+)'
    
    def __init__(self, dut_inputs: List[str] = None, dut_outputs: List[str] = None):
        """
        Args:
            dut_inputs: DUT模块的输入端口列表
            dut_outputs: DUT模块的输出端口列表
        """
        self.dut_inputs = dut_inputs or []
        self.dut_outputs = dut_outputs or []
        self.violations = {'critical': [], 'warning': [], 'info': []}
        self.transformations = []
        
    def validate_and_transform(self, code: str, tb_code: str = None) -> Tuple[str, Dict]:
        """验证并转换代码 - 主入口"""
        self.violations = {'critical': [], 'warning': [], 'info': []}
        self.transformations = []
        
        if tb_code:
            self._extract_signals_from_tb(tb_code)
        
        original_lines = code.strip().split('\n')
        total_lines = len([l for l in original_lines if l.strip() and not l.strip().startswith('//')])
        
        # Step 1: 移除非法语句
        code = self._transform_forbidden_statements(code)
        
        # Step 2: 转换层次化访问
        code = self._transform_hierarchical_access(code)
        
        # Step 3: 智能转换内部信号访问
        code = self._smart_transform_internal_signals(code)
        
        # Step 4: 最后清理
        code = self._final_cleanup(code)
        
        # 计算质量分数
        quality_score = self._calculate_quality_score(total_lines)
        
        # 决定是否需要重试
        should_retry = quality_score < 50 or len(self.violations['critical']) > 3
        
        result = {
            'quality_score': quality_score,
            'is_valid': len(self.violations['critical']) == 0,
            'violations': self.violations,
            'transformations': self.transformations,
            'should_retry': should_retry,
            'allowed_signals': self._get_allowed_signals_info()
        }
        
        return code.strip(), result
    
    def _extract_signals_from_tb(self, tb_code: str):
        """从测试平台代码中提取DUT输入输出信号"""
        dut_match = re.search(r'(\w+)\s+(?:DUT|dut|uut|UUT)\s*\(', tb_code, re.IGNORECASE)
        if dut_match:
            start = dut_match.start()
            bracket_count = 0
            end = start
            for i, char in enumerate(tb_code[start:]):
                if char == '(':
                    bracket_count += 1
                elif char == ')':
                    bracket_count -= 1
                    if bracket_count == 0:
                        end = start + i + 1
                        break
            
            dut_instance = tb_code[start:end]
            port_pattern = r'\.(\w+)\s*\(\s*(\w+)\s*\)'
            
            for match in re.finditer(port_pattern, dut_instance):
                signal_name = match.group(2)
                
                is_input = re.search(rf'\breg\s+(?:\[[\d:]+\]\s*)?{re.escape(signal_name)}\s*[;,\n]', tb_code)
                is_output = re.search(rf'\bwire\s+(?:\[[\d:]+\]\s*)?{re.escape(signal_name)}\s*[;,\n]', tb_code)
                
                if is_input and signal_name not in self.dut_inputs:
                    self.dut_inputs.append(signal_name)
                if is_output and signal_name not in self.dut_outputs:
                    self.dut_outputs.append(signal_name)
        
        # 备用方案：通过reg/wire声明推断
        if not self.dut_inputs and not self.dut_outputs:
            for match in re.finditer(r'\breg\s+(?:\[[\d:]+\]\s*)?(\w+)\s*[;,\n]', tb_code):
                signal = match.group(1)
                if signal.lower() not in ['file', 'scenario', 'i', 'j', 'k', 'cnt']:
                    if signal not in self.dut_inputs:
                        self.dut_inputs.append(signal)
            
            for match in re.finditer(r'\bwire\s+(?:\[[\d:]+\]\s*)?(\w+)\s*[;,\n]', tb_code):
                signal = match.group(1)
                if signal not in self.dut_outputs:
                    self.dut_outputs.append(signal)
    
    def _transform_forbidden_statements(self, code: str) -> str:
        """转换非法语句"""
        for pattern, desc, severity in self.FORBIDDEN_STATEMENTS:
            matches = list(re.finditer(pattern, code, re.IGNORECASE))
            for match in reversed(matches):
                signal = match.group(1) if match.groups() else 'unknown'
                self.violations[severity].append(f"{desc}: {signal}")
                
                line_start = code.rfind('\n', 0, match.start()) + 1
                line_end = code.find('\n', match.end())
                if line_end == -1:
                    line_end = len(code)
                original_line = code[line_start:line_end]
                
                # 尝试转换 force -> 直接赋值（仅对输入信号）
                if 'force' in match.group(0).lower() and signal in self.dut_inputs:
                    new_line = re.sub(r'\bforce\s+', '', original_line, flags=re.IGNORECASE)
                    code = code[:line_start] + new_line + code[line_end:]
                    self.transformations.append({
                        'type': 'force_to_assign',
                        'original': original_line.strip(),
                        'transformed': new_line.strip()
                    })
                    continue
                
                code = code[:line_start] + '// [BLOCKED] ' + original_line.lstrip() + code[line_end:]
                self.transformations.append({
                    'type': 'blocked',
                    'original': original_line.strip(),
                    'reason': desc
                })
        
        return code
    
    def _transform_hierarchical_access(self, code: str) -> str:
        """转换层次化访问（如 DUT.state）"""
        for match in re.finditer(self.HIERARCHICAL_ACCESS, code):
            prefix = match.group(1)
            signal = match.group(2)
            
            if prefix.upper() in ['DUT', 'UUT', 'TOP', 'TB']:
                if signal not in self.dut_outputs:
                    self.violations['critical'].append(f"层次化访问内部信号: {prefix}.{signal}")
                    
                    line_start = code.rfind('\n', 0, match.start()) + 1
                    line_end = code.find('\n', match.end())
                    if line_end == -1:
                        line_end = len(code)
                    original_line = code[line_start:line_end]
                    code = code[:line_start] + '// [HIERARCHY] ' + original_line.lstrip() + code[line_end:]
        
        return code
    
    def _smart_transform_internal_signals(self, code: str) -> str:
        """智能转换内部信号访问"""
        lines = code.split('\n')
        transformed_lines = []
        
        for line in lines:
            stripped = line.strip()
            
            if stripped.startswith('//') or not stripped:
                transformed_lines.append(line)
                continue
            
            if (stripped.startswith('#') or stripped.startswith('$') or 
                stripped.startswith('repeat(') or stripped.startswith('@(')):
                transformed_lines.append(line)
                continue
            
            detected_signals = self._detect_internal_signals_in_line(stripped)
            has_critical = detected_signals.get('critical', [])
            has_warning = detected_signals.get('warning', [])
            
            if not has_critical and not has_warning:
                transformed_lines.append(line)
                continue
            
            context = self._analyze_signal_context(stripped, detected_signals)
            
            if context['type'] == 'assignment':
                transformed_lines.append(f"// [INTERNAL_ASSIGN] Cannot modify internal signal")
                transformed_lines.append(f"// Original: {stripped}")
                self.violations['critical'].append(f"尝试修改内部信号: {context['signals']}")
            elif context['type'] == 'condition':
                transformed = self._transform_condition(stripped, context)
                transformed_lines.append(transformed)
                self.transformations.append({
                    'type': 'condition_transform',
                    'original': stripped,
                    'transformed': transformed
                })
            elif context['type'] == 'wait_for_state':
                transformed = self._transform_state_wait(stripped, context)
                transformed_lines.append(transformed)
                self.transformations.append({
                    'type': 'wait_transform',
                    'original': stripped,
                    'transformed': transformed
                })
            else:
                if has_critical:
                    transformed_lines.append(f"// [WARNING] Contains internal signal reference: {has_critical}")
                    transformed_lines.append(f"// Original: {stripped}")
                    for sig in has_critical:
                        self.violations['warning'].append(f"可疑的内部信号访问: {sig}")
                else:
                    transformed_lines.append(line)
        
        return '\n'.join(transformed_lines)
    
    def _detect_internal_signals_in_line(self, line: str) -> Dict[str, List[str]]:
        """检测行中的内部信号"""
        detected = {'critical': [], 'warning': [], 'info': []}
        
        LEGAL_KEYWORDS = {
            'repeat', 'posedge', 'negedge', 'begin', 'end', 'if', 'else', 
            'while', 'for', 'case', 'default', 'always', 'initial', 
            'assign', 'wire', 'reg', 'input', 'output', 'inout',
            'parameter', 'localparam', 'integer', 'real', 'time',
            'clk', 'clock', 'reset', 'rst', 'areset', 'rst_n',
            'enable', 'ena', 'valid', 'ready', 'data', 'addr', 'address',
            'true', 'false', 'idle', 'wait'
        }
        
        SYSTEM_FUNCTIONS = {'$display', '$write', '$monitor', '$fopen', '$fclose', 
                           '$fdisplay', '$fwrite', '$readmemh', '$readmemb',
                           '$finish', '$stop', '$random', '$time', '$stime'}
        
        for severity, patterns in self.INTERNAL_SIGNAL_PATTERNS.items():
            for pattern, name in patterns:
                matches = re.findall(pattern, line, re.IGNORECASE)
                if matches:
                    for match in matches:
                        if isinstance(match, tuple):
                            match = match[0] if match[0] else match[1]
                        
                        match_lower = match.lower() if match else ''
                        
                        if match_lower in LEGAL_KEYWORDS:
                            continue
                        if match in SYSTEM_FUNCTIONS:
                            continue
                        if match in self.dut_inputs or match in self.dut_outputs:
                            continue
                        if match.startswith('$'):
                            continue
                        
                        if match and match not in detected[severity]:
                            detected[severity].append(match)
        
        return detected
    
    def _analyze_signal_context(self, line: str, signals: Dict) -> Dict:
        """分析信号使用上下文"""
        assign_match = re.search(r'(\w+)\s*(?:=|<=)\s*', line)
        if assign_match:
            target = assign_match.group(1)
            if target in signals.get('critical', []) or target in signals.get('warning', []):
                return {'type': 'assignment', 'signals': [target], 'line': line}
        
        if re.search(r'wait\s*\([^)]*state', line, re.IGNORECASE):
            return {'type': 'wait_for_state', 'signals': signals.get('critical', []), 'line': line}
        
        if re.search(r'if\s*\(|while\s*\(|@\s*\(', line):
            return {'type': 'condition', 'signals': signals.get('critical', []) + signals.get('warning', []), 'line': line}
        
        return {'type': 'other', 'signals': signals.get('critical', []) + signals.get('warning', []), 'line': line}
    
    def _transform_condition(self, line: str, context: Dict) -> str:
        """转换条件判断语句"""
        original = line
        
        if 'state' in str(context['signals']):
            indent = len(line) - len(line.lstrip())
            spaces = ' ' * indent
            
            transformed = f"// [TRANSFORMED] Original: {original.strip()}\n"
            transformed += f"{spaces}// Cannot directly check internal state\n"
            transformed += f"{spaces}// Alternative: Wait for expected clock cycles\n"
            transformed += f"{spaces}repeat(5) @(posedge clk);  // Adjust cycles as needed"
            
            self.violations['warning'].append(f"条件判断转换: {original.strip()}")
            return transformed
        
        return f"// [TRANSFORMED] {original}"
    
    def _transform_state_wait(self, line: str, context: Dict) -> str:
        """转换状态等待语句"""
        indent = len(line) - len(line.lstrip())
        spaces = ' ' * indent
        
        transformed = f"// [TRANSFORMED] Original: {line.strip()}\n"
        transformed += f"{spaces}// Cannot wait for internal state directly\n"
        transformed += f"{spaces}// Alternative: Drive inputs and wait for expected cycles\n"
        transformed += f"{spaces}repeat(10) @(posedge clk);  // Adjust based on FSM design"
        
        self.violations['info'].append(f"状态等待转换: {line.strip()}")
        return transformed
    
    def _final_cleanup(self, code: str) -> str:
        """最终清理"""
        lines = code.split('\n')
        cleaned = []
        
        for line in lines:
            stripped = line.strip()
            
            if stripped in ['begin', 'end'] and cleaned:
                last = cleaned[-1].strip()
                if last.startswith('// [TRANSFORMED]') or last.startswith('// [INTERNAL'):
                    continue
            
            cleaned.append(line)
        
        result = '\n'.join(cleaned)
        result = re.sub(r'\n\s*\n\s*\n', '\n\n', result)
        
        return result
    
    def _calculate_quality_score(self, total_lines: int) -> int:
        """计算代码质量分数"""
        if total_lines == 0:
            return 0
        
        score = 100
        score -= len(self.violations['critical']) * 20
        score -= len(self.violations['warning']) * 5
        score += len([t for t in self.transformations if 'blocked' not in t.get('type', '')]) * 5
        
        return max(0, min(100, score))
    
    def _get_allowed_signals_info(self) -> Dict:
        """获取允许的信号信息"""
        return {
            'inputs': self.dut_inputs,
            'outputs': self.dut_outputs,
            'all_allowed': self.dut_inputs + self.dut_outputs
        }
    
    def generate_constraint_prompt(self) -> str:
        """生成动态约束提示 - 使用实际信号名"""
        prompt = "\n[SIGNAL CONSTRAINTS - DERIVED FROM YOUR DUT]\n"
        
        # 提取复位信号名（优先使用实际的）
        reset_signal = self._find_reset_signal()
        
        if self.dut_inputs:
            prompt += "ALLOWED INPUTS (you CAN drive these):\n"
            for sig in self.dut_inputs:
                prompt += f"  - {sig}\n"
        else:
            prompt += "ALLOWED INPUTS: Check the testbench for actual signal names\n"
        
        if self.dut_outputs:
            prompt += "\nOUTPUTS (you can READ but NOT write):\n"
            for sig in self.dut_outputs:
                prompt += f"  - {sig}\n"
        
        prompt += f"""
FORBIDDEN ACTIONS:
1. NEVER assign values to internal signals (state, counter, etc.)
2. NEVER use 'force' or 'assign' statements
3. NEVER access signals like DUT.state (hierarchical access)

CORRECT APPROACH:
- To reach a specific FSM state: drive inputs and WAIT for natural transition
- Example: Instead of "state = IDLE", use "{reset_signal} = 1; repeat(2) @(posedge clk); {reset_signal} = 0;"
"""
        return prompt
    
    def _find_reset_signal(self) -> str:
        """查找复位信号名"""
        # 按优先级查找常见的复位信号名
        reset_candidates = ['areset', 'rst_n', 'rst', 'reset', 'rst_b']
        for sig in reset_candidates:
            if sig in self.dut_inputs:
                return sig
        # 如果没找到，检查输入列表中是否有类似名称
        for sig in self.dut_inputs:
            sig_lower = sig.lower()
            if 'reset' in sig_lower or 'rst' in sig_lower:
                return sig
        # 默认返回第一个输入信号（排除 clk）
        for sig in self.dut_inputs:
            if 'clk' not in sig.lower():
                return sig
        return "reset"  # 兜底

    # =========================================================================
    # [新增] Verilog 语法预检查 - 检测常见逻辑错误
    # =========================================================================
    def check_syntax_issues(self, code: str, signal_widths: Dict[str, int] = None, declared_signals: set = None) -> Dict:
        """
        检测 Verilog 代码中的常见语法/逻辑问题

        Args:
            code: 待检查的代码
            signal_widths: 信号位宽映射 (可选，如 {'in': 1, 'data': 8})
            declared_signals: 已声明的信号集合 (可选，用于检测未声明信号)

        Returns:
            {
                'width_mismatch': [...],    # 位宽不匹配警告
                'logic_issues': [...],      # 逻辑问题
                'syntax_warnings': [...],   # 语法警告
                'should_retry': bool        # 是否建议重试
            }
        """
        result = {
            'width_mismatch': [],
            'logic_issues': [],
            'syntax_warnings': [],
            'should_retry': False
        }

        # 检查位宽不匹配
        result['width_mismatch'] = self._check_width_mismatch(code, signal_widths)

        # 检查逻辑问题
        result['logic_issues'] = self._check_logic_issues(code, signal_widths)

        # 检查其他语法问题（传入已声明信号）
        result['syntax_warnings'] = self._check_syntax_warnings(code, declared_signals)

        # 决定是否需要重试
        # 包括：位宽不匹配、逻辑问题、语法错误（severity='error'）
        has_syntax_errors = any(
            issue.get('severity') == 'error' 
            for issue in result['syntax_warnings']
        )
        result['should_retry'] = (
            len(result['width_mismatch']) > 0 or
            len(result['logic_issues']) > 0 or
            has_syntax_errors
        )

        return result

    def _check_width_mismatch(self, code: str, signal_widths: Dict[str, int] = None) -> List[Dict]:
        """
        检测位宽不匹配问题

        常见问题:
        - {signal} = N'b... 将多位值赋给单比特信号
        - signal = N'b... 位宽不匹配
        """
        issues = []
        signal_widths = signal_widths or {}

        # 默认假设未声明信号为 1 位
        def get_width(sig):
            return signal_widths.get(sig, 1)

        # 模式1: {signal} = N'bvalue (拼接赋值)
        # 例: {in} = 8'b01111100 - 将 8 位赋给 1 位
        concat_pattern = re.compile(r'\{(\w+)\}\s*=\s*(\d+)\'([bhd])([0-9a-fA-FxXzZ_]+)')
        for match in concat_pattern.finditer(code):
            signal = match.group(1)
            value_width = int(match.group(2))
            base = match.group(3)
            value = match.group(4)

            actual_width = get_width(signal)

            if value_width > actual_width:
                issues.append({
                    'type': 'concat_width_mismatch',
                    'signal': signal,
                    'signal_width': actual_width,
                    'assigned_width': value_width,
                    'original': match.group(0),
                    'message': f"Signal '{signal}' is {actual_width}-bit, but assigned {value_width}-bit value via concatenation. Verilog will truncate.",
                    'severity': 'warning',
                    'suggestion': f"Use a shift register: reg [{value_width-1}:0] temp; temp = {value_width}'{base}{value}; then shift bits one by one"
                })

        # 模式2: signal = N'bvalue (直接赋值)
        assign_pattern = re.compile(r'\b(\w+)\s*=\s*(\d+)\'([bhd])([0-9a-fA-FxXzZ_]+)')
        for match in assign_pattern.finditer(code):
            signal = match.group(1)
            value_width = int(match.group(2))

            # 跳过拼接赋值（已处理）
            if f'{{{signal}}}' in match.group(0):
                continue

            actual_width = get_width(signal)

            # 只有当信号已知且位宽不匹配时才警告
            if signal in signal_widths and value_width > actual_width:
                issues.append({
                    'type': 'direct_width_mismatch',
                    'signal': signal,
                    'signal_width': actual_width,
                    'assigned_width': value_width,
                    'original': match.group(0),
                    'message': f"Signal '{signal}' is {actual_width}-bit, but assigned {value_width}-bit value. Truncation will occur.",
                    'severity': 'warning'
                })

        return issues

    def _check_logic_issues(self, code: str, signal_widths: Dict[str, int] = None) -> List[Dict]:
        """
        检测逻辑问题

        常见问题:
        - 单比特信号自移位 (in = in >> 1 无效果)
        - 无效的循环条件
        """
        issues = []
        signal_widths = signal_widths or {}

        def get_width(sig):
            return signal_widths.get(sig, 1)

        # 模式: signal = signal >> N 或 signal = signal << N
        shift_pattern = re.compile(r'\b(\w+)\s*=\s*\1\s*(>>|<<)\s*(\d+)?')
        for match in shift_pattern.finditer(code):
            signal = match.group(1)
            direction = match.group(2)
            shift_amount = int(match.group(3)) if match.group(3) else 1

            actual_width = get_width(signal)

            if actual_width == 1:
                issues.append({
                    'type': 'single_bit_shift',
                    'signal': signal,
                    'direction': direction,
                    'original': match.group(0),
                    'message': f"Single-bit signal '{signal}' self-shift has no effect. Result is always 0.",
                    'severity': 'warning',
                    'suggestion': f"Use a shift register for bit-serial input, not the input signal itself"
                })

        # 模式: repeat(N) begin ... signal = signal >> 1; end (循环移位单比特)
        repeat_shift_pattern = re.compile(r'repeat\s*\(\s*\d+\s*\)\s*begin[^}]*?(\w+)\s*=\s*\1\s*(>>|<<)', re.DOTALL)
        for match in repeat_shift_pattern.finditer(code):
            signal = match.group(1)
            actual_width = get_width(signal)

            if actual_width == 1:
                issues.append({
                    'type': 'repeat_single_bit_shift',
                    'signal': signal,
                    'original': match.group(0)[:100] + '...',
                    'message': f"Repeat loop shifting single-bit signal '{signal}' is ineffective",
                    'severity': 'warning'
                })

        return issues

    def _check_syntax_warnings(self, code: str, declared_signals: set = None) -> List[Dict]:
        """
        检测其他语法问题
        
        Args:
            code: 待检查的代码
            declared_signals: 已声明的信号集合 (从完整 TB 中提取)
        """
        issues = []
        declared_signals = declared_signals or set()

        # 检查: 缺少分号
        # 注意: 这只是简单检查，不是完整解析
        lines = code.split('\n')
        for i, line in enumerate(lines):
            stripped = line.strip()
            if not stripped or stripped.startswith('//'):
                continue

            # 跳过不需要分号的行
            skip_patterns = [
                r'^begin$', r'^end$', r'^endcase$', r'^endmodule$',
                r'^else$', r'^\)$', r'^\}\s*$', r'^`timescale', r'^`include'
            ]
            if any(re.match(p, stripped) for p in skip_patterns):
                continue

            # 检查是否需要分号但没有
            needs_semicolon = re.search(r'\b(initial|always|assign|reg|wire|parameter|localport)\b', stripped) is None
            has_semicolon = stripped.endswith(';') or stripped.endswith(')') or stripped.endswith('}')

            if needs_semicolon and not has_semicolon and not stripped.endswith('begin'):
                # 可能缺少分号（但不确定）
                pass  # 暂不报警，避免误报

        # 检查: 不匹配的 begin/end
        begin_count = len(re.findall(r'\bbegin\b', code))
        end_count = len(re.findall(r'\bend\b', code))
        if begin_count != end_count:
            issues.append({
                'type': 'mismatched_begin_end',
                'message': f"Mismatched begin/end: {begin_count} begin vs {end_count} end",
                'severity': 'error'
            })

        # 检查: 未声明的信号（在赋值左侧使用的信号）
        # 使用传入的已声明信号集合
        for match in re.finditer(r'^\s*(\w+)\s*=', code, re.MULTILINE):
            signal = match.group(1)
            # 跳过系统任务和关键字
            if signal in ['if', 'else', 'case', 'for', 'while', 'repeat', 'assign', 'force', 'release']:
                continue
            # 跳过以 $ 开头的系统任务
            if signal.startswith('$'):
                continue
            # 检查是否在已声明信号列表中
            if signal not in declared_signals:
                issues.append({
                    'type': 'undeclared_signal',
                    'signal': signal,
                    'message': f"Signal '{signal}' is used but not declared in the testbench",
                    'severity': 'error',
                    'suggestion': f"Use an existing signal name (declared: {', '.join(list(declared_signals)[:10])}...)"
                })

        # 检查: always 块与时钟生成冲突
        # 检测是否有多个 always/initial 块驱动同一信号
        always_blocks = re.findall(r'\balways\s*(@[^i]|begin)', code)
        initial_clk_blocks = len(re.findall(r'initial\s+begin[^i]*?clk\s*=', code, re.DOTALL))
        always_clk_blocks = len(re.findall(r'\balways[^i]*?clk\s*=', code, re.DOTALL))
        
        if initial_clk_blocks > 0 and always_clk_blocks > 0:
            issues.append({
                'type': 'multiple_clock_drivers',
                'message': f"Multiple clock drivers detected: {initial_clk_blocks} initial + {always_clk_blocks} always blocks driving clk",
                'severity': 'error',
                'suggestion': "Remove duplicate clock generation. The testbench already has clock generation."
            })
        
        # 检查: initial 块嵌套（生成了 initial begin ... end 在注入时会导致嵌套）
        if re.search(r'\binitial\s+begin\b', code):
            issues.append({
                'type': 'initial_block_injection',
                'message': "Code contains 'initial begin...end' block which should not be injected into an existing initial block",
                'severity': 'error',
                'suggestion': "Remove the 'initial begin...end' wrapper, keep only the test statements inside"
            })

        return issues


# ============================================================================
# CoverageParser - 覆盖率解析器
# ============================================================================
class CoverageParser:
    """覆盖率解析器 - 从带注释的Verilog文件中提取未覆盖的代码块
    
    [增强] 集成语义分析结果，提供更精准的 FSM 状态路径指导
    [新增] 集成能量分配层，提供目标功能点优先级信息
    [新增] 集成多样性约束注入器，避免测试用例同质化
    """
    
    def __init__(self, annotated_file, tb_code=None, semantic_result=None, 
                 energy_allocator=None, diversity_injector=None):
        self.file_path = annotated_file
        self.tb_code = tb_code
        self.semantic_result = semantic_result  # [新增] 语义分析结果
        self.energy_allocator = energy_allocator  # [新增] 能量分配器
        self.diversity_injector = diversity_injector  # [新增] 多样性约束注入器
        # 修复：Verilator 覆盖率标记格式多样化：
        # %NNNNNN - 行覆盖计数（%000000 表示从未执行）
        # ~NNNNNN - 分支/条件覆盖计数（~000000 表示分支从未执行）
        # ^NNNNNN - 未覆盖的分支标记
        #  NNNNNN - 空格开头+数字（某些 Verilator 版本）
        # NNNNNN - 纯数字开头（无前缀）
        self.line_pattern = re.compile(r'^%(\d+)\s+(.*)$')    # 匹配 %NNNNNN code
        self.tilde_pattern = re.compile(r'^~(\d+)\s+(.*)$')   # 匹配 ~NNNNNN code
        self.caret_pattern = re.compile(r'^\^(\d+)\s+(.*)$')  # 匹配 ^NNNNNN code
        # [修复] 纯数字开头（无前缀）或空格开头
        self.plain_pattern = re.compile(r'^\s*(\d+)\s+(.*)$')  # 匹配 " NNNNNN" 或 "NNNNNN"
        self.decl_pattern = re.compile(r'^\s*(input|output|inout|wire|reg|logic|parameter|localparam|assign)\b')
        
        self.validator = BlackBoxValidator()
        if tb_code:
            self.validator._extract_signals_from_tb(tb_code)

    def generate_prompt(self, current_score):
        """生成覆盖率驱动的Prompt"""
        if not os.path.exists(self.file_path):
            return None

        try:
            with open(self.file_path, 'r', encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()
        except Exception:
            return None

        missing_blocks = []
        current_block = []
        recording = False
        context_buffer = []
        CONTEXT_SIZE = 3
        
        # 收集缺失行用于 FSM 分析
        missing_lines = []

        for i, line in enumerate(lines):
            line = line.strip()
            count = -1
            clean_code = line
            is_tilde = False
            is_caret = False

            # 尝试匹配各种覆盖率标记格式
            # Verilator 覆盖率格式：
            # - %NNNNNN: 行覆盖，NNNNNN 是执行次数，%000000 表示未执行
            # - ~NNNNNN: 分支/条件覆盖，~000000 表示分支从未执行
            # - ^NNNNNN: 未覆盖分支标记
            # - NNNNNN: 无前缀格式（某些版本）
            match_pct = self.line_pattern.match(line)      # %NNNNNN code
            match_tilde = self.tilde_pattern.match(line)   # ~NNNNNN code
            match_caret = self.caret_pattern.match(line)   # ^NNNNNN code
            match_plain = self.plain_pattern.match(line)    # NNNNNN code (无前缀)

            if match_pct:
                count = int(match_pct.group(1))
                clean_code = match_pct.group(2).strip()
            elif match_tilde:
                count = int(match_tilde.group(1))
                clean_code = match_tilde.group(2).strip()
                is_tilde = True
            elif match_caret:
                count = int(match_caret.group(1))
                clean_code = match_caret.group(2).strip()
                is_caret = True
            elif match_plain:
                # 纯数字格式（可能出现在某些 Verilator 版本）
                count = int(match_plain.group(1))
                clean_code = match_plain.group(2).strip()

            if "//" in clean_code:
                clean_code = clean_code.split("//")[0].strip()

            is_hard_noise = (self.decl_pattern.match(clean_code) or clean_code == "endmodule")
            is_soft_noise = (len(clean_code) < 2 or clean_code in ["end", "begin", "else", ");", "endcase", "default:"] or
                           clean_code.startswith("module ") or not any(c.isalnum() for c in clean_code))

            # [修改] 覆盖状态判断：
            # - %NNNNNN: count > 0 表示已覆盖，count == 0 表示未覆盖
            # - ~NNNNNN: 分支覆盖标记，count == 0 也表示未覆盖！
            # - ^NNNNNN: 未覆盖分支标记
            is_definitely_covered = (not is_tilde and not is_caret and count > 0)
            # [关键修复] tilde 格式 count == 0 也应该被视为 missing
            is_definitely_missed = (
                (not is_tilde and not is_caret and count == 0 and not is_hard_noise and not is_soft_noise) or
                (is_tilde and count == 0 and not is_hard_noise and not is_soft_noise) or  # [新增] ~000000 也是 missing
                (is_caret and not is_hard_noise and not is_soft_noise)
            )

            if recording:
                if is_definitely_covered:
                    missing_blocks.append(current_block)
                    missing_lines.extend(current_block)
                    current_block = []
                    recording = False
                    if not is_hard_noise:
                        context_buffer.append(clean_code)
                else:
                    if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
                        current_block.append(f"Line {i+1}: {clean_code}")
            else:
                if is_definitely_missed:
                    recording = True
                    if context_buffer:
                        current_block.append(f"... (Context)")
                        for ctx in context_buffer:
                            current_block.append(f"   {ctx}")
                    current_block.append(f"Line {i+1}: {clean_code}  <--- MISSING START")
                else:
                    if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
                        context_buffer.append(clean_code)
                        if len(context_buffer) > CONTEXT_SIZE:
                            context_buffer.pop(0)

        if recording and current_block:
            missing_blocks.append(current_block)
            missing_lines.extend(current_block)

        # [改进] 详细诊断日志 - 使用 info 级别确保可见
        total_lines = len(lines)
        parsed_lines = sum(1 for l in lines if l.strip() and (
            self.line_pattern.match(l.strip()) or
            self.tilde_pattern.match(l.strip()) or
            self.caret_pattern.match(l.strip()) or
            self.plain_pattern.match(l.strip())
        ))

        # 收集零计数行的详细信息
        zero_count_details = []
        for l in lines:
            l_stripped = l.strip()
            if not l_stripped:
                continue
            match_pct = self.line_pattern.match(l_stripped)
            match_tilde = self.tilde_pattern.match(l_stripped)
            if match_pct and int(match_pct.group(1)) == 0:
                zero_count_details.append(('%', match_pct.group(2).strip()[:50]))
            elif match_tilde and int(match_tilde.group(1)) == 0:
                zero_count_details.append(('~', match_tilde.group(2).strip()[:50]))

        zero_count_lines = len(zero_count_details)

        logger.info(f"CoverageParser: Total={total_lines}, Parsed={parsed_lines}, Zero-count={zero_count_lines}, Missing blocks={len(missing_blocks)}")

        if not missing_blocks:
            # [改进] 详细诊断信息
            if zero_count_lines > 0:
                logger.warning(f"Found {zero_count_lines} lines with zero coverage count, but no missing blocks extracted.")
                logger.warning("Zero-count lines:")
                for prefix, code in zero_count_details[:10]:  # 只显示前10个
                    logger.warning(f"  {prefix}000000: {code}")
                if len(zero_count_details) > 10:
                    logger.warning(f"  ... and {len(zero_count_details) - 10} more")
                logger.warning("These lines may have been filtered as noise (declarations, etc.)")
            return None

        selected_blocks = missing_blocks[:50]

        # 获取实际信号名用于示例
        reset_signal = self.validator._find_reset_signal()
        inputs_no_clk = [s for s in self.validator.dut_inputs if 'clk' not in s.lower()]
        example_signal = inputs_no_clk[0] if inputs_no_clk else (reset_signal if reset_signal != "reset" else "ena")
        
        # 分析 FSM 相关的缺失代码
        fsm_analysis = self._analyze_fsm_missing(missing_lines)
        
        # [新增] 从语义分析结果获取 FSM 和功能点信息
        semantic_context = self._generate_semantic_context()

        prompt = f"""
[ROLE]
You are a hardware verification expert. Your task is to write a test scenario to improve code coverage.

[COVERAGE STATUS]
Current testbench achieves {current_score:.2f}% coverage.
The following logic blocks in the DUT are NEVER executed during simulation:

"""
        for idx, block in enumerate(selected_blocks):
            prompt += f"--- Missing Logic Block {idx+1} ---\n" + "\n".join(block) + "\n\n"
        
        # [新增] 添加语义分析上下文
        if semantic_context:
            prompt += f"""
[SEMANTIC ANALYSIS - MODULE UNDERSTANDING]
{semantic_context}
"""
        
        # === [新增] 添加能量分配目标上下文 ===
        if self.energy_allocator:
            energy_context = self.energy_allocator.get_target_context()
            if energy_context:
                prompt += f"""
[ENERGY-ALIGNED TARGET - PRIORITY]
{energy_context}
Focus your test scenario on covering this high-priority target first.
"""
        # =====================================

        prompt += self.validator.generate_constraint_prompt()
        
        # 添加 FSM 分析提示
        if fsm_analysis:
            prompt += f"""
[FSM STATE TRANSITION ANALYSIS - CRITICAL]
{fsm_analysis}

IMPORTANT: FSM transitions have PRIORITY ORDER!
- 'if' conditions are evaluated TOP to BOTTOM
- The FIRST matching condition determines the next state
- To trigger a branch like "else if (condition)", you MUST ensure all higher-priority conditions are FALSE
- Read the missing code's context carefully: what conditions precede it?

"""

        prompt += f"""
[OUTPUT REQUIREMENTS - CRITICAL]
1. Return ONLY Verilog test scenario code (NOT a task definition)
2. Your code will be inserted INTO an existing `initial begin ... end` block
3. DO NOT wrap your code in `task ... endtask` - just write the test sequence directly
4. DO NOT use `$finish` or `$stop` - the testbench handles simulation end

[CODING STYLE]
1. Use blocking assignments for input signals: `signal = value;`
2. Use `#N;` for time delays: `#10;` means wait 10 time units
3. Use `repeat(N) @(posedge clk);` to wait for N clock cycles
4. Start with reset sequence if needed

[BLACK-BOX CONSTRAINTS - CRITICAL]
1. You can ONLY control module INPUTS listed above
2. You CANNOT access internal signals (state, next_state, counters, etc.)
3. You CANNOT use `force` or `assign` on internal signals
4. To trigger a specific state: drive inputs and wait for the FSM to reach it naturally

[STEP-BY-STEP APPROACH - REQUIRED]
For each missing branch, think through:
1. What STATE must the FSM be in? (Look at the case statement)
2. What CONDITIONS must be true/false? (Check priority order!)
3. How to reach that state from reset? (Trace state transitions)
4. What inputs to apply and in what order?

[POSITIVE EXAMPLE - CORRECT APPROACH]
```verilog
// Reset sequence - use ACTUAL input signal names from above
{reset_signal} = 1;
repeat(2) @(posedge clk);
{reset_signal} = 0;

// Wait for FSM to reach desired state (estimate cycles)
repeat(3) @(posedge clk);

// Trigger missing branch by driving inputs
{example_signal} = 1;
repeat(5) @(posedge clk);
{example_signal} = 0;
repeat(10) @(posedge clk);
```

[NEGATIVE EXAMPLE - DO NOT DO THIS]
```verilog
// WRONG: Using wrong signal name (e.g., 'reset' instead of '{reset_signal}')
reset = 1;  // ERROR: Signal 'reset' does not exist! Use '{reset_signal}' instead!

// WRONG: Not considering condition priority in FSM
// If missing code is "else if (condition_b)", you must make condition_a FALSE first!
// Example: if FSM has "if (!signal_a) ... else if (signal_b) ..."
// Then signal_a must be 1 (FALSE) for the else-if branch to execute
signal_a = 0;  // WRONG: This blocks the else-if branch!
signal_b = 1;  // This will NOT trigger because signal_a=0 took priority

// CORRECT: Analyze priority, set higher-priority conditions to FALSE
signal_a = 1;  // Now the first condition (!signal_a) is FALSE
signal_b = 1;  // Now this else-if branch can execute

// WRONG: Trying to assign internal state
state = IDLE;  // ERROR: Cannot modify internal signal!

// WRONG: Using force on internal signal
force DUT.state = WL;  // ERROR: Cannot force internal signal!

// WRONG: Checking internal state in condition
if (state == WL) begin  // ERROR: Cannot read internal signal!
    {example_signal} = 1;
end

// CORRECT ALTERNATIVE: Estimate timing instead
repeat(5) @(posedge clk);  // Wait for FSM to reach expected state
{example_signal} = 1;
```

[SIGNAL NAME WARNING - CRITICAL]
- DO NOT use 'reset' if the actual signal is '{reset_signal}'
- DO NOT use 'rst' if the actual signal is '{reset_signal}'
- ALWAYS use EXACT signal names from the ALLOWED INPUTS list above
- Double-check every signal name before using it!

Now write the test scenario code to cover the missing blocks:
"""
        
        # === [新增] 注入多样性约束 ===
        if self.diversity_injector:
            # 获取未覆盖功能点
            uncovered_functions = []
            if self.semantic_result and self.semantic_result.get('function_points'):
                uncovered_functions = [
                    fp for fp in self.semantic_result['function_points'] 
                    if not fp.get('covered', False)
                ]
            
            # 获取当前目标功能点
            target_function = ""
            if self.energy_allocator and self.energy_allocator.current_target:
                target_function = self.energy_allocator.current_target.function_point
            
            # 注入多样性约束
            prompt = self.diversity_injector.inject_diversity_constraints(
                prompt=prompt,
                target_function=target_function,
                uncovered_functions=uncovered_functions
            )
        # =================================
        
        return prompt
    
    def _analyze_fsm_missing(self, missing_lines: List[str]) -> str:
        """分析 FSM 相关的缺失代码，生成具体的 FSM 状态转换指导"""
        analysis = []
        
        # 检查是否涉及 FSM 状态转换
        has_state_case = any('case' in line.lower() and 'state' in line.lower() for line in missing_lines)
        has_else_if = any('else if' in line.lower() for line in missing_lines)
        has_if_condition = any(re.search(r'\bif\s*\(', line) for line in missing_lines)
        
        if has_state_case or has_else_if:
            analysis.append("- Missing code involves FSM state transitions or conditional branches")
        
        if has_else_if or has_if_condition:
            analysis.append("- Conditional branches have PRIORITY ORDER (top to bottom)")
            analysis.append("- 'else if' branches require ALL previous conditions to be FALSE")
            analysis.append("- Analyze the missing code's context: what conditions block this branch?")
        
        if has_state_case:
            analysis.append("- To trigger a state transition: first reach the source state, then drive inputs")
        
        # === 新增：FSM 状态路径分析 ===
        # 尝试从缺失代码中提取 FSM 状态信息
        fsm_state_info = self._extract_fsm_state_from_missing(missing_lines)
        if fsm_state_info:
            analysis.append("")
            analysis.append("[FSM STATE PATH ANALYSIS]")
            analysis.extend(fsm_state_info)
        
        return "\n".join(analysis) if analysis else ""
    
    def _extract_fsm_state_from_missing(self, missing_lines: List[str]) -> List[str]:
        """
        从缺失代码中提取 FSM 状态信息，生成具体的状态转换指导
        
        分析策略：
        1. 从缺失代码的上下文识别 case 分支（FSM 状态）
        2. 分析该状态下的条件分支优先级
        3. 识别需要满足的输入条件
        """
        info = []
        
        # 从 annotated 文件中读取完整的 DUT 代码以分析 FSM 结构
        try:
            with open(self.file_path, 'r', encoding='utf-8', errors='ignore') as f:
                full_content = f.read()
        except:
            return info
        
        # 提取缺失代码所在的 FSM 状态
        target_state = None
        missing_condition = None
        
        for line in missing_lines:
            # 查找 case 分支标记（如 "WL:", "WR:", "FALLL:" 等）
            # 格式可能是 "Line N: STATE:" 或 "STATE:"
            state_match = re.search(r'\b([A-Z][A-Z0-9_]*)\s*:', line)
            if state_match:
                potential_state = state_match.group(1)
                # 排除常见的非状态关键字
                if potential_state not in ['IF', 'ELSE', 'CASE', 'BEGIN', 'END', 'DEFAULT']:
                    target_state = potential_state
                    break
        
        # 如果没找到，尝试从整个文件中分析
        if not target_state:
            # 查找缺失行附近的 case 分支
            lines = full_content.split('\n')
            for i, line in enumerate(lines):
                # 查找覆盖率标记为 0 的行
                if re.match(r'^%000000', line.strip()):
                    # 向上查找最近的 case 分支（状态）
                    for j in range(i-1, max(0, i-20), -1):
                        state_match = re.search(r'^\s*([A-Z][A-Z0-9_]*)\s*:', lines[j])
                        if state_match:
                            target_state = state_match.group(1)
                            break
                    if target_state:
                        break
        
        # 分析缺失的条件分支
        for line in missing_lines:
            # 提取 else if 条件
            else_if_match = re.search(r'else\s+if\s*\(([^)]+)\)', line)
            if else_if_match:
                missing_condition = else_if_match.group(1)
                break
            # 提取 if 条件
            if_match = re.search(r'\bif\s*\(([^)]+)\)', line)
            if if_match:
                missing_condition = if_match.group(1)
                break
        
        # 生成具体的指导信息
        if target_state:
            info.append(f"- Target FSM state identified: {target_state}")
            
            # 查找复位后的初始状态
            reset_state = self._find_reset_state(full_content)
            if reset_state:
                info.append(f"- After reset, FSM starts in state: {reset_state}")
                
                if reset_state != target_state:
                    info.append(f"- CRITICAL: You must FIRST transition from {reset_state} to {target_state}!")
                    info.append(f"- Do NOT assume FSM will automatically reach {target_state}!")
                    
                    # 尝试找到状态转换路径
                    transition_hint = self._find_state_transition_hint(full_content, reset_state, target_state)
                    if transition_hint:
                        info.append(f"- To reach {target_state}: {transition_hint}")
        
        if missing_condition:
            info.append(f"- Missing condition: \"{missing_condition}\"")
            # 分析条件优先级
            priority_info = self._analyze_condition_priority(full_content, target_state, missing_condition)
            if priority_info:
                info.extend(priority_info)
        
        return info
    
    def _find_reset_state(self, content: str) -> Optional[str]:
        """从 DUT 代码中找到复位后的初始状态"""
        # 查找复位逻辑中的状态赋值
        # 常见模式: if (reset) state <= IDLE; 或 state <= 0;
        patterns = [
            r'if\s*\([^)]*reset[^)]*\)\s*state\s*<=\s*([A-Z][A-Z0-9_]*);',
            r'if\s*\([^)]*reset[^)]*\)\s*state\s*<=\s*(\d+);',
            r'if\s*\([^)]*rst[^)]*\)\s*state\s*<=\s*([A-Z][A-Z0-9_]*);',
        ]
        
        for pattern in patterns:
            match = re.search(pattern, content, re.IGNORECASE)
            if match:
                state = match.group(1)
                # 如果是数字，尝试从参数中找对应的状态名
                if state.isdigit():
                    # 查找参数定义
                    param_match = re.search(r'parameter\s+([^;]+);', content)
                    if param_match:
                        params = param_match.group(1)
                        # 解析参数列表
                        for param in params.split(','):
                            param = param.strip()
                            if '=' in param:
                                name, value = param.split('=')
                                if value.strip() == state:
                                    return name.strip()
                return state
        
        return None
    
    def _find_state_transition_hint(self, content: str, from_state: str, to_state: str) -> Optional[str]:
        """找到从一个状态到另一个状态的转换条件"""
        # 在 case 语句中查找 from_state 分支
        # 提取该分支下到 to_state 的转换条件
        
        # 简单策略：查找 "next = TO_STATE" 或 "next <= TO_STATE"
        pattern = rf'{from_state}\s*:.*?next\s*=?\s*{to_state}'
        match = re.search(pattern, content, re.DOTALL)
        
        if match:
            # 提取条件
            branch_code = match.group(0)
            # 查找 if 条件
            if_match = re.search(r'if\s*\(([^)]+)\)\s*next\s*=?\s*' + to_state, branch_code)
            if if_match:
                return f"set condition: {if_match.group(1)}"
            
            # 查找 else if 条件
            elif_match = re.search(r'else\s+if\s*\(([^)]+)\)\s*next\s*=?\s*' + to_state, branch_code)
            if elif_match:
                return f"set condition: {elif_match.group(1)} (ensure earlier conditions are FALSE)"
        
        # 尝试反向查找：什么条件下会转换到目标状态
        trans_pattern = rf'(?:if|else\s+if)\s*\(([^)]+)\)\s*(?:next\s*=?\s*{to_state}|{to_state}\s*;)'
        trans_match = re.search(trans_pattern, content)
        if trans_match:
            return f"set condition: {trans_match.group(1)}"
        
        return None
    
    def _analyze_condition_priority(self, content: str, state: str, missing_condition: str) -> List[str]:
        """分析条件分支的优先级，找出需要排除的条件"""
        info = []
        
        if not state:
            return info
        
        # 查找该状态下的所有条件分支
        # 提取 state: 后面的代码块
        state_block_pattern = rf'{state}\s*:(.*?)(?=[A-Z][A-Z0-9_]*\s*:|endcase|default:)'
        match = re.search(state_block_pattern, content, re.DOTALL)
        
        if not match:
            return info
        
        state_block = match.group(1)
        
        # 提取所有条件分支
        conditions = []
        for cond_match in re.finditer(r'(?:if|else\s+if)\s*\(([^)]+)\)', state_block):
            conditions.append(cond_match.group(1).strip())
        
        # 找到缺失条件在列表中的位置
        missing_idx = -1
        for i, cond in enumerate(conditions):
            # 简化比较（去除空格）
            if cond.replace(' ', '') in missing_condition.replace(' ', '') or \
               missing_condition.replace(' ', '') in cond.replace(' ', ''):
                missing_idx = i
                break
        
        if missing_idx > 0:
            info.append(f"- This branch is condition #{missing_idx + 1} (lower priority)")
            info.append(f"- You must make ALL earlier conditions FALSE:")
            for i in range(missing_idx):
                cond = conditions[i]
                # 分析如何使条件为 FALSE
                false_hint = self._get_false_hint(cond)
                info.append(f"  * \"{cond}\" must be FALSE → {false_hint}")
        
        return info
    
    def _get_false_hint(self, condition: str) -> str:
        """分析如何使条件为 FALSE"""
        condition = condition.strip()
        
        # 处理 !signal 形式
        if condition.startswith('!'):
            signal = condition[1:].strip()
            return f"set {signal} = 1"
        
        # 处理 signal 形式（布尔值）
        if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', condition):
            return f"set {condition} = 0"
        
        # 处理比较运算符
        if '==' in condition:
            parts = condition.split('==')
            if len(parts) == 2:
                signal = parts[0].strip()
                value = parts[1].strip()
                if value.isdigit():
                    return f"set {signal} != {value}"
        
        # 处理 >= 形式
        if '>=' in condition:
            parts = condition.split('>=')
            if len(parts) == 2:
                signal = parts[0].strip()
                value = parts[1].strip()
                if value.isdigit():
                    return f"set {signal} < {value}"
        
        # 处理 > 形式
        if '>' in condition and '>=' not in condition:
            parts = condition.split('>')
            if len(parts) == 2:
                signal = parts[0].strip()
                value = parts[1].strip()
                return f"set {signal} <= {value}"
        
        return "analyze the condition logic"
    
    def _generate_semantic_context(self) -> str:
        """
        [新增] 从语义分析结果生成 Prompt 上下文
        
        整合语义分析层 (Layer 0) 的输出，为 LLM 提供更精准的指导：
        - FSM 状态转换图
        - 功能点重要性排序
        - 测试场景建议
        
        Returns:
            语义上下文字符串，用于增强 Prompt
        """
        if not self.semantic_result:
            return ""
        
        context_parts = []
        
        # 1. 模块基础信息
        module_name = self.semantic_result.get('module_name', '')
        inputs = self.semantic_result.get('inputs', [])
        outputs = self.semantic_result.get('outputs', [])
        
        if module_name:
            context_parts.append(f"Module Name: {module_name}")
        if inputs:
            context_parts.append(f"Module Inputs: {', '.join(inputs)}")
        if outputs:
            context_parts.append(f"Module Outputs: {', '.join(outputs)}")
        
        # 2. FSM 信息（最关键）
        fsm_info = self.semantic_result.get('fsm_info')
        if fsm_info:
            context_parts.append("")
            context_parts.append("=== FSM STATE MACHINE DETAILS ===")
            context_parts.append(f"State Variable: {fsm_info.get('state_variable', 'unknown')}")
            
            states = fsm_info.get('states', [])
            if states:
                context_parts.append(f"All States ({len(states)}): {', '.join(states)}")
            
            # 状态转换表
            transitions = fsm_info.get('transitions', {})
            if transitions:
                context_parts.append("")
                context_parts.append("=== STATE TRANSITION TABLE ===")
                context_parts.append("Format: CURRENT_STATE --[CONDITION]--> NEXT_STATE")
                context_parts.append("")
                
                for state, trans_list in transitions.items():
                    for trans in trans_list:
                        condition = trans.get('condition', 'default')
                        next_state = trans.get('next_state', 'unknown')
                        if condition == 'default':
                            context_parts.append(f"  {state} --[default]--> {next_state}")
                        else:
                            context_parts.append(f"  {state} --[if ({condition})]--> {next_state}")
                
                # 添加状态转换路径分析
                context_parts.append("")
                context_parts.append("=== STATE TRANSITION PATH HINTS ===")
                reset_state = self._find_reset_state_from_fsm(fsm_info)
                if reset_state:
                    context_parts.append(f"Initial State (after reset): {reset_state}")
                    context_parts.append("")
                    context_parts.append("IMPORTANT: To reach a target state, trace the path from reset:")
                    context_parts.append("  1. Reset the DUT to initialize to the starting state")
                    context_parts.append("  2. Apply inputs to trigger state transitions")
                    context_parts.append("  3. Wait for the FSM to naturally reach the target state")
                    context_parts.append("  4. THEN apply inputs to trigger the missing branch")
        
        # 3. 功能点优先级
        function_points = self.semantic_result.get('function_points', [])
        if function_points:
            context_parts.append("")
            context_parts.append("=== FUNCTION POINTS (Ranked by Importance) ===")
            
            for i, fp in enumerate(function_points[:10]):  # Top 10
                name = fp.get('name', 'unknown')
                fp_type = fp.get('type', 'unknown')
                importance = fp.get('importance', 0)
                covered = fp.get('covered', False)
                status = "✓ COVERED" if covered else "✗ NOT COVERED"
                context_parts.append(f"  {i+1}. [{status}] {name} ({fp_type}): importance={importance:.2f}")
        
        # 4. 测试场景建议
        test_scenarios = self.semantic_result.get('test_scenarios', [])
        if test_scenarios:
            context_parts.append("")
            context_parts.append("=== RECOMMENDED TEST SCENARIOS ===")
            
            for i, ts in enumerate(test_scenarios[:5]):  # Top 5
                name = ts.get('name', 'unknown')
                description = ts.get('description', '')
                priority = ts.get('priority', 0)
                context_parts.append(f"  {i+1}. {name}: {description} (priority={priority:.2f})")
        
        if context_parts:
            return "\n".join(context_parts)
        return ""
    
    def _find_reset_state_from_fsm(self, fsm_info: dict) -> Optional[str]:
        """从 FSM 信息中推断复位后的初始状态"""
        # 方法1：检查是否有明确的复位状态
        transitions = fsm_info.get('transitions', {})
        
        # 复位后通常进入第一个定义的状态或特定名称的状态
        states = fsm_info.get('states', [])
        
        # 常见的初始状态命名
        initial_state_names = ['IDLE', 'INIT', 'RESET', 'START', 'BEGIN']
        
        for name in initial_state_names:
            if name in states:
                return name
        
        # 如果没有找到，返回第一个状态
        if states:
            return states[0]
        
        return None


# ============================================================================
# TBInjector - 场景注入器
# ============================================================================
class TBInjector:
    """
    场景注入器 - 将LLM生成的测试代码注入到现有测试平台
    
    集成三层防护策略：
    1. Layer 1: Prompt约束（由CoverageParser处理）
    2. Layer 2: 智能代码转换
    3. Layer 3: 质量评估和重试建议
    """
    
    def __init__(self, tb_code):
        """
        初始化注入器
        
        Args:
            tb_code: 原始测试平台代码字符串
        """
        self.content = tb_code
        self.validator = BlackBoxValidator()
        self.validator._extract_signals_from_tb(tb_code)
        self.last_validation_result = None

    def inject(self, new_code, iter_idx):
        """
        注入新的测试场景到测试平台
        
        Args:
            new_code: LLM生成的测试代码
            iter_idx: 迭代序号
            
        Returns:
            修改后的测试平台代码
        """
        # Step 1: 预处理代码（包含三层防护）
        scenario_code, result = self._preprocess_code(new_code, iter_idx)
        
        self.last_validation_result = result
        
        # 记录日志
        if result['violations']['critical']:
            logger.warning(f"[CGA-{iter_idx}] Critical violations detected:")
            for v in result['violations']['critical']:
                logger.warning(f"  - {v}")
        
        if result['violations']['warning']:
            logger.info(f"[CGA-{iter_idx}] Warnings:")
            for v in result['violations']['warning']:
                logger.info(f"  - {v}")
        
        if result['transformations']:
            logger.info(f"[CGA-{iter_idx}] Code transformations applied:")
            for t in result['transformations']:
                logger.info(f"  - {t['type']}: {t.get('original', 'N/A')[:50]}...")
        
        # Step 2: 构建场景块
        scenario_block = self._build_scenario_block(scenario_code, iter_idx)
        
        # Step 3: 注入到TB中
        modified_tb = self._inject_scenario(scenario_block)
        
        return modified_tb

    def should_retry(self):
        """是否应该重试"""
        if self.last_validation_result is None:
            return False
        return self.last_validation_result.get('should_retry', False)

    def get_quality_score(self):
        """获取代码质量分数"""
        if self.last_validation_result is None:
            return 0
        return self.last_validation_result.get('quality_score', 0)

    def _preprocess_code(self, code, iter_idx):
        """预处理LLM生成的代码 - 增强版，包含语法预检查"""
        # 移除markdown标记
        code = re.sub(r'```(?:verilog|systemverilog|sv)?\n?', '', code)
        code = re.sub(r'```', '', code)

        # 移除task包装
        code = re.sub(r'task\s+\w+\s*(?:\([^)]*\))?\s*;', '', code)
        code = re.sub(r'endtask', '', code)

        # 移除$finish和$stop
        code = re.sub(r'\$finish\s*;', '', code)
        code = re.sub(r'\$stop\s*;', '', code)

        # 移除多余空行
        code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)

        
        # [新增] 移除 initial begin ... end 代码块
        # LLM 可能生成完整的 initial begin...end 块，但我们只需要其中的测试代码
        initial_pattern = re.compile(r'\binitial\s+begin\b.*?\bend\b', re.DOTALL | re.IGNORECASE)
        
        # 检查并移除 initial begin ... end 块
        initial_match = initial_pattern.search(code)
        if initial_match:
            logger.warning(f"[CGA-{iter_idx}] Detected 'initial begin...end' block in generated code - this should not be included")
            logger.warning(f"[CGA-{iter_idx}] Removing 'initial begin...end' wrapper, keeping only the test content")
            # 提取块内的内容
            block_content = initial_match.group(0)
            # 移除 initial begin 和 end 包装
            # 保留块内的实际测试代码
            inner_content = re.sub(r'^\s*initial\s+begin\s*', '', block_content)
            inner_content = re.sub(r'\bend\s*$', '', inner_content)
            # 替换整个块为内部内容
            code = initial_pattern.sub(inner_content.strip(), code, count=1)

        code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)

        
        # 信号名自动修正（在验证之前）
        code = self._auto_correct_signal_names(code)

        # 三层防护：黑盒约束验证和转换
        code, result = self.validator.validate_and_transform(code, self.content)

        # [新增] 第四层：Verilog 语法预检查
        # 提取完整 TB 中已声明的信号（不只是代码片段）
        signal_widths = self._extract_signal_widths()
        declared_signals = self._extract_declared_signals()
        
        # 调用语法检查，传入已声明信号列表
        syntax_result = self.validator.check_syntax_issues(
            code, 
            signal_widths,
            declared_signals=declared_signals
        )

        # 合并检查结果
        result['syntax_check'] = syntax_result

        # 记录语法问题日志
        if syntax_result['width_mismatch']:
            logger.warning(f"[CGA-{iter_idx}] Width mismatch detected:")
            for issue in syntax_result['width_mismatch']:
                logger.warning(f"  - {issue['message']}")
                if 'suggestion' in issue:
                    logger.info(f"    Suggestion: {issue['suggestion']}")

        if syntax_result['logic_issues']:
            logger.warning(f"[CGA-{iter_idx}] Logic issues detected:")
            for issue in syntax_result['logic_issues']:
                logger.warning(f"  - {issue['message']}")
                if 'suggestion' in issue:
                    logger.info(f"    Suggestion: {issue['suggestion']}")

        if syntax_result['syntax_warnings']:
            for issue in syntax_result['syntax_warnings']:
                if issue['severity'] == 'error':
                    logger.error(f"[CGA-{iter_idx}] Syntax error: {issue['message']}")
                else:
                    logger.warning(f"[CGA-{iter_idx}] Syntax warning: {issue['message']}")

        # 如果语法检查发现问题，设置 should_retry
        if syntax_result['should_retry']:
            result['should_retry'] = True
            logger.warning(f"[CGA-{iter_idx}] Syntax issues detected, recommend retry with corrected code")

        code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)

        return code.strip(), result

    def _extract_declared_signals(self) -> set:
        """从完整测试平台中提取所有已声明的信号"""
        signals = set()
        
        # 匹配 reg [N:0] signal 或 wire [N:0] signal
        for match in re.finditer(r'\b(reg|wire|logic)\s+(?:\[[^\]]+\]\s*)?(\w+)', self.content):
            signals.add(match.group(2))
        
        # 匹配 input/output 声明
        for match in re.finditer(r'\b(input|output|inout)\s+(?:\[[^\]]+\]\s*)?(\w+)', self.content):
            signals.add(match.group(2))
        
        # 匹配模块端口连接中的信号
        for match in re.finditer(r'\.(\w+)\s*\(\s*(\w+)\s*\)', self.content):
            signals.add(match.group(2))  # 添加连接的信号名
        
        return signals

    def _extract_signal_widths(self) -> Dict[str, int]:
        """从测试平台中提取信号位宽信息"""
        widths = {}

        # 匹配 reg [N:0] signal 或 wire [N:0] signal
        width_pattern = re.compile(r'\b(reg|wire)\s+\[(\d+):(\d+)\]\s+(\w+)')

        for match in width_pattern.finditer(self.content):
            high = int(match.group(2))
            low = int(match.group(3))
            width = high - low + 1
            signal = match.group(4)
            widths[signal] = width

        # 匹配无位宽声明的信号（默认 1 位）
        single_bit_pattern = re.compile(r'\b(reg|wire)\s+(?!.*\[)(\w+)\s*;')
        for match in single_bit_pattern.finditer(self.content):
            signal = match.group(2)
            if signal not in widths:
                widths[signal] = 1

        return widths
    
    def _auto_correct_signal_names(self, code: str) -> str:
        """自动修正信号名错误"""
        corrections = []
        
        # 获取正确的复位信号名
        reset_signal = self.validator._find_reset_signal()
        
        # 如果正确的复位信号不是 'reset'，则修正所有 'reset' 引用
        if reset_signal != "reset":
            # 匹配独立的 'reset' 单词（不包括 'areset', 'rst_n' 等）
            pattern = r'\breset\b(?!\w)'
            matches = re.findall(pattern, code)
            if matches:
                code = re.sub(pattern, reset_signal, code)
                corrections.append(f"reset -> {reset_signal} ({len(matches)} occurrences)")
        
        # 检查是否有使用 'rst' 但正确信号是 'areset' 的情况
        if reset_signal == "areset":
            pattern = r'\brst\b(?!\w)'
            matches = re.findall(pattern, code)
            if matches:
                code = re.sub(pattern, reset_signal, code)
                corrections.append(f"rst -> {reset_signal} ({len(matches)} occurrences)")
        
        # 检查是否使用了不存在的信号
        for signal in re.findall(r'\b(\w+)\s*=', code):
            signal = signal.strip()
            # 跳过已知的合法信号
            if signal in self.validator.dut_inputs:
                continue
            # 检查是否是复位信号的别名
            if signal.lower() in ['reset', 'rst', 'rst_n', 'rst_b'] and reset_signal != signal:
                code = re.sub(rf'\b{signal}\b', reset_signal, code)
                corrections.append(f"{signal} -> {reset_signal}")
        
        if corrections:
            logger.info(f"[Signal Correction] Applied corrections: {'; '.join(corrections)}")
        
        return code

    def _build_scenario_block(self, scenario_code, iter_idx):
        """构建完整的场景代码块"""
        # 格式化缩进
        lines = scenario_code.split('\n')
        formatted_lines = []
        for line in lines:
            stripped = line.strip()
            if stripped:
                formatted_lines.append(f"    {stripped}")
        formatted_code = '\n'.join(formatted_lines)
        
        # 检测输出信号用于日志
        output_signals = self._detect_output_signals()
        output_log = self._generate_output_log(output_signals, iter_idx)
        
        # 构建完整块
        block = f'''
    // ========== CGA Iteration {iter_idx} ==========
    scenario = 100 + {iter_idx};
    // Reset signals to safe state
{self._generate_signal_reset()}
    #5;
    // CGA generated test sequence:
{formatted_code}
    // Log results
{output_log}
    // ==============================================
'''
        return block

    def _detect_output_signals(self):
        """检测DUT的输出信号"""
        outputs = []
        wire_pattern = re.compile(r'wire\s+(?:\[[\d:]+\]\s*)?(\w+)\s*;')
        for match in wire_pattern.finditer(self.content):
            signal = match.group(1)
            if signal.lower() not in ['clk', 'clock', 'rst', 'reset', 'areset']:
                outputs.append(signal)
        return outputs

    def _generate_signal_reset(self):
        """生成信号重置代码"""
        inputs = []
        reg_pattern = re.compile(r'reg\s+(?:\[[\d:]+\]\s*)?(\w+)\s*;')
        for match in reg_pattern.finditer(self.content):
            signal = match.group(1)
            if signal.lower() not in ['clk', 'clock', 'file', 'scenario']:
                inputs.append(signal)
        
        if inputs:
            return "    " + "; ".join([f"{sig} = 0" for sig in inputs]) + ";"
        return "    // No input signals to reset"

    def _generate_output_log(self, signals, iter_idx):
        """生成输出日志代码"""
        if not signals:
            return f'    $display("[CGA-{iter_idx}] Scenario executed");'
        
        sig_names = ", ".join(signals)
        format_str = ", ".join(["%b"] * len(signals))
        
        return f'    $fdisplay(file, "[CGA-{iter_idx}] {sig_names} = {format_str}", {sig_names});'

    def _inject_scenario(self, scenario_block):
        """将场景块注入到测试平台"""
        modified_tb = self.content
        
        # 策略：如果有 $fclose，在其之前插入
        if "$fclose" in modified_tb:
            modified_tb = re.sub(
                r'(\s*)(\$fclose\s*\([^)]+\)\s*;)',
                scenario_block + r'\1\2',
                modified_tb,
                count=1
            )
        elif "$finish" in modified_tb:
            # 否则在 $finish 之前插入
            modified_tb = modified_tb.replace(
                "$finish;",
                scenario_block + "\n    $finish;"
            )
        else:
            # 兜底：在最后一个 end 之前插入
            last_end = modified_tb.rfind("end")
            if last_end != -1:
                modified_tb = modified_tb[:last_end] + scenario_block + modified_tb[last_end:]
        
        return modified_tb