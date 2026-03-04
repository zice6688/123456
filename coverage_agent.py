import sys
import re
import os

class CoverageAnalyzer:
    def __init__(self, annotated_file_path):
        self.file_path = annotated_file_path
        self.source_code = self._load_file()
        self.module_name = self._extract_module_name()
        self.coverage_score = 0.0
        self.missing_blocks = []

    def _load_file(self):
        """加载文件内容，处理异常"""
        if not os.path.exists(self.file_path):
            raise FileNotFoundError(f"Cannot find file: {self.file_path}")
        with open(self.file_path, 'r', encoding='utf-8') as f:
            return f.readlines()

    def _extract_module_name(self):
        """通用化步骤1：自动从代码中提取 module name"""
        for line in self.source_code:
            match = re.search(r'module\s+(\w+)', line)
            if match:
                return match.group(1)
        return "unknown_module"

    def analyze(self):
        """核心分析逻辑：计算分数并提取未覆盖块"""
        total_lines = 0
        covered_lines = 0
        current_block = []
        recording = False

        for i, line in enumerate(self.source_code):
            # === [修复点] 安检门：如果行是空的，直接跳过 ===
            if not line.strip():
                continue

            # 判定行类型
            is_missed = line.startswith('%000000') or line.strip().startswith('#')
            is_covered = line.startswith('%') and not is_missed
            
            # 统计分数
            if is_missed or is_covered:
                total_lines += 1
                if is_covered:
                    covered_lines += 1

            # === [修复点] 安全切分：防止切割失败 ===
            parts = line.split(maxsplit=1)
            if len(parts) < 2:
                # 如果这一行切不出两部分（比如只有标号没有代码），也跳过
                continue
            
            clean_code = parts[-1].strip()
            # 过滤掉非实质性代码
            is_substantive = len(clean_code) > 3 and not clean_code.startswith("//")

            if is_missed and is_substantive:
                if not recording:
                    recording = True
                    # 添加上下文 (尝试找前一行非空行作为上下文比较复杂，这里简化处理)
                    if i > 0 and self.source_code[i-1].strip():
                         prev_parts = self.source_code[i-1].split(maxsplit=1)
                         if len(prev_parts) >= 2:
                            prev_code = prev_parts[-1].strip()
                            current_block.append(f"Line {i}: {prev_code} ...")
                current_block.append(f"Line {i+1}: {clean_code} <--- MISSING")
            else:
                if recording:
                    recording = False
                    self.missing_blocks.append(current_block)
                    current_block = []

        # 计算最终分数
        if total_lines > 0:
            self.coverage_score = (covered_lines / total_lines) * 100.0
        
        return self.coverage_score

    def generate_prompt(self):
        """通用化步骤2：使用模板生成 Prompt"""
        prompt_template = """
You are an expert FPGA verification engineer.
I am verifying a Verilog module named '{module_name}'.
The current testbench achieves only {score:.2f}% coverage.
The following logic blocks are NEVER executed during simulation:

{missing_logic_str}

[Task]
Please write a NEW SystemVerilog task to target these specific missing scenarios.
1. Analyze WHY these lines are not executed (e.g., specific counter value, rare state transition).
2. Generate a task named 'test_coverage_fix' that drives inputs to trigger these conditions.
3. Return ONLY the code block.
"""
        blocks_str = ""
        for idx, block in enumerate(self.missing_blocks[:4]): 
            blocks_str += f"--- Missing Scenario {idx+1} ---\n"
            blocks_str += "\n".join(block)
            blocks_str += "\n\n"

        if not blocks_str:
            blocks_str = "(No significant missing logic found. Coverage is likely high.)"

        return prompt_template.format(
            module_name=self.module_name,
            score=self.coverage_score,
            missing_logic_str=blocks_str
        )

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 coverage_agent.py <annotated_file_path>")
        sys.exit(1)
    
    agent = CoverageAnalyzer(sys.argv[1])
    score = agent.analyze()
    
    print(f"--- Analysis Report for {agent.module_name} ---")
    print(f"Score: {score:.2f}%")
    print("-" * 30)
    print(agent.generate_prompt())