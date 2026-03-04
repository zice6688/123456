import streamlit as st
import json
import yaml
import os
import subprocess
import time
import glob
import pandas as pd

# ==================== 配置 ====================
ORIGINAL_DATASET = "data/HDLBits/HDLBits_data.jsonl"  # 原始 156 题数据集
TEMP_DATASET = "data/temp_single_task.jsonl"          # 临时单题数据集
CONFIG_FILE = "config/custom.yaml"
LOG_FILE = "research_run.log"
SAVES_DIR = "saves"

st.set_page_config(page_title="Week 1: 基线构建工具", layout="wide", page_icon="🔬")

st.title("🔬 CorrectBench 基线研究平台 (Baseline Research)")
st.markdown("""
**当前阶段**：Week 1 - 建立“低覆盖率”基线
**目标**：运行 SOTA 工具，获取 Generated TB，并观察其在 Mutation Test (Eval2) 中的表现，以证明其覆盖率不足。
""")
st.divider()

# ==================== 功能函数 ====================
@st.cache_data
def load_dataset_options():
    """读取原始数据集，返回题目列表"""
    tasks = []
    if os.path.exists(ORIGINAL_DATASET):
        with open(ORIGINAL_DATASET, 'r', encoding='utf-8') as f:
            for line in f:
                try:
                    data = json.loads(line)
                    # 提取 task_id 和 简短描述
                    t_id = data.get('task_id', 'Unknown')
                    desc = data.get('detail_description', '')[:60] + "..."
                    tasks.append(f"{t_id} | {desc}")
                except:
                    pass
    return tasks

def extract_task_id(selection_str):
    return selection_str.split(" | ")[0].strip()

# ==================== 第一步：选择现有题目 ====================
st.sidebar.header("1. 题目选择 (Benchmark Selection)")
task_options = load_dataset_options()

if not task_options:
    st.error(f"❌ 未找到数据集文件: `{ORIGINAL_DATASET}`，请检查路径。")
    st.stop()

selected_option = st.sidebar.selectbox("选择测试题目 (Select Task)", task_options)
selected_task_id = extract_task_id(selected_option)

# 显示题目详情
st.subheader(f"📌 当前研究对象: `{selected_task_id}`")
# 读取该题的完整信息
task_full_data = None
with open(ORIGINAL_DATASET, 'r', encoding='utf-8') as f:
    for line in f:
        if f'"{selected_task_id}"' in line:
            task_full_data = json.loads(line)
            break

if task_full_data:
    with st.expander("查看题目完整规格说明 (Spec & Prompt)", expanded=False):
        st.json(task_full_data)
else:
    st.warning("读取题目详情失败。")

# ==================== 第二步：环境配置与运行 ====================
st.sidebar.header("2. 运行控制")
model_select = st.sidebar.selectbox("模型选择", ["qwen-plus", "qwen-max"], index=0)

if st.sidebar.button("🚀 启动基线测试 (Run Baseline)", type="primary"):
    # 1. 创建单题临时数据集
    if task_full_data:
        # 强制修正 task_number 为 1，防止 CorrectBench 索引报错
        task_full_data['task_number'] = 1 
        with open(TEMP_DATASET, 'w', encoding='utf-8') as f:
            f.write(json.dumps(task_full_data) + "\n")
        st.toast(f"✅ 已构建单任务数据集: {TEMP_DATASET}")
    
    # 2. 修改 Config
    with open(CONFIG_FILE, 'r', encoding='utf-8') as f:
        config = yaml.safe_load(f)
    
    config['autoline']['probset']['path'] = TEMP_DATASET
    config['gpt']['model'] = model_select
    config['gpt']['rtlgen_model'] = model_select
    
    with open(CONFIG_FILE, 'w', encoding='utf-8') as f:
        yaml.dump(config, f, default_flow_style=False)
    
    # 3. 启动进程
    with open(LOG_FILE, "w") as f: f.write("--- Research Baseline Run Started ---\n")
    
    cmd = f"python -u main.py -c {CONFIG_FILE} > {LOG_FILE} 2>&1"
    subprocess.Popen(cmd, shell=True)
    st.session_state.running_task = selected_task_id
    st.rerun()

# ==================== 第三步：实时监控 ====================
col1, col2 = st.columns([3, 2])

