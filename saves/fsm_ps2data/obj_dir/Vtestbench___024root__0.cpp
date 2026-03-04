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
    ++(vlSymsp->__Vcoverage[74]);
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
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                             21);
        vlSelfRef.testbench__DOT__clk = (1U & (~ (IData)(vlSelfRef.testbench__DOT__clk)));
        ++(vlSymsp->__Vcoverage[72]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__clk)))) {
        ++(vlSymsp->__Vcoverage[70]);
    }
    if (vlSelfRef.testbench__DOT__clk) {
        ++(vlSymsp->__Vcoverage[71]);
    }
    ++(vlSymsp->__Vcoverage[73]);
    co_return;}

VlCoroutine Vtestbench___024root___eval_initial__TOP__Vtiming__1(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ testbench__DOT__scenario;
    testbench__DOT__scenario = 0;
    // Body
    testbench__DOT__scenario = 1U;
    vlSelfRef.testbench__DOT__reset = 1U;
    vlSelfRef.testbench__DOT__in = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario:           1, clk = %1#, in =   0, reset = 1, out_bytes = %8#, done = %1#\n",0,
                  1,vlSelfRef.testbench__DOT__clk,24,
                  vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         32);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__reset = 0U;
    vlSelfRef.testbench__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         34);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x2cU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         36);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x81U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         38);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 9U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         40);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         41);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         42);
    testbench__DOT__scenario = 2U;
    vlSelfRef.testbench__DOT__in = 0x6bU;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         46);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x0dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         48);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x8dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         50);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         51);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         52);
    testbench__DOT__scenario = 3U;
    vlSelfRef.testbench__DOT__in = 0x6dU;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         56);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x12U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         58);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         60);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xedU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         62);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x76U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         64);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x3dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         66);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         67);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         68);
    testbench__DOT__scenario = 4U;
    vlSelfRef.testbench__DOT__in = 0xedU;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         72);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x8cU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         74);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xf9U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         76);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         78);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         80);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xceU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         82);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xc5U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         84);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xaaU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         86);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         87);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         88);
    testbench__DOT__scenario = 5U;
    vlSelfRef.testbench__DOT__in = 0x2cU;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         92);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x81U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         94);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 9U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         96);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__reset = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         98);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__reset = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         100);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x6bU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         102);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x0dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         104);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x8dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         106);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         107);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         108);
    testbench__DOT__scenario = 6U;
    vlSelfRef.testbench__DOT__in = 0x6bU;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         112);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x0dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         114);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x8dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         116);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         118);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         120);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xedU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         122);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x76U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         124);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x3dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         126);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         127);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         128);
    testbench__DOT__scenario = 7U;
    vlSelfRef.testbench__DOT__in = 0xedU;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         132);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x8cU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         134);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xf9U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         136);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         138);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         140);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xceU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         142);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xc5U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         144);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0xaaU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         146);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         147);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         148);
    testbench__DOT__scenario = 8U;
    vlSelfRef.testbench__DOT__in = 0x2cU;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         152);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x81U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         154);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 9U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         156);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__reset = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         158);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__reset = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         160);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x6bU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         162);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x0dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         164);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__in = 0x8dU;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         166);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 
                                         167);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, in = %3#, reset = %1#, out_bytes = %8#, done = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  8,vlSelfRef.testbench__DOT__in,1,
                  (IData)(vlSelfRef.testbench__DOT__reset),
                  24,vlSelfRef.testbench__DOT__out_bytes,
                  1,(3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    VL_FCLOSE_I(vlSelfRef.testbench__DOT__file); VL_FINISH_MT("/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 171, "");
    ++(vlSymsp->__Vcoverage[75]);
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
        VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__in, vlSelfRef.testbench__DOT____Vtogcov__in);
        vlSelfRef.testbench__DOT____Vtogcov__in = vlSelfRef.testbench__DOT__in;
    }
    if (((IData)(vlSelfRef.testbench__DOT__reset) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__reset))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 18, vlSelfRef.testbench__DOT__reset, vlSelfRef.testbench__DOT____Vtogcov__reset);
        vlSelfRef.testbench__DOT____Vtogcov__reset 
            = vlSelfRef.testbench__DOT__reset;
    }
    if ((1U & (((IData)(vlSelfRef.testbench__DOT__in) 
                >> 3U) ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3)))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 84, 
                               ((IData)(vlSelfRef.testbench__DOT__in) 
                                >> 3U), vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3 
            = (1U & ((IData)(vlSelfRef.testbench__DOT__in) 
                     >> 3U));
    }
    if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[88]);
                    }(), 1U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[89]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[90]);
    } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[91]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
    } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[92]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
    } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[95]);
                    }(), 1U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[96]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[97]);
    }
    if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
        ++(vlSymsp->__Vcoverage[86]);
    }
    if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                  >> 3U)))) {
        ++(vlSymsp->__Vcoverage[87]);
    }
    if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
        ++(vlSymsp->__Vcoverage[93]);
    }
    if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                  >> 3U)))) {
        ++(vlSymsp->__Vcoverage[94]);
    }
    ++(vlSymsp->__Vcoverage[98]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 80, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
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
        if (((IData)(vlSelfRef.testbench__DOT__clk) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
            vlSelfRef.testbench__DOT____Vtogcov__clk 
                = vlSelfRef.testbench__DOT__clk;
        }
        if (((IData)(vlSelfRef.testbench__DOT__in) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__in))) {
            VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__in, vlSelfRef.testbench__DOT____Vtogcov__in);
            vlSelfRef.testbench__DOT____Vtogcov__in 
                = vlSelfRef.testbench__DOT__in;
        }
        if (((IData)(vlSelfRef.testbench__DOT__reset) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__reset))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 18, vlSelfRef.testbench__DOT__reset, vlSelfRef.testbench__DOT____Vtogcov__reset);
            vlSelfRef.testbench__DOT____Vtogcov__reset 
                = vlSelfRef.testbench__DOT__reset;
        }
        if ((1U & (((IData)(vlSelfRef.testbench__DOT__in) 
                    >> 3U) ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3)))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 84, 
                                   ((IData)(vlSelfRef.testbench__DOT__in) 
                                    >> 3U), vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3 
                = (1U & ((IData)(vlSelfRef.testbench__DOT__in) 
                         >> 3U));
        }
        if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            vlSelfRef.testbench__DOT__DUT__DOT__next 
                = (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                          ? ([&]() {
                            ++(vlSymsp->__Vcoverage[88]);
                        }(), 1U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[89]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[90]);
        } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[91]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[92]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            vlSelfRef.testbench__DOT__DUT__DOT__next 
                = (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                          ? ([&]() {
                            ++(vlSymsp->__Vcoverage[95]);
                        }(), 1U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[96]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[97]);
        }
        if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
            ++(vlSymsp->__Vcoverage[86]);
        }
        if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                      >> 3U)))) {
            ++(vlSymsp->__Vcoverage[87]);
        }
        if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
            ++(vlSymsp->__Vcoverage[93]);
        }
        if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                      >> 3U)))) {
            ++(vlSymsp->__Vcoverage[94]);
        }
        ++(vlSymsp->__Vcoverage[98]);
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
            VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 80, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
                = vlSelfRef.testbench__DOT__DUT__DOT__next;
        }
    }
}

