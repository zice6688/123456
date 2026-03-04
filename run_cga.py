import sys
import os

# === 导入你的自定义模块 ===
from coverage_agent import CoverageAnalyzer  # "眼"
from tb_injector import TestbenchInjector    # "手"

# === 导入 CorrectBench 的核心模块 ===
# 假设你的 GPT_call.py 文件就在根目录，如果是在 utils 文件夹下，请改为 from utils.GPT_call import ...
try:
    from GPT_call import llm_call, extract_code 
except ImportError:
    # 尝试从 utils 导入 (根据你的文件结构调整)
    sys.path.append(os.path.join(os.path.dirname(__file__), 'utils'))
    from GPT_call import llm_call, extract_code

def main(annotated_file, tb_file):
    print(f"--- [CGA] Starting Coverage-Guided Agent Loop ---")
    
    # 1. 初始化眼 (CoverageAnalyzer)
    print(f"--- Step 1: Analyzing Coverage for {annotated_file} ---")
    analyzer = CoverageAnalyzer(annotated_file)
    score = analyzer.analyze()
    print(f"   Current Score: {score:.2f}%")
    
    # 设定目标阈值
    if score > 95.0:
        print("   [Success] Coverage is already high. No action needed.")
        return

    # 2. 生成 Prompt (由覆盖率报告驱动)
    prompt = analyzer.generate_prompt()
    print("   [Info] Prompt generated successfully.")

    # 3. 调用 CorrectBench 的大脑 (GPT_call)
    print("--- Step 2: Asking LLM for Fix (via CorrectBench Infra) ---")
    
    # 构建消息格式 (CorrectBench 标准格式)
    messages = [{"role": "user", "content": prompt}]
    
    # === 关键集成点 ===
    # 使用 Qwen-max 或你配置里的任何模型
    # 注意：确保你的 config/key_API.json 或环境变量配置正确
    target_model = "qwen-max" 
    
    try:
        response_text, other_infos = llm_call(
            input_messages=messages,
            model=target_model,
            system_message="You are a Verilog expert specializing in testbench generation.",
            temperature=0.2 # 保持低温度以获得稳定代码
        )
        print(f"   [LLM] Response received. Tokens used: {other_infos['usage']['total_tokens']}")
        
    except Exception as e:
        print(f"   [Error] LLM Call failed: {e}")
        return

    # 4. 提取代码
    # 直接复用 GPT_call 里的 extract_code 函数
    codes = extract_code(response_text, "verilog") # 或者是 "systemverilog"
    
    if not codes:
        print("   [Error] No code block found in LLM response.")
        return
        
    fix_code = codes[0] # 取第一个代码块

    # 5. 注入代码 (手术)
    print("--- Step 3: Injecting Code into Testbench ---")
    injector = TestbenchInjector(tb_file)
    try:
        new_tb_path = injector.inject_task(fix_code, new_tb_path="enhanced_tb.v")
        print(f"   [Success] Enhanced Testbench saved to: {new_tb_path}")
        print("   -> Now you can run simulation with 'enhanced_tb.v' to verify improvement.")
    except Exception as e:
        print(f"   [Error] Injection failed: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 run_cga.py <annotated_file_path> <original_tb_path>")
        print("Example: python3 run_cga.py logs/annotated/prob_lemmings4.v saves/lemmings4/final_TB.v")
    else:
        main(sys.argv[1], sys.argv[2])