with col1:
    st.subheader("📺 终端运行监控 (Terminal Output)")
    log_placeholder = st.empty()
    
    # 自动刷新日志逻辑
    if 'running_task' in st.session_state and st.session_state.running_task == selected_task_id:
        if st.button("🛑 停止刷新"):
            del st.session_state.running_task
            st.rerun()
            
        # 读取最后 50 行日志
        if os.path.exists(LOG_FILE):
            with open(LOG_FILE, "r", encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()
                log_content = "".join(lines[-50:])
                log_placeholder.code(log_content, language="bash")
        
        time.sleep(1)
        st.rerun()
    else:
        # 静态显示
        if os.path.exists(LOG_FILE):
            with open(LOG_FILE, "r", encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()
                log_placeholder.code("".join(lines[-50:]), language="bash")

# ==================== 第四步：证据收集 (LLM & Final TB) ====================
with col2:
    st.subheader("🕵️ 证据收集箱")
    
    result_dir = os.path.join(SAVES_DIR, selected_task_id)
    
    tab1, tab2, tab3 = st.tabs(["📄 Final Testbench", "🤖 LLM 交互", "📊 覆盖率/Eval结果"])
    
    # --- Tab 1: Final TB ---
    with tab1:
        if os.path.exists(result_dir):
            tb_files = glob.glob(os.path.join(result_dir, "*_tb.v"))
            # 优先找 prob_xxx_tb.v
            target_tb = os.path.join(result_dir, f"prob_{selected_task_id}_tb.v")
            
            if os.path.exists(target_tb):
                st.success("✅ 找到最终 TB")
                with open(target_tb, 'r') as f:
                    st.code(f.read(), language="verilog")
            elif tb_files:
                st.warning("未找到标准命名 TB，展示第一个发现的 TB")
                with open(tb_files[0], 'r') as f:
                    st.code(f.read(), language="verilog")
            else:
                st.info("等待生成...")
        else:
            st.info("任务尚未启动或目录不存在")

    # --- Tab 2: LLM 回复监控 ---
    with tab2:
        # CorrectBench 的 prompt 交互通常分散在日志或临时文件中
        # 这里我们尝试读取 run_info.txt 或直接解析主日志中的 prompt 部分
        if os.path.exists(result_dir):
            log_files = glob.glob(os.path.join(result_dir, "*.txt")) # 通常 run_info.txt 在这
            if log_files:
                selected_log = st.selectbox("选择日志文件", [os.path.basename(f) for f in log_files])
                with open(os.path.join(result_dir, selected_log), 'r') as f:
                    st.text_area("LLM Log", f.read(), height=400)
            else:
                st.info("暂无 LLM 交互日志")
        else:
            st.info("等待生成...")

    # --- Tab 3: 覆盖率证据 (Eval2) ---
    with tab3:
        st.markdown("### 关键证据：变异测试得分 (Mutation Score)")
        st.info("如果 Eval2 Ratio 低于 100%，即证明 SOTA 工具生成的 TB 无法覆盖所有 Bug。")
        
        # 尝试从 Main_Results 中解析结果
        main_results_root = "Main_Results/CorrectBench"
        if os.path.exists(main_results_root):
            # 找最新的结果文件夹
            all_dirs = [os.path.join(main_results_root, d) for d in os.listdir(main_results_root) if os.path.isdir(os.path.join(main_results_root, d))]
            if all_dirs:
                latest_dir = max(all_dirs, key=os.path.getmtime)
                jsonl_res = glob.glob(os.path.join(latest_dir, "*.jsonl"))
                
                if jsonl_res:
                    # 读取最后一行（对应当前任务）
                    with open(jsonl_res[0], 'r') as f:
                        lines = f.readlines()
                        for line in reversed(lines):
                            if selected_task_id in line:
                                res_data = json.loads(line)
                                
                                pass_rate = res_data.get('eval2_pass_ratio', 0)
                                is_pass = res_data.get('pass_eval2', False)
                                
                                st.metric("Eval2 Pass Ratio", f"{pass_rate*100:.0f}%")
                                if pass_rate < 1.0:
                                    st.error(f"⚠️ 发现覆盖率缺口！漏测率: {(1-pass_rate)*100:.0f}%")
                                    st.markdown(f"**结论**：`{selected_task_id}` 的 TB 虽然语法正确，但未能检测出所有变异 Bug，验证了本课题的研究动机。")
                                else:
                                    st.success("该任务覆盖率表现良好 (100%)，建议更换题目测试。")
                                break