void Vtestbench___024root___nba_sequent__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_sequent__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    ++(vlSymsp->__Vcoverage[150]);
    vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r 
        = ((0x00ffff00U & (vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r 
                           << 8U)) | (IData)(vlSelfRef.testbench__DOT__in));
    if (vlSelfRef.testbench__DOT__reset) {
        ++(vlSymsp->__Vcoverage[99]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = 0U;
    } else {
        ++(vlSymsp->__Vcoverage[100]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
    ++(vlSymsp->__Vcoverage[101]);
    if ((vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r 
         ^ vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__out_bytes_r)) {
        VL_COV_TOGGLE_CHG_ST_I(24, vlSymsp->__Vcoverage + 102, vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__out_bytes_r);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__out_bytes_r 
            = vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r;
    }
    if (((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__done))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 68, 
                               (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__done);
        vlSelfRef.testbench__DOT____Vtogcov__done = 
            (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
    }
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 76, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
            = vlSelfRef.testbench__DOT__DUT__DOT__state;
    }
    vlSelfRef.testbench__DOT__out_bytes = ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))
                                            ? ([&]() {
                ++(vlSymsp->__Vcoverage[151]);
            }(), vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r)
                                            : ([&]() {
                ++(vlSymsp->__Vcoverage[152]);
            }(), 0U));
    if ((vlSelfRef.testbench__DOT__out_bytes ^ vlSelfRef.testbench__DOT____Vtogcov__out_bytes)) {
        VL_COV_TOGGLE_CHG_ST_I(24, vlSymsp->__Vcoverage + 20, vlSelfRef.testbench__DOT__out_bytes, vlSelfRef.testbench__DOT____Vtogcov__out_bytes);
        vlSelfRef.testbench__DOT____Vtogcov__out_bytes 
            = vlSelfRef.testbench__DOT__out_bytes;
    }
}

