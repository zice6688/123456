# #第四版

# """
# Description :   Coverage-Guided Agent (CGA) Main Controller
#                 - Integrated with Layer 0: Semantic Analysis
#                 - Integrated with Layer 1: Diversity Constraint Injection
#                 - Integrated with Layer 4: Energy Allocation
# Author      :   CorrectBench Integration
# """
# import os
# import sys
# import shutil

# import LLM_call as llm
# import loader_saver as ls
# from loader_saver import autologger as logger
# from utils.verilator_call import verilator_run_coverage
# from autoline.cga_utils import CoverageParser, TBInjector
# # [新增] 导入语义分析层
# from autoline.semantic_analyzer import SemanticAnalyzer, FunctionPointType
# # [新增] 导入能量分配层
# from autoline.energy_allocator import EnergyAllocator, EnergyState
# # [新增] 导入多样性约束注入器
# from autoline.diversity_injector import DiversityInjector
# # [新增] 导入测试历史管理器
# from autoline.test_history import TestHistoryManager

# class TaskTBCGA:
#     def __init__(self, task_dir, task_id, header, DUT_code, TB_code, config):
#         self.task_dir = task_dir
#         self.task_id = task_id
#         self.header = header
#         self.DUT_code = DUT_code
#         self.TB_code = TB_code
#         self.config = config
        
#         self.max_iter = 5  
#         self.target_coverage = 95.0
#         self.model = config.gpt.model  
        
#         self.best_tb = TB_code
#         self.best_score = 0.0
        
#         # [新增] 能量分配器
#         self.energy_allocator: EnergyAllocator = None
#         # [新增] 多样性约束注入器
#         self.diversity_injector: DiversityInjector = None

#     # [新增辅助函数] 从父目录拷贝 DUT
#     def _prepare_dut(self, target_dir):
#         source_dut = os.path.join(self.task_dir, "DUT.v")
#         target_dut = os.path.join(target_dir, "DUT.v")
        
#         # 优先拷贝现有的文件
#         if os.path.exists(source_dut):
#             shutil.copy(source_dut, target_dut)
#         else:
#             # 只有当文件由于某种原因被删除了，才降级使用内存中的 code
#             ls.save_code(self.DUT_code, target_dut)



#     def run(self):
#         logger.info(f"[{self.task_id}] Starting Coverage-Guided Agent (CGA)...")
        
#         # 1. 确保工作目录存在 (saves/任务名/5_CGA)
#         work_dir = os.path.join(self.task_dir, "5_CGA")
#         if os.path.exists(work_dir):
#             shutil.rmtree(work_dir)
#         os.makedirs(work_dir, exist_ok=True)

#         # === [新增] Step 0: 语义分析 ===
#         logger.info(f"[{self.task_id}] Running Semantic Analysis (Layer 0)...")
#         self.semantic_result = None
#         try:
#             semantic_analyzer = SemanticAnalyzer(self.DUT_code)
#             self.semantic_result = semantic_analyzer.analyze()
            
#             # 记录分析结果摘要
#             fp_count = len(self.semantic_result.get('function_points', []))
#             fsm_info = semantic_analyzer.get_fsm_info()
#             if fsm_info:
#                 logger.info(f"  FSM detected: {fsm_info.get('state_variable', 'unknown')} "
#                            f"({len(fsm_info.get('states', []))} states)")
#             logger.info(f"  Total function points identified: {fp_count}")
            
#             # 保存语义分析报告
#             semantic_report = semantic_analyzer.generate_prompt_context()
#             ls.save_code(semantic_report, os.path.join(work_dir, "semantic_analysis.txt"))
            
#             # === [新增] Step 0.1: 初始化能量分配器 ===
#             if self.semantic_result.get('function_points'):
#                 self.energy_allocator = EnergyAllocator(max_iterations=self.max_iter)
#                 energy_init_result = self.energy_allocator.initialize(
#                     self.semantic_result['function_points']
#                 )
#                 logger.info(f"  Energy allocator initialized: {energy_init_result['targets']} targets")
            
#             # === [新增] Step 0.2: 初始化多样性约束注入器 ===
#             history_file = os.path.join(work_dir, "test_history.json")
#             # 创建 TestHistoryManager 并传递 history_file
#             history_manager = TestHistoryManager(history_file=history_file)
#             self.diversity_injector = DiversityInjector(history_manager=history_manager)
#             logger.info(f"  Diversity injector initialized with history file: {history_file}")
            
