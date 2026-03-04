"""
Description :   Coverage-Guided Agent (CGA) Main Controller
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



    def run(self):
        logger.info(f"[{self.task_id}] Starting Coverage-Guided Agent (CGA)...")
        
        # 1. 确保工作目录存在 (saves/任务名/5_CGA)
        work_dir = os.path.join(self.task_dir, "5_CGA")
        if os.path.exists(work_dir):
            shutil.rmtree(work_dir)
        os.makedirs(work_dir, exist_ok=True)

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
            
            if not last_annotated_file: break

            parser = CoverageParser(last_annotated_file)
            prompt = parser.generate_prompt(self.best_score)
            
            if not prompt:
                logger.info("No reachable missing blocks found. Stopping.")
                break

            logger.info(f"Asking LLM to fix missing logic (Current: {self.best_score:.2f}%)...")
            messages = [{"role": "user", "content": prompt}]
            
            try:
                response, _ = llm.llm_call(messages, self.model)
                codes = llm.extract_code(response, "verilog")
                new_task_code = codes[0] if codes else ""
                if not new_task_code: continue
            except Exception as e:
                logger.error(f"LLM Call failed: {e}")
                break

            injector = TBInjector(self.best_tb)
            enhanced_tb = injector.inject(new_task_code, iter_idx=i)
            
            iter_dir = os.path.join(work_dir, f"iter_{i}")
            os.makedirs(iter_dir, exist_ok=True)
            
            self._prepare_dut(iter_dir)
            ls.save_code(enhanced_tb, os.path.join(iter_dir, "driver.v"))
            
            success, new_score, new_annotated_path = verilator_run_coverage(iter_dir, "DUT.v", "driver.v")
            
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
        # [修改] 返回元组 (代码, 分数)
        return self.best_tb, self.best_score