import json
import os
import sys

# ================= 配置 =================
# 数据集路径 (请确保指向你正在使用的那个文件)
DATASET_PATH = "data/HDLBits/HDLBits_data.jsonl" 
# 提取出的 RTL 存放目录 (建议直接放到 saves 方便一起找)
OUTPUT_BASE_DIR = "saves"

def extract_dut(task_id_target):
    found = False
    
    if not os.path.exists(DATASET_PATH):
        print(f"❌ 错误：找不到数据集文件 {DATASET_PATH}")
        return

    print(f"🔍 正在从 {DATASET_PATH} 中查找任务: {task_id_target} ...")

    with open(DATASET_PATH, 'r', encoding='utf-8') as f:
        for line in f:
            try:
                data = json.loads(line)
                current_task_id = data.get('task_id')

                if current_task_id == task_id_target:
                    # 找到目标任务
                    found = True
                    
                    # 尝试获取标准代码
                    # HDLBits 数据集通常用 'module_code' 或 'solution' 存标准答案
                    dut_code = data.get('module_code') or data.get('solution')
                    
                    if not dut_code:
                        print(f"❌ 错误：在数据集里找到了任务，但 'module_code' 字段为空！")
                        return

                    # 确定保存路径
                    save_dir = os.path.join(OUTPUT_BASE_DIR, task_id_target)
                    if not os.path.exists(save_dir):
                        os.makedirs(save_dir)
                        print(f"⚠️ 注意：创建了新目录 {save_dir}")

                    # 写入文件
                    # 文件名通常命名为 prob_<task_id>.v
                    filename = f"prob_{task_id_target}.v"
                    file_path = os.path.join(save_dir, filename)
                    
                    with open(file_path, 'w', encoding='utf-8') as vf:
                        vf.write(dut_code)
                    
                    print(f"✅ 成功！DUT 文件已提取到：")
                    print(f"   -> {file_path}")
                    print("\n现在你可以运行 Verilator 了：")
                    print(f"verilator --binary --timing --coverage -j 0 {filename} ...")
                    break
            except Exception as e:
                continue

    if not found:
        print(f"❌ 未找到任务 ID: {task_id_target}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python extract_dut.py <任务ID>")
        print("示例: python extract_dut.py fsm_serial")
    else:
        extract_dut(sys.argv[1])