#         except Exception as e:
#             logger.warning(f"Semantic analysis failed: {e}. Continuing without semantic guidance.")
#         # ================================

#         current_tb = self.TB_code
#         last_annotated_file = None 
        
#         # --- Baseline ---
#         logger.info(f"--- CGA Iter 0 (Baseline) ---")
#         iter0_dir = os.path.join(work_dir, "iter_0")
#         os.makedirs(iter0_dir, exist_ok=True)
        
#         self._prepare_dut(iter0_dir)
#         ls.save_code(current_tb, os.path.join(iter0_dir, "driver.v"))

#         success, score, annotated_path = verilator_run_coverage(iter0_dir, "DUT.v", "driver.v")
        
#         self.best_score = score
#         self.best_tb = current_tb
#         last_annotated_file = annotated_path
        
#         logger.info(f"Baseline Coverage: {score:.2f}%")

#         if score >= self.target_coverage:
#             logger.success(f"Target reached at baseline!")
#             # [修改] 返回元组 (代码, 分数)
#             return self.best_tb, self.best_score

#         # --- Loop ---
#         for i in range(1, self.max_iter + 1):
#             logger.info(f"--- CGA Iter {i} / {self.max_iter} ---")
            
#             # === [新增] 能量检查：是否还有活跃目标 ===
#             if self.energy_allocator:
#                 current_target = self.energy_allocator.select_next_target()
#                 if not current_target:
#                     logger.info("No more active targets with remaining energy. Stopping.")
#                     break
#                 logger.info(f"Target: {current_target}")
#             # =========================================
            
#             if not last_annotated_file: break

#             # [修改] 传递语义分析结果、能量分配器、多样性注入器给 CoverageParser
#             parser = CoverageParser(
#                 last_annotated_file, 
#                 tb_code=self.best_tb, 
#                 semantic_result=self.semantic_result,
#                 energy_allocator=self.energy_allocator,
#                 diversity_injector=self.diversity_injector  # [新增]
#             )
#             prompt = parser.generate_prompt(self.best_score)
            
#             if not prompt:
#                 logger.info("No reachable missing blocks found. Stopping.")
#                 break

#             logger.info(f"Asking LLM to fix missing logic (Current: {self.best_score:.2f}%)...")
#             messages = [{"role": "user", "content": prompt}]
            
#             try:
#                 response, _ = llm.llm_call(messages, self.model)
#                 codes = llm.extract_code(response, "verilog")
#                 new_task_code = codes[0] if codes else ""
#                 if not new_task_code:
#                     # [新增] 记录失败
#                     if self.energy_allocator:
#                         self.energy_allocator.record_generation(
#                             success=False,
#                             coverage_delta=0.0,
#                             energy_cost=1.0
#                         )
#                     continue
#             except Exception as e:
#                 logger.error(f"LLM Call failed: {e}")
#                 # [新增] 记录失败
#                 if self.energy_allocator:
#                     self.energy_allocator.record_generation(
#                         success=False,
#                         coverage_delta=0.0,
#                         energy_cost=1.0
#                     )
#                 break

#             injector = TBInjector(self.best_tb)
#             enhanced_tb = injector.inject(new_task_code, iter_idx=i)
            
#             iter_dir = os.path.join(work_dir, f"iter_{i}")
#             os.makedirs(iter_dir, exist_ok=True)
            
#             self._prepare_dut(iter_dir)
#             ls.save_code(enhanced_tb, os.path.join(iter_dir, "driver.v"))
            
#             success, new_score, new_annotated_path = verilator_run_coverage(iter_dir, "DUT.v", "driver.v")
            
#             # === [新增] 记录生成结果到能量分配器 ===
#             coverage_delta = new_score - self.best_score if success else 0.0
#             generation_success = success and new_score > self.best_score
            
#             if self.energy_allocator:
#                 self.energy_allocator.record_generation(
#                     success=generation_success,
#                     coverage_delta=coverage_delta,
#                     energy_cost=1.0
#                 )
#             # =========================================
            
#             # === [新增] 记录测试用例到多样性历史 ===
#             if self.diversity_injector:
#                 # 提取已知信号
#                 known_signals = []
#                 if self.semantic_result:
#                     known_signals = [p.get('name', '') for p in self.semantic_result.get('ports', [])]
                
