# """
# Description :   Utils for CGA (CoverageParser & TBInjector)
#                 - Features: Sticky Mode, Smart Noise Filtering (No assign/decls)
# Author      :   CorrectBench Integration
# """
# import re
# import os

# class CoverageParser:
#     def __init__(self, annotated_file):
#         self.file_path = annotated_file
#         # 匹配: %000000 ...
#         self.line_pattern = re.compile(r'^%(\d+)\s+(.*)$')
#         # 匹配: ~000000 ...
#         self.tilde_pattern = re.compile(r'^~(\d+)\s+(.*)$')
        
#         # [关键修改] 加入 assign 到声明列表
#         self.decl_pattern = re.compile(r'^\s*(input|output|inout|wire|reg|logic|parameter|localparam|assign)\b')

#     def generate_prompt(self, current_score):
#         if not os.path.exists(self.file_path): return None

#         try:
#             with open(self.file_path, 'r', encoding='utf-8', errors='ignore') as f: 
#                 lines = f.readlines()
#         except Exception: return None

#         missing_blocks = []
#         current_block = []
#         recording = False
        
#         context_buffer = [] 
#         CONTEXT_SIZE = 3 

#         for i, line in enumerate(lines):
#             line = line.strip()
            
#             # --- 1. 解析 ---
#             count = -1
#             clean_code = line
#             is_tilde = False

#             match_pct = self.line_pattern.match(line)
#             match_tilde = self.tilde_pattern.match(line)

#             if match_pct:
#                 count = int(match_pct.group(1))
#                 clean_code = match_pct.group(2).strip()
#             elif match_tilde:
#                 count = int(match_tilde.group(1))
#                 clean_code = match_tilde.group(2).strip()
#                 is_tilde = True
#             elif line.startswith('^'): 
#                 count = 0
#                 clean_code = line[1:].strip()
            
#             if "//" in clean_code: clean_code = clean_code.split("//")[0].strip()

#             # --- 2. 智能噪音过滤 (Smart Filter) ---
            
#             # [A] 强噪音 (Hard Noise): 无论多长，只要匹配就一定要过滤掉
#             # 包括：变量声明、assign赋值、模块结束符
#             is_hard_noise = (
#                 self.decl_pattern.match(clean_code) or 
#                 clean_code == "endmodule"
#             )

#             # [B] 软噪音 (Soft Noise): 只有当长度很短时才过滤
#             # 我们想保留 'always @(...)' 这种长语句作为上下文，但去掉单独的 'end' / 'begin'
#             is_soft_noise = (
#                 len(clean_code) < 2 or 
#                 clean_code in ["end", "begin", "else", ");", "endcase", "default:"] or
#                 clean_code.startswith("module ") or
#                 not any(c.isalnum() for c in clean_code)
#             )

#             is_definitely_covered = (not is_tilde and count > 0)
#             is_definitely_missed = (not is_tilde and count == 0 and not is_hard_noise and not is_soft_noise)

#             # --- 3. 录制逻辑 ---
#             if recording:
#                 if is_definitely_covered:
#                     # 遇到明确覆盖行 -> 结束录制
#                     missing_blocks.append(current_block)
#                     current_block = []
#                     recording = False
#                     # 把这一行加入 Context 供下一块使用 (除非是强噪音)
#                     if not is_hard_noise:
#                         context_buffer.append(clean_code)
#                 else:
#                     # 录制中 (包括 Miss, Tilde, Noise)
#                     # [关键修改] 只有当它不是强噪音，且不是短的软噪音时，才录入 Block
#                     if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
#                         current_block.append(f"Line {i+1}: {clean_code}")
#             else:
#                 if is_definitely_missed:
#                     # 开始录制
#                     recording = True
#                     if context_buffer:
#                         current_block.append(f"... (Context)")
#                         for ctx in context_buffer:
#                             current_block.append(f"   {ctx}")
#                     current_block.append(f"Line {i+1}: {clean_code}  <--- MISSING START")
#                 else:
#                     # 维护上下文 Buffer
#                     # 同样，强噪音不进 Buffer，软噪音太短不进 Buffer
#                     if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
#                         context_buffer.append(clean_code)
#                         if len(context_buffer) > CONTEXT_SIZE:
#                             context_buffer.pop(0)
        
