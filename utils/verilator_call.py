
# """
# Description :   Verilator wrapper for CGA (Coverage-Guided Agent)
# Author      :   CorrectBench Integration
# """
# import os
# import sys

# # === [Path Auto-Configuration] ===
# # 获取当前脚本的目录
# script_dir = os.path.dirname(os.path.abspath(__file__))

# # 智能判断项目根目录：
# # 如果当前目录下有 loader_saver.py，说明我们就在根目录
# if os.path.exists(os.path.join(script_dir, "loader_saver.py")):
#     project_root = script_dir
#     in_utils_folder = False
# else:
#     # 否则假设我们在 utils/ 子目录下，根目录在上级
#     project_root = os.path.dirname(script_dir)
#     in_utils_folder = True

# # 1. 确保项目根目录在 sys.path 中 (以便能 import utils, config 等)
# if project_root not in sys.path:
#     sys.path.insert(0, project_root)

# # 2. 只有当我们确实在 utils/ 子目录下运行时，才需要移除 script_dir
# # 这样可以避免 "import utils" 错误地导入了当前目录而不是 utils 包
# if in_utils_folder and script_dir in sys.path:
#     try:
#         sys.path.remove(script_dir)
#     except ValueError:
#         pass
# # =================================

# from utils.utils import run_in_dir
# from utils.subproc import subproc_call
# from loader_saver import autologger as logger

# # 假设 Verilator 在系统 PATH 中
# VERILATOR_BIN = "verilator"
# COVERAGE_BIN = "verilator_coverage"

# def verilator_run_coverage(run_dir, dut_file="DUT.v", tb_file="driver.v", top_module="top_module", timeout=120):
#     """
#     运行 Verilator 仿真流程：编译 -> 运行 -> 生成覆盖率 -> 标注
#     返回: [success, coverage_score, annotated_file_path]
#     """
    
#     # 1. 编译
#     # cmd_compile = f"{VERILATOR_BIN} --binary -j 0 --coverage {dut_file} {tb_file} --top-module {top_module}"
#     cmd_compile = f"{VERILATOR_BIN} --binary -j 0 --coverage -Wno-TIMESCALEMOD -Wno-fatal {dut_file} {tb_file} --top-module {top_module}"
#     # 2. 运行
#     cmd_run = f"./obj_dir/V{top_module}"
    
#     # 3. 标注
#     cmd_annotate = f"{COVERAGE_BIN} --annotate logs/annotated logs/coverage.dat"

#     with run_in_dir(run_dir):
#         # Step 1: Compile
#         res = subproc_call(cmd_compile, timeout)
#         if res["haserror"]:
#             logger.error(f"Verilator Compile Failed: {res['err']}")
#             return False, 0.0, None

#         # Step 2: Run
#         res = subproc_call(cmd_run, timeout)
#         if res["haserror"]:
#             logger.warning(f"Verilator Run Output: {res['err']}")

#         # Step 3: Annotate
#         if not os.path.exists("logs"):
#             os.makedirs("logs")
#         res = subproc_call(cmd_annotate, timeout)
#         if res["haserror"]:
#             logger.error(f"Verilator Annotation Failed: {res['err']}")
#             return False, 0.0, None

#         # Step 4: Find Annotated File & Calculate Score
#         annotated_dir = os.path.join(run_dir, "logs", "annotated")
#         target_file = None
        
#         if os.path.exists(annotated_dir):
#             for f in os.listdir(annotated_dir):
#                 # 排除 driver/testbench，只找 DUT
#                 if (os.path.basename(dut_file) in f or "DUT" in f) and "driver" not in f and "tb" not in f.lower():
#                     target_file = os.path.join(annotated_dir, f)
#                     break
        
#         if not target_file:
#             logger.error(f"Could not find annotated DUT file in {annotated_dir}")
#             return False, 0.0, None

#         score = _quick_calc_score(target_file)
#         return True, score, target_file

# def _quick_calc_score(filepath):
#     try:
#         with open(filepath, 'r') as f:
#             lines = f.readlines()
#         total = 0
#         covered = 0
#         for line in lines:
#             if line.startswith('%') or line.strip().startswith('#'):
#                 total += 1
#                 if not (line.startswith('%000000') or line.strip().startswith('#')):
#                     covered += 1
#         return (covered / total * 100.0) if total > 0 else 0.0
#     except Exception:
#         return 0.0

# if __name__ == "__main__":
#     print("--- Self-Test Mode: Initializing CorrectBench Environment ---")
    
#     try:
#         from config import Config
#         from loader_saver import AutoLogger
        
#         # 初始化配置，优先寻找 custom.yaml
#         custom_cfg_path = os.path.join(project_root, "config/custom.yaml")
#         if os.path.exists(custom_cfg_path):
#             Config(custom_cfg_path)
#         else:
#             Config() # 使用默认配置
            
#         # 启动日志
#         AutoLogger()
#         print("--- Environment Initialized. Starting Verilator Test ---")
        