#                 self.diversity_injector.record_test(
#                     code=new_task_code,
#                     target_function=self.energy_allocator.current_target.function_point if self.energy_allocator and self.energy_allocator.current_target else "",
#                     coverage_score=new_score,
#                     success=generation_success,
#                     iteration=i,
#                     known_signals=known_signals
#                 )
#             # =======================================
            
#             if success and new_score > self.best_score:
#                 improvement = new_score - self.best_score
#                 logger.success(f"Coverage Improved! +{improvement:.2f}% ({self.best_score:.2f}% -> {new_score:.2f}%)")
#                 self.best_score = new_score
#                 self.best_tb = enhanced_tb
#                 last_annotated_file = new_annotated_path
#             elif success and new_score == self.best_score:
#                 logger.info(f"Coverage unchanged. Keeping previous.")
#             else:
#                 logger.warning(f"Regression or Failure. Discarding changes.")

#             if self.best_score >= self.target_coverage:
#                 logger.success("Target coverage reached!")
#                 break

#         logger.info(f"CGA Finished. Final Coverage: {self.best_score:.2f}%")
        
#         # === [新增] 生成能量分配报告 ===
#         if self.energy_allocator:
#             energy_report = self.energy_allocator.generate_report()
#             ls.save_code(energy_report, os.path.join(work_dir, "energy_report.txt"))
#             logger.info(f"Energy report saved to {work_dir}/energy_report.txt")
#         # =================================
        
#         # === [新增] 生成多样性报告并保存历史 ===
#         if self.diversity_injector:
#             diversity_report = self.diversity_injector.generate_diversity_report()
#             ls.save_code(diversity_report, os.path.join(work_dir, "diversity_report.txt"))
#             logger.info(f"Diversity report saved to {work_dir}/diversity_report.txt")
            
#             # 保存测试历史
#             self.diversity_injector.history.save()
#         # ======================================
        
#         # [修改] 返回元组 (代码, 分数)
#         return self.best_tb, self.best_score

#终版
"""
Description :   Coverage-Guided Agent (CGA) Main Controller
                - Integrated with Layer 0: Semantic Analysis
                - Integrated with Layer 1: Diversity Constraint Injection
                - Integrated with Layer 3: Quality Evaluation
                - Integrated with Layer 4: Energy Allocation
Author      :   CorrectBench Integration
"""
import os
import sys
import shutil

import LLM_call as llm
import loader_saver as ls
from loader_saver import autologger as logger
from utils.verilator_call import verilator_run_coverage
from autoline.cga_utils import CoverageParser, TBInjector
# [新增] 导入语义分析层
from autoline.semantic_analyzer import SemanticAnalyzer, FunctionPointType
# [新增] 导入能量分配层
from autoline.energy_allocator import EnergyAllocator, EnergyState
# [新增] 导入多样性约束注入器
from autoline.diversity_injector import DiversityInjector
# [新增] 导入测试历史管理器
from autoline.test_history import TestHistoryManager
# [新增] 导入质量评估层
from autoline.quality_evaluator import QualityEvaluator, DiversityScore, SemanticCoverageResult