#         if recording and current_block: missing_blocks.append(current_block)
#         if not missing_blocks: return None

# # === 4. 构建 Prompt (全量提取) ===
#         selected_blocks = missing_blocks[:50] 
        
#         prompt = f"""
# Current testbench achieves {current_score:.2f}% coverage. 
# Below is a LIST of logic blocks in the DUT that are NEVER executed. 
# Some blocks might be related (e.g., part of the same FSM sequence).

# Please analyze these missing blocks globally:
# 1. Identify the root cause (e.g., a specific state is never reached).
# 2. Group related missing blocks.
# 3. Write a NEW SystemVerilog task to trigger the MOST IMPORTANT missing logic first.

# """
#         for idx, block in enumerate(selected_blocks): 
#             prompt += f"--- Missing Logic Block {idx+1} ---\n" + "\n".join(block) + "\n\n"

# # === [升级版 Prompt：解决参数错误 + 强化黑盒约束] ===
#             prompt += """
#             [OUTPUT REQUIREMENTS - CRITICAL]
#             1. Return ONLY Verilog test scenario code (NOT a task definition)
#             2. Your code will be inserted INTO an existing `initial begin ... end` block
#             3. DO NOT wrap your code in `task ... endtask`
#             4. DO NOT use `$finish` or `$stop`
# """
#         # =================================================
#         return prompt

# # class TBInjector:
# #     def __init__(self, tb_code):
# #         self.content = tb_code

# #     def inject(self, new_task_code, iter_idx):
# #         task_code = re.sub(r'```.*?\n', '', new_task_code)
# #         task_code = re.sub(r'```', '', task_code).strip()
        
# #         task_name = f"test_coverage_fix_{iter_idx}"
# #         if re.search(r'task\s+\w+', task_code):
# #             task_code = re.sub(r'task\s+(\w+)', f'task {task_name}', task_code, count=1)
# #         else:
# #             task_code = f"task {task_name};\n{task_code}\nendtask"

# #         modified_tb = self.content

# #         if "endmodule" in modified_tb:
# #              modified_tb = re.sub(r'(\s*endmodule\s*$)', f"\n\n// CGA {iter_idx}\n{task_code}\n\\1", modified_tb, count=1)
        
# #         if "$finish" in modified_tb:
# #             modified_tb = modified_tb.replace("$finish;", f"\n    {task_name}();\n    $finish;")
# #         else:
# #             last_end = modified_tb.rfind("end")
# #             if last_end != -1:
# #                 modified_tb = modified_tb[:last_end] + f"\n    {task_name}();\n" + modified_tb[last_end:]
        
# #         return modified_tb
# class TBInjector:
#     def __init__(self, tb_code):
#         self.content = tb_code

#     def inject(self, new_code, iter_idx):
#         """三个步骤：预处理 -> 构建场景块 -> 注入"""
#         scenario_code = self._preprocess_code(new_code, iter_idx)
#         scenario_block = self._build_scenario_block(scenario_code, iter_idx)
#         modified_tb = self._inject_scenario(scenario_block)
#         return modified_tb
    
#     def _preprocess_code(self, code, iter_idx):
#         """移除 task 包装、$finish 等"""
#         code = re.sub(r'task\s+\w+\s*(?:\([^)]*\))?\s*;', '', code)
#         code = re.sub(r'endtask', '', code)
#         return code.strip()
    
#     def _inject_scenario(self, scenario_block):
#         """核心：在 $fclose 之前插入（而非 $finish 之前）"""
#         if "$fclose" in modified_tb:
#             modified_tb = re.sub(
#                 r'(\s*)(\$fclose\s*\([^)]+\)\s*;)',
#                 scenario_block + r'\1\2',  # 场景 -> $fclose -> $finish
#                 modified_tb, count=1
#             )