#     except Exception as e:
#         print(f"Environment Init Failed: {e}")
#         # 如果不是在 CorrectBench 环境下，可能无法继续
#         sys.exit(1)

#     # === 开始测试 ===
#     if len(sys.argv) < 3:
#         print("Usage: python3 verilator_call.py <run_dir> <dut_file> <tb_file>")
#         print("Example: python3 verilator_call.py saves/lemmings4 prob_lemmings4.v final_TB.v")
#     else:
#         run_dir = sys.argv[1]
#         dut = sys.argv[2]
#         tb = sys.argv[3]
        
#         success, score, path = verilator_run_coverage(run_dir, dut, tb)
#         print(f"\n[Test Result]\nSuccess: {success}\nScore: {score:.2f}%\nAnnotated File: {path}")
"""
Description :   Verilator wrapper for CGA - AUTO TOP-MODULE DETECTION
Author      :   CorrectBench Integration
"""
import os
import sys
import shutil
import re # 引入正则

# === [Path Auto-Configuration] ===
script_dir = os.path.dirname(os.path.abspath(__file__))
if os.path.exists(os.path.join(script_dir, "loader_saver.py")):
    project_root = script_dir
    in_utils_folder = False
else:
    project_root = os.path.dirname(script_dir)
    in_utils_folder = True

if project_root not in sys.path:
    sys.path.insert(0, project_root)

if in_utils_folder and script_dir in sys.path:
    try:
        sys.path.remove(script_dir)
    except ValueError:
        pass
# =================================

from utils.utils import run_in_dir
from utils.subproc import subproc_call
from loader_saver import autologger as logger

VERILATOR_BIN = "verilator"
COVERAGE_BIN = "verilator_coverage"

def get_module_name(file_path):
    """
    从 Verilog 文件中解析 module name
    """
    if not os.path.exists(file_path):
        return None
    try:
        with open(file_path, 'r') as f:
            content = f.read()
        # 匹配: module 名字 (忽略前面的空白，甚至可能有参数)
        # 简单匹配 module xxx; 或 module xxx (
        match = re.search(r'^\s*module\s+(\w+)', content, re.MULTILINE)
        if match:
            return match.group(1)
    except Exception:
        pass
    return None

def verilator_run_coverage(run_dir, dut_file="DUT.v", tb_file="driver.v", top_module="top_module", timeout=120):
    
    abs_run_dir = os.path.abspath(run_dir)
    abs_dut = os.path.abspath(os.path.join(run_dir, dut_file))
    abs_tb = os.path.abspath(os.path.join(run_dir, tb_file))
    abs_obj_dir = os.path.join(abs_run_dir, "obj_dir")
    abs_annotated = os.path.join(abs_run_dir, "logs", "annotated")
    

    # 如果 tb_file 存在，优先从 tb_file 里找模块名，而不是用默认的 "top_module"
    # 因为想仿真 Testbench，而不是裸的 DUT
    detected_top = get_module_name(abs_tb)
    if detected_top:
        print(f"[DEBUG] Auto-detected top module from {os.path.basename(tb_file)}: '{detected_top}'")
        real_top_module = detected_top
    else:
        print(f"[DEBUG] Could not detect top module, using default: '{top_module}'")
        real_top_module = top_module

    # 清理旧编译
    if os.path.exists(abs_obj_dir):
        shutil.rmtree(abs_obj_dir)
    
    # 构建编译命令
    # 注意：这里只通过 --top-module 指定顶层
    cmd_compile = (
        f"{VERILATOR_BIN} --binary -j 0 --coverage --timing "
        f"-Wno-TIMESCALEMOD -Wno-fatal -Wno-STMTDLY "
        f"--Mdir {abs_obj_dir} "
        f"{abs_dut} {abs_tb} --top-module {real_top_module}"
    )
    
    cmd_run = f"{abs_obj_dir}/V{real_top_module}"
    cmd_annotate = f"{COVERAGE_BIN} --annotate {abs_annotated} coverage.dat"

    with run_in_dir(abs_run_dir):
        # Step 1: Compile
        if os.path.exists("coverage.dat"): os.remove("coverage.dat")
        
        # print(f"[DEBUG] Compiling...")
        res = subproc_call(cmd_compile, timeout)
        
        if not os.path.exists(f"{abs_obj_dir}/V{real_top_module}"):
            logger.error(f"Verilator Compile Failed.")
            if res['err']: print(f"[COMPILE STDERR]:\n{res['err']}")
            return False, 0.0, None

        # Step 2: Run
        # print(f"[DEBUG] Running Simulation...")
        res = subproc_call(cmd_run, timeout)
        
        # 打印输出，确认时间是否走动
        print(f"--- Simulation Output ({real_top_module}) ---")
        if res['out']: print(res['out'])
        # if res['err']: print(res['err']) # Warnings
        
        if not os.path.exists("coverage.dat"):
            logger.error("coverage.dat not created.")
            return False, 0.0, None
        
        # Step 3: Annotate
        if not os.path.exists(abs_annotated):
            os.makedirs(abs_annotated)
        
        res = subproc_call(cmd_annotate, timeout)

        # Step 4: Find Annotated File (Target: DUT)
        target_file = None
        generated_files = os.listdir(abs_annotated) if os.path.exists(abs_annotated) else []
        
        if generated_files:
            for f in generated_files:
                # 我们的目标是看 DUT 的覆盖率
                # 排除 TB 文件
                is_dut = (os.path.basename(dut_file) in f) or \
                         (top_module in f) or \
                         ("DUT" in f)
                is_tb = ("driver" in f) or \
                        ("tb" in f.lower() and "tb" not in os.path.basename(dut_file).lower())
                
                # 如果自动侦测的顶层名出现在文件名里（例如 testbench.v），也要排除
                if real_top_module in f:
                    is_tb = True

                if is_dut and not is_tb:
                    target_file = os.path.join(abs_annotated, f)
                    break
        
        if not target_file:
            logger.error(f"Could not find annotated DUT file in {generated_files}")
            return False, 0.0, None

        score = _quick_calc_score(target_file)
        return True, score, target_file