class TaskTBCGA:
    def __init__(self, task_dir, task_id, header, DUT_code, TB_code, config):
        self.task_dir = task_dir
        self.task_id = task_id
        self.header = header
        self.DUT_code = DUT_code
        self.TB_code = TB_code
        self.config = config
        
        self.max_iter = 5  
        self.target_coverage = 95.0
        self.model = config.gpt.model  
        
        self.best_tb = TB_code
        self.best_score = 0.0
        
        # [新增] 能量分配器
        self.energy_allocator: EnergyAllocator = None
        # [新增] 多样性约束注入器
        self.diversity_injector: DiversityInjector = None
        # [新增] 质量评估器
        self.quality_evaluator: QualityEvaluator = None

    # [新增辅助函数] 从父目录拷贝 DUT
    def _prepare_dut(self, target_dir):
        source_dut = os.path.join(self.task_dir, "DUT.v")
        target_dut = os.path.join(target_dir, "DUT.v")
        
        # 优先拷贝现有的文件
        if os.path.exists(source_dut):
            shutil.copy(source_dut, target_dut)
        else:
            # 只有当文件由于某种原因被删除了，才降级使用内存中的 code
            ls.save_code(self.DUT_code, target_dut)

    def _generate_exploration_prompt(self, iteration: int) -> str:
        """
        生成探索性测试 Prompt

        当找不到明确的 missing blocks 但覆盖率仍未达标时，
        生成一个探索性 Prompt 来尝试发现新的测试路径。

        Args:
            iteration: 当前迭代次数

        Returns:
            探索性测试 Prompt，如果无法生成则返回 None
        """
        # 从语义分析结果获取 FSM 和功能点信息
        fsm_info = ""
        if self.semantic_result:
            fsm_data = self.semantic_result.get('fsm', {})
            if fsm_data:
                states = fsm_data.get('states', [])
                state_var = fsm_data.get('state_variable', 'state')
                fsm_info = f"""
[FSM INFORMATION]
- State variable: {state_var}
- Known states: {', '.join(states) if states else 'unknown'}

The DUT appears to be a Finite State Machine. To improve coverage:
1. Try to visit each state by driving inputs that trigger state transitions
2. For each state, try different input combinations
3. Consider edge cases: reset transitions, timeout conditions, error states
"""

        # 从能量分配器获取目标功能点
        target_info = ""
        if self.energy_allocator and self.energy_allocator.current_target:
            target = self.energy_allocator.current_target
            target_info = f"""
[CURRENT TARGET]
Focus on: {target.function_point}
Remaining energy: {target.remaining}
"""

        # 从多样性注入器获取已尝试的测试
        diversity_hints = ""
        if self.diversity_injector:
            history = self.diversity_injector.history
            # if history and len(history.history) > 0:
            #     recent_tests = history.history[-5:] if len(history.history) > 5 else history.history
            if history and hasattr(history, 'records') and len(history.records) > 0:
                recent_tests = history.records[-5:] if len(history.records) > 5 else history.records
                diversity_hints = f"""
[RECENTLY TRIED APPROACHES - AVOID REPETITION]
Recent test patterns tried:
"""
                # for i, test in enumerate(recent_tests):
                #     diversity_hints += f"- Iter {test.get('iteration', i)}: target={test.get('target_function', 'unknown')}\n"
                for i, test in enumerate(recent_tests):
                # TestRecord 是 dataclass，使用属性访问
                    target = getattr(test, 'target_function', 'unknown') if hasattr(test, 'target_function') else 'unknown'
                    iteration = getattr(test, 'iteration', i) if hasattr(test, 'iteration') else i
                    diversity_hints += f"- Iter {iteration}: target={target}\n"

        prompt = f"""
[EXPLORATION MODE - ITERATION {iteration}]

Current coverage is {self.best_score:.2f}%, but no specific uncovered code blocks were identified.
This may happen when:
1. Coverage data is incomplete or filtered
2. Branch/condition coverage needs improvement (not just line coverage)
3. State transitions in FSM are not fully exercised

{fsm_info}
{target_info}
{diversity_hints}

[YOUR TASK]
Write an EXPLORATORY test scenario that:
1. Covers different input combinations than previous tests
2. Explores different FSM state transitions
3. Tests edge cases and boundary conditions
4. Varies timing and sequence of inputs

[OUTPUT FORMAT]
Return ONLY Verilog test scenario code (no task wrapper).
Use the signal names from the testbench.

```verilog
// Your exploratory test code here
```
"""
        return prompt




    def run(self):
        logger.info(f"[{self.task_id}] Starting Coverage-Guided Agent (CGA)...")
        
        # 1. 确保工作目录存在 (saves/任务名/5_CGA)
        work_dir = os.path.join(self.task_dir, "5_CGA")
        if os.path.exists(work_dir):
            shutil.rmtree(work_dir)
        os.makedirs(work_dir, exist_ok=True)

        # === [新增] Step 0: 语义分析 ===
        logger.info(f"[{self.task_id}] Running Semantic Analysis (Layer 0)...")
        self.semantic_result = None
        try:
            semantic_analyzer = SemanticAnalyzer(self.DUT_code)
            self.semantic_result = semantic_analyzer.analyze()
            
            # 记录分析结果摘要
            fp_count = len(self.semantic_result.get('function_points', []))
            fsm_info = semantic_analyzer.get_fsm_info()
            if fsm_info:
                logger.info(f"  FSM detected: {fsm_info.get('state_variable', 'unknown')} "
                           f"({len(fsm_info.get('states', []))} states)")
            logger.info(f"  Total function points identified: {fp_count}")
            
            # 保存语义分析报告
            semantic_report = semantic_analyzer.generate_prompt_context()
            ls.save_code(semantic_report, os.path.join(work_dir, "semantic_analysis.txt"))
            
            # === [新增] Step 0.1: 初始化能量分配器 ===
            if self.semantic_result.get('function_points'):
                self.energy_allocator = EnergyAllocator(max_iterations=self.max_iter)
                energy_init_result = self.energy_allocator.initialize(
                    self.semantic_result['function_points']
                )
                logger.info(f"  Energy allocator initialized: {energy_init_result['targets']} targets")
            
            # === [新增] Step 0.2: 初始化多样性约束注入器 ===
            history_file = os.path.join(work_dir, "test_history.json")
            # 创建 TestHistoryManager 并传递 history_file
            history_manager = TestHistoryManager(history_file=history_file)
            self.diversity_injector = DiversityInjector(history_manager=history_manager)
            logger.info(f"  Diversity injector initialized with history file: {history_file}")
            
            # === [新增] Step 0.3: 初始化质量评估器 ===
            if self.semantic_result.get('function_points'):
                self.quality_evaluator = QualityEvaluator(
                    function_points=self.semantic_result['function_points']
                )
                logger.info(f"  Quality evaluator initialized")
            
        except Exception as e:
            logger.warning(f"Semantic analysis failed: {e}. Continuing without semantic guidance.")
        # ================================

        current_tb = self.TB_code
        last_annotated_file = None 
        
        # --- Baseline ---
        logger.info(f"--- CGA Iter 0 (Baseline) ---")
        iter0_dir = os.path.join(work_dir, "iter_0")
        os.makedirs(iter0_dir, exist_ok=True)
        
        self._prepare_dut(iter0_dir)
        ls.save_code(current_tb, os.path.join(iter0_dir, "driver.v"))

        success, score, annotated_path = verilator_run_coverage(iter0_dir, "DUT.v", "driver.v")
        
        self.best_score = score
        self.best_tb = current_tb
        last_annotated_file = annotated_path
        
        logger.info(f"Baseline Coverage: {score:.2f}%")

        if score >= self.target_coverage:
            logger.success(f"Target reached at baseline!")
            # [修改] 返回元组 (代码, 分数)
            return self.best_tb, self.best_score

        # --- Loop ---
        for i in range(1, self.max_iter + 1):
            logger.info(f"--- CGA Iter {i} / {self.max_iter} ---")
            
            # === [新增] 能量检查：是否还有活跃目标 ===
            if self.energy_allocator:
                current_target = self.energy_allocator.select_next_target()
                if not current_target:
                    logger.info("No more active targets with remaining energy. Stopping.")
                    break
                logger.info(f"Target: {current_target}")
            # =========================================
            
            if not last_annotated_file: break

            # [修改] 传递语义分析结果、能量分配器、多样性注入器给 CoverageParser
            parser = CoverageParser(
                last_annotated_file, 
                tb_code=self.best_tb, 
                semantic_result=self.semantic_result,
                energy_allocator=self.energy_allocator,
                diversity_injector=self.diversity_injector  # [新增]
            )
            prompt = parser.generate_prompt(self.best_score)
            
            # if not prompt:
            #     logger.info("No reachable missing blocks found. Stopping.")
            #     break
            if not prompt:
                if self.best_score >= self.target_coverage:
                 break  # 达标才停止
            else:
            # 未达标，尝试探索性测试
                prompt = self._generate_exploration_prompt(i)

            logger.info(f"Asking LLM to fix missing logic (Current: {self.best_score:.2f}%)...")
            messages = [{"role": "user", "content": prompt}]
            
            try:
                response, _ = llm.llm_call(messages, self.model)
                codes = llm.extract_code(response, "verilog")
                new_task_code = codes[0] if codes else ""
                if not new_task_code:
                    # [新增] 记录失败
                    if self.energy_allocator:
                        self.energy_allocator.record_generation(
                            success=False,
                            coverage_delta=0.0,
                            energy_cost=1.0
                        )
                    continue
            except Exception as e:
                logger.error(f"LLM Call failed: {e}")
                # [新增] 记录失败
                if self.energy_allocator:
                    self.energy_allocator.record_generation(
                        success=False,
                        coverage_delta=0.0,
                        energy_cost=1.0
                    )
                break

            injector = TBInjector(self.best_tb)
            enhanced_tb = injector.inject(new_task_code, iter_idx=i)
            
            iter_dir = os.path.join(work_dir, f"iter_{i}")
            os.makedirs(iter_dir, exist_ok=True)
            
            self._prepare_dut(iter_dir)
            ls.save_code(enhanced_tb, os.path.join(iter_dir, "driver.v"))
            
            success, new_score, new_annotated_path = verilator_run_coverage(iter_dir, "DUT.v", "driver.v")
            
            # === [新增] 记录生成结果到能量分配器 ===
            coverage_delta = new_score - self.best_score if success else 0.0
            generation_success = success and new_score > self.best_score
            
            if self.energy_allocator:
                self.energy_allocator.record_generation(
                    success=generation_success,
                    coverage_delta=coverage_delta,
                    energy_cost=1.0
                )
            # =========================================
            
            # === [新增] 记录测试用例到多样性历史 ===
            if self.diversity_injector:
                # 提取已知信号
                known_signals = []
                if self.semantic_result:
                    known_signals = [p.get('name', '') for p in self.semantic_result.get('ports', [])]
                
                self.diversity_injector.record_test(
                    code=new_task_code,
                    target_function=self.energy_allocator.current_target.function_point if self.energy_allocator and self.energy_allocator.current_target else "",
                    coverage_score=new_score,
                    success=generation_success,
                    iteration=i,
                    known_signals=known_signals
                )
            # =======================================
            
            # === [新增] Layer 3: 质量评估 ===
            if self.quality_evaluator:
                # 评估测试用例质量
                eval_result = self.quality_evaluator.evaluate_test_case(
                    code=new_task_code,
                    covered_lines=set(),  # 如果有具体覆盖行信息可传入
                    covered_functions=[],  # 如果有覆盖功能点信息可传入
                    test_id=f"iter_{i}",
                    iteration=i
                )
                
                # 记录多样性得分
                diversity_score = eval_result.get('diversity', {}).get('overall_score', 0)
                logger.info(f"  Quality Evaluation: diversity={diversity_score:.2f}")
                
                # 检查是否应该接受该测试用例
                should_accept, reason = self.quality_evaluator.should_accept(eval_result)
                if not should_accept:
                    logger.warning(f"  Quality check failed: {reason}")
            # =====================================
            
            if success and new_score > self.best_score:
                improvement = new_score - self.best_score
                logger.success(f"Coverage Improved! +{improvement:.2f}% ({self.best_score:.2f}% -> {new_score:.2f}%)")
                self.best_score = new_score
                self.best_tb = enhanced_tb
                last_annotated_file = new_annotated_path
            elif success and new_score == self.best_score:
                logger.info(f"Coverage unchanged. Keeping previous.")
            else:
                logger.warning(f"Regression or Failure. Discarding changes.")

            if self.best_score >= self.target_coverage:
                logger.success("Target coverage reached!")
                break

        logger.info(f"CGA Finished. Final Coverage: {self.best_score:.2f}%")
        
        # === [新增] 生成能量分配报告 ===
        if self.energy_allocator:
            energy_report = self.energy_allocator.generate_report()
            ls.save_code(energy_report, os.path.join(work_dir, "energy_report.txt"))
            logger.info(f"Energy report saved to {work_dir}/energy_report.txt")
        # =================================
        
        # === [新增] 生成多样性报告并保存历史 ===
        if self.diversity_injector:
            diversity_report = self.diversity_injector.generate_diversity_report()
            ls.save_code(diversity_report, os.path.join(work_dir, "diversity_report.txt"))
            logger.info(f"Diversity report saved to {work_dir}/diversity_report.txt")
            
            # 保存测试历史
            self.diversity_injector.history.save()
        # ======================================
        
        # === [新增] Layer 3: 生成质量评估报告 ===
        if self.quality_evaluator:
            quality_report = self.quality_evaluator.generate_report()
            ls.save_code(quality_report, os.path.join(work_dir, "quality_evaluation_report.txt"))
            logger.info(f"Quality evaluation report saved to {work_dir}/quality_evaluation_report.txt")
            
            # 输出语义覆盖率摘要
            coverage_result = self.quality_evaluator.semantic_coverage.calculate_coverage()
            logger.info(f"Semantic Coverage: {coverage_result.semantic_coverage:.2%}")
        # ===========================================
        
        # [修改] 返回元组 (代码, 分数)
        return self.best_tb, self.best_score