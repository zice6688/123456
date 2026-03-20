// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtestbench.h for the primary calling header

#include "Vtestbench__pch.h"

VlCoroutine Vtestbench___024root___eval_initial__TOP__Vtiming__0(Vtestbench___024root* vlSelf);
VlCoroutine Vtestbench___024root___eval_initial__TOP__Vtiming__1(Vtestbench___024root* vlSelf);

void Vtestbench___024root___eval_initial(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_initial\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.testbench__DOT__file = VL_FOPEN_NN("TBout.txt"s
                                                 , "w"s);
    ;
    ++(vlSymsp->__Vcoverage[12]);
    Vtestbench___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtestbench___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vtestbench___024root___eval_initial__TOP__Vtiming__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.testbench__DOT__clk = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(5ULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                             18);
        vlSelfRef.testbench__DOT__clk = (1U & (~ (IData)(vlSelfRef.testbench__DOT__clk)));
        ++(vlSymsp->__Vcoverage[10]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__clk)))) {
        ++(vlSymsp->__Vcoverage[8]);
    }
    if (vlSelfRef.testbench__DOT__clk) {
        ++(vlSymsp->__Vcoverage[9]);
    }
    ++(vlSymsp->__Vcoverage[11]);
    co_return;}

VlCoroutine Vtestbench___024root___eval_initial__TOP__Vtiming__1(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ testbench__DOT__scenario;
    testbench__DOT__scenario = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_1__DOT____Vrepeat0;
    testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_2__DOT____Vrepeat1;
    testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_3__DOT____Vrepeat2;
    testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_4__DOT____Vrepeat3;
    testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_5__DOT____Vrepeat4;
    testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0;
    // Body
    testbench__DOT__scenario = 1U;
    vlSelfRef.testbench__DOT__reset = 1U;
    vlSelfRef.testbench__DOT__in = 0U;
    testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                      32,testbench__DOT__scenario,1,
                      (IData)(vlSelfRef.testbench__DOT__clk),
                      1,vlSelfRef.testbench__DOT__in,
                      1,(IData)(vlSelfRef.testbench__DOT__reset),
                      1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
        co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                             31);
        testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[13]);
    }
    vlSelfRef.testbench__DOT__reset = 0U;
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         34);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         35);
    testbench__DOT__scenario = 2U;
    vlSelfRef.testbench__DOT__reset = 1U;
    vlSelfRef.testbench__DOT__in = 0U;
    testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                      32,testbench__DOT__scenario,1,
                      (IData)(vlSelfRef.testbench__DOT__clk),
                      1,vlSelfRef.testbench__DOT__in,
                      1,(IData)(vlSelfRef.testbench__DOT__reset),
                      1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
        co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                             41);
        testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[14]);
    }
    vlSelfRef.testbench__DOT__reset = 0U;
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         44);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         45);
    testbench__DOT__scenario = 3U;
    vlSelfRef.testbench__DOT__reset = 1U;
    vlSelfRef.testbench__DOT__in = 0U;
    testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                      32,testbench__DOT__scenario,1,
                      (IData)(vlSelfRef.testbench__DOT__clk),
                      1,vlSelfRef.testbench__DOT__in,
                      1,(IData)(vlSelfRef.testbench__DOT__reset),
                      1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
        co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                             51);
        testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[15]);
    }
    vlSelfRef.testbench__DOT__reset = 0U;
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         54);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         55);
    testbench__DOT__scenario = 4U;
    vlSelfRef.testbench__DOT__reset = 1U;
    vlSelfRef.testbench__DOT__in = 0U;
    testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_4__DOT____Vrepeat3)) {
        VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                      32,testbench__DOT__scenario,1,
                      (IData)(vlSelfRef.testbench__DOT__clk),
                      1,vlSelfRef.testbench__DOT__in,
                      1,(IData)(vlSelfRef.testbench__DOT__reset),
                      1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
        co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                             61);
        testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 
            = (testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[16]);
    }
    vlSelfRef.testbench__DOT__reset = 0U;
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         64);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         65);
    testbench__DOT__scenario = 5U;
    vlSelfRef.testbench__DOT__reset = 1U;
    vlSelfRef.testbench__DOT__in = 0U;
    testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_5__DOT____Vrepeat4)) {
        VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                      32,testbench__DOT__scenario,1,
                      (IData)(vlSelfRef.testbench__DOT__clk),
                      1,vlSelfRef.testbench__DOT__in,
                      1,(IData)(vlSelfRef.testbench__DOT__reset),
                      1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
        co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                             71);
        testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 
            = (testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[17]);
    }
    vlSelfRef.testbench__DOT__reset = 0U;
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    vlSelfRef.testbench__DOT__in = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 
                                         74);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %1#, reset = %1#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  1,(0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    VL_FCLOSE_I(vlSelfRef.testbench__DOT__file); VL_FINISH_MT("/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 78, "");
    ++(vlSymsp->__Vcoverage[18]);
    co_return;}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtestbench___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vtestbench___024root___eval_triggers__act(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_triggers__act\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.testbench__DOT__clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__testbench__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__testbench__DOT__clk__0 
        = vlSelfRef.testbench__DOT__clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtestbench___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vtestbench___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtestbench___024root___act_sequent__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___act_sequent__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.testbench__DOT__clk) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
        vlSelfRef.testbench__DOT____Vtogcov__clk = vlSelfRef.testbench__DOT__clk;
    }
    if (((IData)(vlSelfRef.testbench__DOT__in) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__in))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__in, vlSelfRef.testbench__DOT____Vtogcov__in);
        vlSelfRef.testbench__DOT____Vtogcov__in = vlSelfRef.testbench__DOT__in;
    }
    if (((IData)(vlSelfRef.testbench__DOT__reset) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__reset))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 4, vlSelfRef.testbench__DOT__reset, vlSelfRef.testbench__DOT____Vtogcov__reset);
        vlSelfRef.testbench__DOT____Vtogcov__reset 
            = vlSelfRef.testbench__DOT__reset;
    }
    if (((((((((8U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
               | (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
              | (1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
             | (2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
            | (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
           | (4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
          | (5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
         | (6U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
        if ((8U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            vlSelfRef.testbench__DOT__DUT__DOT__next 
                = (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                                   ? ([&]() {
                            ++(vlSymsp->__Vcoverage[37]);
                        }(), 8U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[38]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[39]);
        } else if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[40]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
        } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[41]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[42]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[43]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 4U;
        } else if ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[44]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 5U;
        } else if ((5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[45]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 6U;
        } else {
            ++(vlSymsp->__Vcoverage[46]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 7U;
        }
    } else if ((7U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[47]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 9U;
    } else if ((9U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                             ? ([&]() {
                        ++(vlSymsp->__Vcoverage[50]);
                    }(), 0x0000000aU) : ([&]() {
                        ++(vlSymsp->__Vcoverage[51]);
                    }(), 0x0000000bU)));
        ++(vlSymsp->__Vcoverage[52]);
    } else if ((0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                             ? ([&]() {
                        ++(vlSymsp->__Vcoverage[55]);
                    }(), 8U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[56]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[57]);
    } else if ((0x0bU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                             ? ([&]() {
                        ++(vlSymsp->__Vcoverage[60]);
                    }(), 8U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[61]);
                    }(), 0x0000000bU)));
        ++(vlSymsp->__Vcoverage[62]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[35]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[36]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[48]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[49]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[53]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[54]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[58]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[59]);
    }
    ++(vlSymsp->__Vcoverage[63]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(4, vlSymsp->__Vcoverage + 27, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
            = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
}

void Vtestbench___024root___eval_act(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_act\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtestbench___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtestbench___024root___nba_sequent__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_sequent__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.testbench__DOT__clk) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
        vlSelfRef.testbench__DOT____Vtogcov__clk = vlSelfRef.testbench__DOT__clk;
    }
    if (((IData)(vlSelfRef.testbench__DOT__in) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__in))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__in, vlSelfRef.testbench__DOT____Vtogcov__in);
        vlSelfRef.testbench__DOT____Vtogcov__in = vlSelfRef.testbench__DOT__in;
    }
    if (((IData)(vlSelfRef.testbench__DOT__reset) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__reset))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 4, vlSelfRef.testbench__DOT__reset, vlSelfRef.testbench__DOT____Vtogcov__reset);
        vlSelfRef.testbench__DOT____Vtogcov__reset 
            = vlSelfRef.testbench__DOT__reset;
    }
}

void Vtestbench___024root___nba_sequent__TOP__1(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_sequent__TOP__1\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.testbench__DOT__reset) {
        ++(vlSymsp->__Vcoverage[64]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = 8U;
    } else {
        ++(vlSymsp->__Vcoverage[65]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
    ++(vlSymsp->__Vcoverage[66]);
    if (((0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__done))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 6, 
                               (0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__done);
        vlSelfRef.testbench__DOT____Vtogcov__done = 
            (0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
    }
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(4, vlSymsp->__Vcoverage + 19, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
            = vlSelfRef.testbench__DOT__DUT__DOT__state;
    }
}

void Vtestbench___024root___nba_comb__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_comb__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((((((((8U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
               | (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
              | (1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
             | (2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
            | (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
           | (4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
          | (5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) 
         | (6U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
        if ((8U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            vlSelfRef.testbench__DOT__DUT__DOT__next 
                = (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                                   ? ([&]() {
                            ++(vlSymsp->__Vcoverage[37]);
                        }(), 8U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[38]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[39]);
        } else if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[40]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
        } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[41]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[42]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[43]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 4U;
        } else if ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[44]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 5U;
        } else if ((5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[45]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 6U;
        } else {
            ++(vlSymsp->__Vcoverage[46]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 7U;
        }
    } else if ((7U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[47]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 9U;
    } else if ((9U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                             ? ([&]() {
                        ++(vlSymsp->__Vcoverage[50]);
                    }(), 0x0000000aU) : ([&]() {
                        ++(vlSymsp->__Vcoverage[51]);
                    }(), 0x0000000bU)));
        ++(vlSymsp->__Vcoverage[52]);
    } else if ((0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                             ? ([&]() {
                        ++(vlSymsp->__Vcoverage[55]);
                    }(), 8U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[56]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[57]);
    } else if ((0x0bU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (0x0000000fU & ((IData)(vlSelfRef.testbench__DOT__in)
                             ? ([&]() {
                        ++(vlSymsp->__Vcoverage[60]);
                    }(), 8U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[61]);
                    }(), 0x0000000bU)));
        ++(vlSymsp->__Vcoverage[62]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[35]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[36]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[48]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[49]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[53]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[54]);
    }
    if (vlSelfRef.testbench__DOT__in) {
        ++(vlSymsp->__Vcoverage[58]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__in)))) {
        ++(vlSymsp->__Vcoverage[59]);
    }
    ++(vlSymsp->__Vcoverage[63]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(4, vlSymsp->__Vcoverage + 27, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
            = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
}

void Vtestbench___024root___eval_nba(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_nba\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (((IData)(vlSelfRef.testbench__DOT__clk) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
            vlSelfRef.testbench__DOT____Vtogcov__clk 
                = vlSelfRef.testbench__DOT__clk;
        }
        if (((IData)(vlSelfRef.testbench__DOT__in) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__in))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__in, vlSelfRef.testbench__DOT____Vtogcov__in);
            vlSelfRef.testbench__DOT____Vtogcov__in 
                = vlSelfRef.testbench__DOT__in;
        }
        if (((IData)(vlSelfRef.testbench__DOT__reset) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__reset))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 4, vlSelfRef.testbench__DOT__reset, vlSelfRef.testbench__DOT____Vtogcov__reset);
            vlSelfRef.testbench__DOT____Vtogcov__reset 
                = vlSelfRef.testbench__DOT__reset;
        }
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (vlSelfRef.testbench__DOT__reset) {
            ++(vlSymsp->__Vcoverage[64]);
            vlSelfRef.testbench__DOT__DUT__DOT__state = 8U;
        } else {
            ++(vlSymsp->__Vcoverage[65]);
            vlSelfRef.testbench__DOT__DUT__DOT__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__next;
        }
        ++(vlSymsp->__Vcoverage[66]);
        if (((0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__done))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 6, 
                                   (0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__done);
            vlSelfRef.testbench__DOT____Vtogcov__done 
                = (0x0aU == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
        }
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
            VL_COV_TOGGLE_CHG_ST_I(4, vlSymsp->__Vcoverage + 19, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__state;
        }
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtestbench___024root___nba_comb__TOP__0(vlSelf);
    }
}

void Vtestbench___024root___timing_resume(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___timing_resume\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtestbench___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtestbench___024root___eval_phase__act(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_phase__act\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtestbench___024root___eval_triggers__act(vlSelf);
    Vtestbench___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtestbench___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        Vtestbench___024root___timing_resume(vlSelf);
        Vtestbench___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vtestbench___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtestbench___024root___eval_phase__nba(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_phase__nba\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtestbench___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtestbench___024root___eval_nba(vlSelf);
        Vtestbench___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtestbench___024root___eval(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtestbench___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 1, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtestbench___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/zhang/CorrectBench/saves/0309~0315/Main_Results/CorrectBench/NO_20260315_235638/fsm_serial/5_CGA/iter_0/driver.v", 1, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vtestbench___024root___eval_phase__act(vlSelf));
    } while (Vtestbench___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vtestbench___024root___eval_debug_assertions(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_debug_assertions\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
