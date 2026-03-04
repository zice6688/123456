"""
Description :   Utils for CGA (CoverageParser & TBInjector)
                - Features: Sticky Mode, Smart Noise Filtering (No assign/decls)
Author      :   CorrectBench Integration
"""
import re
import os

class CoverageParser:
    def __init__(self, annotated_file):
        self.file_path = annotated_file
        # 匹配: %000000 ...
        self.line_pattern = re.compile(r'^%(\d+)\s+(.*)$')
        # 匹配: ~000000 ...
        self.tilde_pattern = re.compile(r'^~(\d+)\s+(.*)$')
        
        # [关键修改] 加入 assign 到声明列表
        self.decl_pattern = re.compile(r'^\s*(input|output|inout|wire|reg|logic|parameter|localparam|assign)\b')

    def generate_prompt(self, current_score):
        if not os.path.exists(self.file_path): return None

        try:
            with open(self.file_path, 'r', encoding='utf-8', errors='ignore') as f: 
                lines = f.readlines()
        except Exception: return None

        missing_blocks = []
        current_block = []
        recording = False
        
        context_buffer = [] 
        CONTEXT_SIZE = 3 

        for i, line in enumerate(lines):
            line = line.strip()
            
            # --- 1. 解析 ---
            count = -1
            clean_code = line
            is_tilde = False

            match_pct = self.line_pattern.match(line)
            match_tilde = self.tilde_pattern.match(line)

            if match_pct:
                count = int(match_pct.group(1))
                clean_code = match_pct.group(2).strip()
            elif match_tilde:
                count = int(match_tilde.group(1))
                clean_code = match_tilde.group(2).strip()
                is_tilde = True
            elif line.startswith('^'): 
                count = 0
                clean_code = line[1:].strip()
            
            if "//" in clean_code: clean_code = clean_code.split("//")[0].strip()

            # --- 2. 智能噪音过滤 (Smart Filter) ---
            
            # [A] 强噪音 (Hard Noise): 无论多长，只要匹配就一定要过滤掉
            # 包括：变量声明、assign赋值、模块结束符
            is_hard_noise = (
                self.decl_pattern.match(clean_code) or 
                clean_code == "endmodule"
            )

            # [B] 软噪音 (Soft Noise): 只有当长度很短时才过滤
            # 我们想保留 'always @(...)' 这种长语句作为上下文，但去掉单独的 'end' / 'begin'
            is_soft_noise = (
                len(clean_code) < 2 or 
                clean_code in ["end", "begin", "else", ");", "endcase", "default:"] or
                clean_code.startswith("module ") or
                not any(c.isalnum() for c in clean_code)
            )

            is_definitely_covered = (not is_tilde and count > 0)
            is_definitely_missed = (not is_tilde and count == 0 and not is_hard_noise and not is_soft_noise)

            # --- 3. 录制逻辑 ---
            if recording:
                if is_definitely_covered:
                    # 遇到明确覆盖行 -> 结束录制
                    missing_blocks.append(current_block)
                    current_block = []
                    recording = False
                    # 把这一行加入 Context 供下一块使用 (除非是强噪音)
                    if not is_hard_noise:
                        context_buffer.append(clean_code)
                else:
                    # 录制中 (包括 Miss, Tilde, Noise)
                    # [关键修改] 只有当它不是强噪音，且不是短的软噪音时，才录入 Block
                    if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
                        current_block.append(f"Line {i+1}: {clean_code}")
            else:
                if is_definitely_missed:
                    # 开始录制
                    recording = True
                    if context_buffer:
                        current_block.append(f"... (Context)")
                        for ctx in context_buffer:
                            current_block.append(f"   {ctx}")
                    current_block.append(f"Line {i+1}: {clean_code}  <--- MISSING START")
                else:
                    # 维护上下文 Buffer
                    # 同样，强噪音不进 Buffer，软噪音太短不进 Buffer
                    if not is_hard_noise and not (is_soft_noise and len(clean_code) < 4):
                        context_buffer.append(clean_code)
                        if len(context_buffer) > CONTEXT_SIZE:
                            context_buffer.pop(0)
        
        if recording and current_block: missing_blocks.append(current_block)
        if not missing_blocks: return None

# === 4. 构建 Prompt (全量提取) ===
        selected_blocks = missing_blocks[:50] 
        
        prompt = f"""
Current testbench achieves {current_score:.2f}% coverage. 
Below is a LIST of logic blocks in the DUT that are NEVER executed. 
Some blocks might be related (e.g., part of the same FSM sequence).

Please analyze these missing blocks globally:
1. Identify the root cause (e.g., a specific state is never reached).
2. Group related missing blocks.
3. Write a NEW SystemVerilog task to trigger the MOST IMPORTANT missing logic first.

"""
        for idx, block in enumerate(selected_blocks): 
            prompt += f"--- Missing Logic Block {idx+1} ---\n" + "\n".join(block) + "\n\n"

# === [升级版 Prompt：解决参数错误 + 强化黑盒约束] ===
        prompt += """
    [Task Requirements]
    1. Return ONLY the SystemVerilog task code. 
    2. **NO ARGUMENTS**: The task must NOT have any inputs or outputs (e.g., `task my_task;` NOT `task my_task(input clk);`).
    3. **USE GLOBAL SIGNALS**: The task should directly drive the testbench variables (clk, areset, bump_left, dig, ground) which are already defined in the scope.
    4. Name the task 'test_coverage_fix_X' (X is the iteration number).
    5. Use 'repeat(N) @(posedge clk);' to wait for cycles.

    [CRITICAL CONSTRAINTS - READ CAREFULLY]
    1. **BLACK-BOX ONLY**: You CANNOT access internal signals like 'state', 'next_state', 'fall_counter', 'count'.
    2. **NO FORCE/ASSIGN**: Do NOT try to force internal values. To increase a counter, you must wait for enough clock cycles (e.g., `repeat(20) @(posedge clk);`).
    3. **INPUTS ONLY**: Control the FSM ONLY by driving the module inputs.
    """
        # =================================================
        return prompt

class TBInjector:
    def __init__(self, tb_code):
        self.content = tb_code

    def inject(self, new_task_code, iter_idx):
        task_code = re.sub(r'```.*?\n', '', new_task_code)
        task_code = re.sub(r'```', '', task_code).strip()
        
        task_name = f"test_coverage_fix_{iter_idx}"
        if re.search(r'task\s+\w+', task_code):
            task_code = re.sub(r'task\s+(\w+)', f'task {task_name}', task_code, count=1)
        else:
            task_code = f"task {task_name};\n{task_code}\nendtask"

        modified_tb = self.content

        if "endmodule" in modified_tb:
             modified_tb = re.sub(r'(\s*endmodule\s*$)', f"\n\n// CGA {iter_idx}\n{task_code}\n\\1", modified_tb, count=1)
        
        if "$finish" in modified_tb:
            modified_tb = modified_tb.replace("$finish;", f"\n    {task_name}();\n    $finish;")
        else:
            last_end = modified_tb.rfind("end")
            if last_end != -1:
                modified_tb = modified_tb[:last_end] + f"\n    {task_name}();\n" + modified_tb[last_end:]
        
        return modified_tb