void Vtestbench___024root___nba_sequent__TOP__1(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_sequent__TOP__1\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.testbench__DOT__clk) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
        vlSelfRef.testbench__DOT____Vtogcov__clk = vlSelfRef.testbench__DOT__clk;
    }
    if (((IData)(vlSelfRef.testbench__DOT__in) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__in))) {
        VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__in, vlSelfRef.testbench__DOT____Vtogcov__in);
        vlSelfRef.testbench__DOT____Vtogcov__in = vlSelfRef.testbench__DOT__in;
    }
    if (((IData)(vlSelfRef.testbench__DOT__reset) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__reset))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 18, vlSelfRef.testbench__DOT__reset, vlSelfRef.testbench__DOT____Vtogcov__reset);
        vlSelfRef.testbench__DOT____Vtogcov__reset 
            = vlSelfRef.testbench__DOT__reset;
    }
    if ((1U & (((IData)(vlSelfRef.testbench__DOT__in) 
                >> 3U) ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3)))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 84, 
                               ((IData)(vlSelfRef.testbench__DOT__in) 
                                >> 3U), vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3 
            = (1U & ((IData)(vlSelfRef.testbench__DOT__in) 
                     >> 3U));
    }
}

void Vtestbench___024root___nba_comb__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_comb__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[88]);
                    }(), 1U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[89]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[90]);
    } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[91]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
    } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[92]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
    } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[95]);
                    }(), 1U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[96]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[97]);
    }
    if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
        ++(vlSymsp->__Vcoverage[86]);
    }
    if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                  >> 3U)))) {
        ++(vlSymsp->__Vcoverage[87]);
    }
    if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
        ++(vlSymsp->__Vcoverage[93]);
    }
    if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                  >> 3U)))) {
        ++(vlSymsp->__Vcoverage[94]);
    }
    ++(vlSymsp->__Vcoverage[98]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 80, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
            = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
}