# def _quick_calc_score(filepath):
#     try:
#         with open(filepath, 'r') as f:
#             lines = f.readlines()
#         total = 0
#         covered = 0
#         for line in lines:
#             if line.startswith('%') or line.strip().startswith('#'):
#                 total += 1
#                 if not (line.startswith('%000000') or line.strip().startswith('#')):
#                     covered += 1
#         return (covered / total * 100.0) if total > 0 else 0.0
#     except Exception:
#         return 0.0

def _quick_calc_score(filepath):
    """
    计算 Verilator 覆盖率文件的覆盖率分数
    
    支持的格式：
    - %NNNNNN: 行覆盖计数（%000000 表示未执行）
    - ~NNNNNN: 分支/条件覆盖计数
    -  NNNNNN: 空格开头+数字（某些 Verilator 版本）
    - ^NNNNNN: 未覆盖分支标记
    """
    import re
    
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
        
        # 匹配各种覆盖率标记格式
        pct_pattern = re.compile(r'^%(\d+)\s+')   # %NNNNNN code
        tilde_pattern = re.compile(r'^~(\d+)\s+') # ~NNNNNN code
        caret_pattern = re.compile(r'^\^(\d+)\s+') # ^NNNNNN code
        plain_pattern = re.compile(r'^\s*(\d+)\s+') # "NNNNNN" or " NNNNNN"
        
        # 过滤声明语句（不计入覆盖率）
        decl_pattern = re.compile(r'^\s*(input|output|inout|wire|reg|logic|parameter|localparam|assign)\b')
        
        total = 0
        covered = 0
        
        for line in lines:
            line_stripped = line.strip()
            if not line_stripped:
                continue
            
            count = -1
            is_covered = False
            
            # 尝试匹配各种格式
            match_pct = pct_pattern.match(line_stripped)
            match_tilde = tilde_pattern.match(line_stripped)
            match_caret = caret_pattern.match(line_stripped)
            match_plain = plain_pattern.match(line_stripped)
            
            if match_pct:
                count = int(match_pct.group(1))
                # 获取代码部分用于过滤
                code_part = line_stripped[7:].strip() if len(line_stripped) > 7 else ""
                if not decl_pattern.match(code_part):
                    total += 1
                    if count > 0:
                        covered += 1
            elif match_tilde:
                count = int(match_tilde.group(1))
                code_part = line_stripped[7:].strip() if len(line_stripped) > 7 else ""
                if not decl_pattern.match(code_part):
                    total += 1
                    if count > 0:
                        covered += 1
            elif match_caret:
                # ^ 表示未覆盖分支
                code_part = line_stripped[7:].strip() if len(line_stripped) > 7 else ""
                if not decl_pattern.match(code_part):
                    total += 1
                    # caret 表示未覆盖，不计入 covered
            elif match_plain:
                count = int(match_plain.group(1))
                # 计算数字部分的长度
                num_str = match_plain.group(1)
                code_part = line_stripped[len(num_str):].strip()
                if not decl_pattern.match(code_part):
                    total += 1
                    if count > 0:
                        covered += 1
        
        return (covered / total * 100.0) if total > 0 else 0.0
    except Exception as e:
        print(f"[DEBUG] _quick_calc_score error: {e}")
        return 0.0


if __name__ == "__main__":
    try:
        from config import Config
        from loader_saver import AutoLogger
        custom_cfg_path = os.path.join(project_root, "config/custom.yaml")
        if os.path.exists(custom_cfg_path): Config(custom_cfg_path)
        else: Config()
        AutoLogger()
    except Exception: sys.exit(1)

    if len(sys.argv) < 3:
        print("Usage: python3 verilator_call.py <run_dir> <dut_file> <tb_file>")
    else:
        run_dir = sys.argv[1]
        dut = sys.argv[2]
        tb = sys.argv[3]
        success, score, path = verilator_run_coverage(run_dir, dut, tb)
        print(f"\n[Test Result]\nSuccess: {success}\nScore: {score:.2f}%\nAnnotated File: {path}")