"""
Description :   Utils for CGA (CoverageParser & TBInjector)
                - Features: Sticky Mode, Smart Noise Filtering (No assign/decls)
                - Enhanced: Three-layer protection for black-box constraints
                  * Layer 1: Enhanced Prompt constraints (prevention)
                  * Layer 2: Smart code transformation (conversion)
                  * Layer 3: Quality assessment & retry (fallback)
Author      :   CorrectBench Integration
"""
import re
import os
import logging
from typing import Tuple, List, Optional, Dict

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


# ============================================================================
# CoverageParser - 覆盖率解析器
# ============================================================================
class CoverageParser:
    """覆盖率解析器 - 从带注释的Verilog文件中提取未覆盖的代码块"""
    
    def __init__(self, annotated_file, tb_code=None):
        self.file_path = annotated_file
        self.tb_code = tb_code
        # 修复：Verilator 覆盖率标记格式为 %NNNNNN 或 ~NNNNNN 或 ^NNNNNN
        # %NNNNNN - 行覆盖计数（%000000 表示从未执行）
        # ~NNNNNN - 分支/条件覆盖计数
        # ^NNNNNN - 未覆盖的分支
        self.line_pattern = re.compile(r'^%(\d+)\s+(.*)$')  # 匹配 %NNNNNN code
        self.tilde_pattern = re.compile(r'^~(\d+)\s+(.*)$')  # 匹配 ~NNNNNN code
        self.caret_pattern = re.compile(r'^\^(\d+)\s+(.*)$')  # 匹配 ^NNNNNN code
        # 有些情况可能是纯数字开头（无前缀）
        self.plain_pattern = re.compile(r'^(\d+)\s+(.*)$')
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

            # 覆盖状态判断：
            # - %NNNNNN: count > 0 表示已覆盖，count == 0 表示未覆盖
            # - ~NNNNNN: 分支覆盖标记，需要进一步检查
            # - ^NNNNNN: 未覆盖分支标记
            is_definitely_covered = (not is_tilde and not is_caret and count > 0)
            is_definitely_missed = (not is_tilde and not is_caret and count == 0 and not is_hard_noise and not is_soft_noise) or \
                                   (is_caret and not is_hard_noise and not is_soft_noise)

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
        if not missing_blocks:
            return None

        selected_blocks = missing_blocks[:50]

        # 获取实际信号名用于示例
        reset_signal = self.validator._find_reset_signal()
        inputs_no_clk = [s for s in self.validator.dut_inputs if 'clk' not in s.lower()]
        example_signal = inputs_no_clk[0] if inputs_no_clk else (reset_signal if reset_signal != "reset" else "ena")
        
        # 分析 FSM 相关的缺失代码
        fsm_analysis = self._analyze_fsm_missing(missing_lines)

        prompt = f"""
[ROLE]
You are a hardware verification expert. Your task is to write a test scenario to improve code coverage.

[COVERAGE STATUS]
Current testbench achieves {current_score:.2f}% coverage.
The following logic blocks in the DUT are NEVER executed during simulation:

"""
        for idx, block in enumerate(selected_blocks):
            prompt += f"--- Missing Logic Block {idx+1} ---\n" + "\n".join(block) + "\n\n"

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
        return prompt
    
    def _analyze_fsm_missing(self, missing_lines: List[str]) -> str:
        """分析 FSM 相关的缺失代码，生成通用提示"""
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
        
        return "\n".join(analysis) if analysis else ""


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
        """预处理LLM生成的代码"""
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
        
        # 信号名自动修正（在验证之前）
        code = self._auto_correct_signal_names(code)
        
        # 三层防护：黑盒约束验证和转换
        code, result = self.validator.validate_and_transform(code, self.content)
        
        code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)
        
        return code.strip(), result
    
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