void Vtestbench___024root___eval_nba(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_nba\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        ++(vlSymsp->__Vcoverage[150]);
        vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r 
            = ((0x00ffff00U & (vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r 
                               << 8U)) | (IData)(vlSelfRef.testbench__DOT__in));
        if (vlSelfRef.testbench__DOT__reset) {
            ++(vlSymsp->__Vcoverage[99]);
            vlSelfRef.testbench__DOT__DUT__DOT__state = 0U;
        } else {
            ++(vlSymsp->__Vcoverage[100]);
            vlSelfRef.testbench__DOT__DUT__DOT__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__next;
        }
        ++(vlSymsp->__Vcoverage[101]);
        if ((vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r 
             ^ vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__out_bytes_r)) {
            VL_COV_TOGGLE_CHG_ST_I(24, vlSymsp->__Vcoverage + 102, vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__out_bytes_r);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__out_bytes_r 
                = vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r;
        }
        if (((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__done))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 68, 
                                   (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__done);
            vlSelfRef.testbench__DOT____Vtogcov__done 
                = (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
        }
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
            VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 76, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__state;
        }
        vlSelfRef.testbench__DOT__out_bytes = ((3U 
                                                == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))
                                                ? ([&]() {
                    ++(vlSymsp->__Vcoverage[151]);
                }(), vlSelfRef.testbench__DOT__DUT__DOT__out_bytes_r)
                                                : ([&]() {
                    ++(vlSymsp->__Vcoverage[152]);
                }(), 0U));
        if ((vlSelfRef.testbench__DOT__out_bytes ^ vlSelfRef.testbench__DOT____Vtogcov__out_bytes)) {
            VL_COV_TOGGLE_CHG_ST_I(24, vlSymsp->__Vcoverage + 20, vlSelfRef.testbench__DOT__out_bytes, vlSelfRef.testbench__DOT____Vtogcov__out_bytes);
            vlSelfRef.testbench__DOT____Vtogcov__out_bytes 
                = vlSelfRef.testbench__DOT__out_bytes;
        }
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (((IData)(vlSelfRef.testbench__DOT__clk) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
            vlSelfRef.testbench__DOT____Vtogcov__clk 
                = vlSelfRef.testbench__DOT__clk;
        }
        if (((IData)(vlSelfRef.testbench__DOT__in) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__in))) {
            VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__in, vlSelfRef.testbench__DOT____Vtogcov__in);
            vlSelfRef.testbench__DOT____Vtogcov__in 
                = vlSelfRef.testbench__DOT__in;
        }
        if (((IData)(vlSelfRef.testbench__DOT__reset) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__reset))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 18, vlSelfRef.testbench__DOT__reset, vlSelfRef.testbench__DOT____Vtogcov__reset);
            vlSelfRef.testbench__DOT____Vtogcov__reset 
                = vlSelfRef.testbench__DOT__reset;
        }
        if ((1U & (((IData)(vlSelfRef.testbench__DOT__in) 
                    >> 3U) ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3)))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 84, 
                                   ((IData)(vlSelfRef.testbench__DOT__in) 
                                    >> 3U), vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3 
                = (1U & ((IData)(vlSelfRef.testbench__DOT__in) 
                         >> 3U));
        }
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            vlSelfRef.testbench__DOT__DUT__DOT__next 
                = (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                          ? ([&]() {
                            ++(vlSymsp->__Vcoverage[88]);
                        }(), 1U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[89]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[90]);
        } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[91]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[92]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            vlSelfRef.testbench__DOT__DUT__DOT__next 
                = (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                          ? ([&]() {
                            ++(vlSymsp->__Vcoverage[95]);
                        }(), 1U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[96]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[97]);
        }
        if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
            ++(vlSymsp->__Vcoverage[86]);
        }
        if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                      >> 3U)))) {
            ++(vlSymsp->__Vcoverage[87]);
        }
        if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
            ++(vlSymsp->__Vcoverage[93]);
        }
        if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                      >> 3U)))) {
            ++(vlSymsp->__Vcoverage[94]);
        }
        ++(vlSymsp->__Vcoverage[98]);
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
            VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 80, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
                = vlSelfRef.testbench__DOT__DUT__DOT__next;
        }
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
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 2, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtestbench___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/zhang/CorrectBench/saves/fsm_ps2data/final_TB.v", 2, "", "Active region did not converge after 100 tries");
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
