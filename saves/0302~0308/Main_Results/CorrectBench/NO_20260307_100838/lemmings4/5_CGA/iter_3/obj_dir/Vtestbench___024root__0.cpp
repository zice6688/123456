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
    ++(vlSymsp->__Vcoverage[24]);
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                             31);
        vlSelfRef.testbench__DOT__clk = (1U & (~ (IData)(vlSelfRef.testbench__DOT__clk)));
        ++(vlSymsp->__Vcoverage[22]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__clk)))) {
        ++(vlSymsp->__Vcoverage[20]);
    }
    if (vlSelfRef.testbench__DOT__clk) {
        ++(vlSymsp->__Vcoverage[21]);
    }
    ++(vlSymsp->__Vcoverage[23]);
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
    IData/*31:0*/ testbench__DOT__unnamedblk1_6__DOT____Vrepeat5;
    testbench__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_7__DOT____Vrepeat6;
    testbench__DOT__unnamedblk1_7__DOT____Vrepeat6 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_8__DOT____Vrepeat7;
    testbench__DOT__unnamedblk1_8__DOT____Vrepeat7 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_9__DOT____Vrepeat8;
    testbench__DOT__unnamedblk1_9__DOT____Vrepeat8 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_10__DOT____Vrepeat9;
    testbench__DOT__unnamedblk1_10__DOT____Vrepeat9 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_11__DOT____Vrepeat10;
    testbench__DOT__unnamedblk1_11__DOT____Vrepeat10 = 0;
    // Body
    testbench__DOT__scenario = 1U;
    vlSelfRef.testbench__DOT__areset = 1U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario:           1, clk = %1#, areset = 1, bump_left = 0, bump_right = 0, ground = 1, dig = 0, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  1,vlSelfRef.testbench__DOT__clk,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         43);
    vlSelfRef.testbench__DOT__areset = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         46);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         47);
    testbench__DOT__scenario = 2U;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         53);
    vlSelfRef.testbench__DOT__bump_left = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         56);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         57);
    testbench__DOT__scenario = 3U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         63);
    vlSelfRef.testbench__DOT__bump_right = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         66);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         67);
    testbench__DOT__scenario = 4U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         73);
    vlSelfRef.testbench__DOT__bump_right = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         76);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         77);
    testbench__DOT__scenario = 5U;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         83);
    vlSelfRef.testbench__DOT__bump_left = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         86);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         87);
    testbench__DOT__scenario = 6U;
    vlSelfRef.testbench__DOT__ground = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         93);
    vlSelfRef.testbench__DOT__ground = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         96);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         97);
    testbench__DOT__scenario = 7U;
    vlSelfRef.testbench__DOT__ground = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         103);
    vlSelfRef.testbench__DOT__ground = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         106);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         107);
    testbench__DOT__scenario = 8U;
    vlSelfRef.testbench__DOT__dig = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         113);
    vlSelfRef.testbench__DOT__dig = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         115);
    vlSelfRef.testbench__DOT__ground = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         118);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         119);
    testbench__DOT__scenario = 9U;
    vlSelfRef.testbench__DOT__ground = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         125);
    vlSelfRef.testbench__DOT__ground = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         128);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         129);
    testbench__DOT__scenario = 0x0000000aU;
    vlSelfRef.testbench__DOT__ground = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         134);
    testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x00000014U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                      32,testbench__DOT__scenario,1,
                      (IData)(vlSelfRef.testbench__DOT__clk),
                      1,vlSelfRef.testbench__DOT__areset,
                      1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                      1,vlSelfRef.testbench__DOT__bump_right,
                      1,(IData)(vlSelfRef.testbench__DOT__ground),
                      1,vlSelfRef.testbench__DOT__dig,
                      1,(0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                      1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                      1,(IData)(vlSelfRef.testbench__DOT__aaah),
                      1,vlSelfRef.testbench__DOT__digging);
        co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                             136);
        testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[25]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         140);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         141);
    testbench__DOT__scenario = 0x0000000bU;
    vlSelfRef.testbench__DOT__areset = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         147);
    vlSelfRef.testbench__DOT__areset = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         149);
    vlSelfRef.testbench__DOT__bump_left = 1U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 1U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         152);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[check]scenario: %11d, clk = %1#, areset = %1#, bump_left = %1#, bump_right = %1#, ground = %1#, dig = %1#, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  32,testbench__DOT__scenario,1,(IData)(vlSelfRef.testbench__DOT__clk),
                  1,vlSelfRef.testbench__DOT__areset,
                  1,(IData)(vlSelfRef.testbench__DOT__bump_left),
                  1,vlSelfRef.testbench__DOT__bump_right,
                  1,(IData)(vlSelfRef.testbench__DOT__ground),
                  1,vlSelfRef.testbench__DOT__dig,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    testbench__DOT__scenario = 0x00000067U;
    vlSelfRef.testbench__DOT__areset = 0U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                         158);
    vlSelfRef.testbench__DOT__areset = 1U;
    testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             162);
        testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[26]);
    }
    vlSelfRef.testbench__DOT__areset = 0U;
    testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             165);
        testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[27]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 1U;
    testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_4__DOT____Vrepeat3)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             170);
        testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 
            = (testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[28]);
    }
    vlSelfRef.testbench__DOT__bump_left = 0U;
    testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_5__DOT____Vrepeat4)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             173);
        testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 
            = (testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[29]);
    }
    testbench__DOT__unnamedblk1_6__DOT____Vrepeat5 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_6__DOT____Vrepeat5)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             175);
        testbench__DOT__unnamedblk1_6__DOT____Vrepeat5 
            = (testbench__DOT__unnamedblk1_6__DOT____Vrepeat5 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[30]);
    }
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    testbench__DOT__unnamedblk1_7__DOT____Vrepeat6 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_7__DOT____Vrepeat6)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             179);
        testbench__DOT__unnamedblk1_7__DOT____Vrepeat6 
            = (testbench__DOT__unnamedblk1_7__DOT____Vrepeat6 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[31]);
    }
    testbench__DOT__unnamedblk1_8__DOT____Vrepeat7 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_8__DOT____Vrepeat7)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             181);
        testbench__DOT__unnamedblk1_8__DOT____Vrepeat7 
            = (testbench__DOT__unnamedblk1_8__DOT____Vrepeat7 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[32]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    testbench__DOT__unnamedblk1_9__DOT____Vrepeat8 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_9__DOT____Vrepeat8)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             188);
        testbench__DOT__unnamedblk1_9__DOT____Vrepeat8 
            = (testbench__DOT__unnamedblk1_9__DOT____Vrepeat8 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[33]);
    }
    testbench__DOT__unnamedblk1_10__DOT____Vrepeat9 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_10__DOT____Vrepeat9)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             190);
        testbench__DOT__unnamedblk1_10__DOT____Vrepeat9 
            = (testbench__DOT__unnamedblk1_10__DOT____Vrepeat9 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[34]);
    }
    vlSelfRef.testbench__DOT__bump_left = 0U;
    testbench__DOT__unnamedblk1_11__DOT____Vrepeat10 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_11__DOT____Vrepeat10)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 
                                                             193);
        testbench__DOT__unnamedblk1_11__DOT____Vrepeat10 
            = (testbench__DOT__unnamedblk1_11__DOT____Vrepeat10 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[35]);
    }
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[CGA-3] walk_left, walk_right, aaah, digging = %b, %b, %b, %b\n",0,
                  1,(0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    VL_FCLOSE_I(vlSelfRef.testbench__DOT__file); VL_FINISH_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 200, "");
    ++(vlSymsp->__Vcoverage[36]);
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
                                                      << 2U) 
                                                     | ((((IData)(vlSelfRef.testbench__DOT__clk) 
                                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__testbench__DOT__clk__0))) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.testbench__DOT__areset) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__testbench__DOT__areset__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__testbench__DOT__areset__0 
        = vlSelfRef.testbench__DOT__areset;
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
}

void Vtestbench___024root___act_comb__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___act_comb__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.testbench__DOT__areset) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__areset))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__areset, vlSelfRef.testbench__DOT____Vtogcov__areset);
        vlSelfRef.testbench__DOT____Vtogcov__areset 
            = vlSelfRef.testbench__DOT__areset;
    }
    if (((IData)(vlSelfRef.testbench__DOT__bump_left) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__bump_left))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 4, vlSelfRef.testbench__DOT__bump_left, vlSelfRef.testbench__DOT____Vtogcov__bump_left);
        vlSelfRef.testbench__DOT____Vtogcov__bump_left 
            = vlSelfRef.testbench__DOT__bump_left;
    }
    if (((IData)(vlSelfRef.testbench__DOT__bump_right) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__bump_right))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 6, vlSelfRef.testbench__DOT__bump_right, vlSelfRef.testbench__DOT____Vtogcov__bump_right);
        vlSelfRef.testbench__DOT____Vtogcov__bump_right 
            = vlSelfRef.testbench__DOT__bump_right;
    }
    if (((IData)(vlSelfRef.testbench__DOT__ground) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__ground))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 8, vlSelfRef.testbench__DOT__ground, vlSelfRef.testbench__DOT____Vtogcov__ground);
        vlSelfRef.testbench__DOT____Vtogcov__ground 
            = vlSelfRef.testbench__DOT__ground;
    }
    if (((IData)(vlSelfRef.testbench__DOT__dig) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__dig))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 10, vlSelfRef.testbench__DOT__dig, vlSelfRef.testbench__DOT____Vtogcov__dig);
        vlSelfRef.testbench__DOT____Vtogcov__dig = vlSelfRef.testbench__DOT__dig;
    }
    if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        if (vlSelfRef.testbench__DOT__ground) {
            if (vlSelfRef.testbench__DOT__dig) {
                vlSelfRef.testbench__DOT__DUT__DOT__next = 4U;
                ++(vlSymsp->__Vcoverage[61]);
            } else if (vlSelfRef.testbench__DOT__bump_left) {
                ++(vlSymsp->__Vcoverage[59]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            } else {
                ++(vlSymsp->__Vcoverage[60]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[62]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        }
        ++(vlSymsp->__Vcoverage[65]);
    } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        if (vlSelfRef.testbench__DOT__ground) {
            if (vlSelfRef.testbench__DOT__dig) {
                ++(vlSymsp->__Vcoverage[68]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 5U;
            } else if (vlSelfRef.testbench__DOT__bump_right) {
                ++(vlSymsp->__Vcoverage[66]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            } else {
                ++(vlSymsp->__Vcoverage[67]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[69]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        }
        ++(vlSymsp->__Vcoverage[72]);
    } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[77]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[75]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[76]);
                            }(), 0U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[78]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[79]);
    } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[84]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[82]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[83]);
                            }(), 1U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[85]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[86]);
    } else if ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[89]);
                    }(), 4U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[90]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[91]);
    } else if ((5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[94]);
                    }(), 5U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[95]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[96]);
    } else if ((6U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[97]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 6U;
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[63]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[64]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[70]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[71]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[73]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[74]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[80]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[81]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[87]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[88]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[92]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[93]);
    }
    ++(vlSymsp->__Vcoverage[98]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 43, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
            = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
}

void Vtestbench___024root___eval_act(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_act\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        if (((IData)(vlSelfRef.testbench__DOT__clk) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
            vlSelfRef.testbench__DOT____Vtogcov__clk 
                = vlSelfRef.testbench__DOT__clk;
        }
    }
    if ((6ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtestbench___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtestbench___024root___nba_sequent__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_sequent__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         | (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
        if ((0x14U > (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))) {
            vlSelfRef.testbench__DOT__DUT__DOT__fall_counter 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter)));
            ++(vlSymsp->__Vcoverage[102]);
        } else {
            ++(vlSymsp->__Vcoverage[103]);
        }
        ++(vlSymsp->__Vcoverage[104]);
    } else {
        ++(vlSymsp->__Vcoverage[105]);
        vlSelfRef.testbench__DOT__DUT__DOT__fall_counter = 0U;
    }
    if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[106]);
    }
    if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[107]);
    }
    if (((2U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         & (3U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
        ++(vlSymsp->__Vcoverage[108]);
    }
    ++(vlSymsp->__Vcoverage[109]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter))) {
        VL_COV_TOGGLE_CHG_ST_I(5, vlSymsp->__Vcoverage + 49, vlSelfRef.testbench__DOT__DUT__DOT__fall_counter, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter 
            = vlSelfRef.testbench__DOT__DUT__DOT__fall_counter;
    }
}

void Vtestbench___024root___nba_comb__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_comb__TOP__0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.testbench__DOT__areset) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__areset))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__areset, vlSelfRef.testbench__DOT____Vtogcov__areset);
        vlSelfRef.testbench__DOT____Vtogcov__areset 
            = vlSelfRef.testbench__DOT__areset;
    }
    if (((IData)(vlSelfRef.testbench__DOT__bump_left) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__bump_left))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 4, vlSelfRef.testbench__DOT__bump_left, vlSelfRef.testbench__DOT____Vtogcov__bump_left);
        vlSelfRef.testbench__DOT____Vtogcov__bump_left 
            = vlSelfRef.testbench__DOT__bump_left;
    }
    if (((IData)(vlSelfRef.testbench__DOT__bump_right) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__bump_right))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 6, vlSelfRef.testbench__DOT__bump_right, vlSelfRef.testbench__DOT____Vtogcov__bump_right);
        vlSelfRef.testbench__DOT____Vtogcov__bump_right 
            = vlSelfRef.testbench__DOT__bump_right;
    }
    if (((IData)(vlSelfRef.testbench__DOT__ground) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__ground))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 8, vlSelfRef.testbench__DOT__ground, vlSelfRef.testbench__DOT____Vtogcov__ground);
        vlSelfRef.testbench__DOT____Vtogcov__ground 
            = vlSelfRef.testbench__DOT__ground;
    }
    if (((IData)(vlSelfRef.testbench__DOT__dig) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__dig))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 10, vlSelfRef.testbench__DOT__dig, vlSelfRef.testbench__DOT____Vtogcov__dig);
        vlSelfRef.testbench__DOT____Vtogcov__dig = vlSelfRef.testbench__DOT__dig;
    }
}

void Vtestbench___024root___nba_sequent__TOP__2(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_sequent__TOP__2\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.testbench__DOT__areset) {
        ++(vlSymsp->__Vcoverage[99]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = 0U;
    } else {
        ++(vlSymsp->__Vcoverage[100]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
    ++(vlSymsp->__Vcoverage[101]);
    if (((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__walk_left))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 12, 
                               (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__walk_left);
        vlSelfRef.testbench__DOT____Vtogcov__walk_left 
            = (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
    }
    if (((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__walk_right))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 14, 
                               (1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__walk_right);
        vlSelfRef.testbench__DOT____Vtogcov__walk_right 
            = (1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
    }
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 37, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
            = vlSelfRef.testbench__DOT__DUT__DOT__state;
    }
    vlSelfRef.testbench__DOT__aaah = ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
                                      | (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__digging = ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
                                         | (5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    if (((IData)(vlSelfRef.testbench__DOT__aaah) ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__aaah))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 16, vlSelfRef.testbench__DOT__aaah, vlSelfRef.testbench__DOT____Vtogcov__aaah);
        vlSelfRef.testbench__DOT____Vtogcov__aaah = vlSelfRef.testbench__DOT__aaah;
    }
    if (((IData)(vlSelfRef.testbench__DOT__digging) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__digging))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 18, vlSelfRef.testbench__DOT__digging, vlSelfRef.testbench__DOT____Vtogcov__digging);
        vlSelfRef.testbench__DOT____Vtogcov__digging 
            = vlSelfRef.testbench__DOT__digging;
    }
}

void Vtestbench___024root___nba_comb__TOP__1(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___nba_comb__TOP__1\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        if (vlSelfRef.testbench__DOT__ground) {
            if (vlSelfRef.testbench__DOT__dig) {
                vlSelfRef.testbench__DOT__DUT__DOT__next = 4U;
                ++(vlSymsp->__Vcoverage[61]);
            } else if (vlSelfRef.testbench__DOT__bump_left) {
                ++(vlSymsp->__Vcoverage[59]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            } else {
                ++(vlSymsp->__Vcoverage[60]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[62]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        }
        ++(vlSymsp->__Vcoverage[65]);
    } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        if (vlSelfRef.testbench__DOT__ground) {
            if (vlSelfRef.testbench__DOT__dig) {
                ++(vlSymsp->__Vcoverage[68]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 5U;
            } else if (vlSelfRef.testbench__DOT__bump_right) {
                ++(vlSymsp->__Vcoverage[66]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            } else {
                ++(vlSymsp->__Vcoverage[67]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[69]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        }
        ++(vlSymsp->__Vcoverage[72]);
    } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[77]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[75]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[76]);
                            }(), 0U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[78]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[79]);
    } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[84]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[82]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[83]);
                            }(), 1U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[85]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[86]);
    } else if ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[89]);
                    }(), 4U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[90]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[91]);
    } else if ((5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[94]);
                    }(), 5U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[95]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[96]);
    } else if ((6U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[97]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 6U;
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[63]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[64]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[70]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[71]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[73]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[74]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[80]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[81]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[87]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[88]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[92]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[93]);
    }
    ++(vlSymsp->__Vcoverage[98]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 43, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
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
        if (((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             | (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
            if ((0x14U > (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))) {
                vlSelfRef.testbench__DOT__DUT__DOT__fall_counter 
                    = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter)));
                ++(vlSymsp->__Vcoverage[102]);
            } else {
                ++(vlSymsp->__Vcoverage[103]);
            }
            ++(vlSymsp->__Vcoverage[104]);
        } else {
            ++(vlSymsp->__Vcoverage[105]);
            vlSelfRef.testbench__DOT__DUT__DOT__fall_counter = 0U;
        }
        if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[106]);
        }
        if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[107]);
        }
        if (((2U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             & (3U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
            ++(vlSymsp->__Vcoverage[108]);
        }
        ++(vlSymsp->__Vcoverage[109]);
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter))) {
            VL_COV_TOGGLE_CHG_ST_I(5, vlSymsp->__Vcoverage + 49, vlSelfRef.testbench__DOT__DUT__DOT__fall_counter, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter 
                = vlSelfRef.testbench__DOT__DUT__DOT__fall_counter;
        }
    }
    if ((4ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (((IData)(vlSelfRef.testbench__DOT__clk) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__clk))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.testbench__DOT__clk, vlSelfRef.testbench__DOT____Vtogcov__clk);
            vlSelfRef.testbench__DOT____Vtogcov__clk 
                = vlSelfRef.testbench__DOT__clk;
        }
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (((IData)(vlSelfRef.testbench__DOT__areset) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__areset))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.testbench__DOT__areset, vlSelfRef.testbench__DOT____Vtogcov__areset);
            vlSelfRef.testbench__DOT____Vtogcov__areset 
                = vlSelfRef.testbench__DOT__areset;
        }
        if (((IData)(vlSelfRef.testbench__DOT__bump_left) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__bump_left))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 4, vlSelfRef.testbench__DOT__bump_left, vlSelfRef.testbench__DOT____Vtogcov__bump_left);
            vlSelfRef.testbench__DOT____Vtogcov__bump_left 
                = vlSelfRef.testbench__DOT__bump_left;
        }
        if (((IData)(vlSelfRef.testbench__DOT__bump_right) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__bump_right))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 6, vlSelfRef.testbench__DOT__bump_right, vlSelfRef.testbench__DOT____Vtogcov__bump_right);
            vlSelfRef.testbench__DOT____Vtogcov__bump_right 
                = vlSelfRef.testbench__DOT__bump_right;
        }
        if (((IData)(vlSelfRef.testbench__DOT__ground) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__ground))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 8, vlSelfRef.testbench__DOT__ground, vlSelfRef.testbench__DOT____Vtogcov__ground);
            vlSelfRef.testbench__DOT____Vtogcov__ground 
                = vlSelfRef.testbench__DOT__ground;
        }
        if (((IData)(vlSelfRef.testbench__DOT__dig) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__dig))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 10, vlSelfRef.testbench__DOT__dig, vlSelfRef.testbench__DOT____Vtogcov__dig);
            vlSelfRef.testbench__DOT____Vtogcov__dig 
                = vlSelfRef.testbench__DOT__dig;
        }
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (vlSelfRef.testbench__DOT__areset) {
            ++(vlSymsp->__Vcoverage[99]);
            vlSelfRef.testbench__DOT__DUT__DOT__state = 0U;
        } else {
            ++(vlSymsp->__Vcoverage[100]);
            vlSelfRef.testbench__DOT__DUT__DOT__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__next;
        }
        ++(vlSymsp->__Vcoverage[101]);
        if (((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__walk_left))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 12, 
                                   (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__walk_left);
            vlSelfRef.testbench__DOT____Vtogcov__walk_left 
                = (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
        }
        if (((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__walk_right))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 14, 
                                   (1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__walk_right);
            vlSelfRef.testbench__DOT____Vtogcov__walk_right 
                = (1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
        }
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
            VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 37, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__state;
        }
        vlSelfRef.testbench__DOT__aaah = ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
                                          | (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
        vlSelfRef.testbench__DOT__digging = ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
                                             | (5U 
                                                == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
        if (((IData)(vlSelfRef.testbench__DOT__aaah) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__aaah))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 16, vlSelfRef.testbench__DOT__aaah, vlSelfRef.testbench__DOT____Vtogcov__aaah);
            vlSelfRef.testbench__DOT____Vtogcov__aaah 
                = vlSelfRef.testbench__DOT__aaah;
        }
        if (((IData)(vlSelfRef.testbench__DOT__digging) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__digging))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 18, vlSelfRef.testbench__DOT__digging, vlSelfRef.testbench__DOT____Vtogcov__digging);
            vlSelfRef.testbench__DOT____Vtogcov__digging 
                = vlSelfRef.testbench__DOT__digging;
        }
    }
    if ((7ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtestbench___024root___nba_comb__TOP__1(vlSelf);
    }
}

void Vtestbench___024root___timing_commit(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___timing_commit\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((! (2ULL & vlSelfRef.__VactTriggered[0U]))) {
        vlSelfRef.__VtrigSched_h08c4dc9b__0.commit(
                                                   "@(posedge testbench.clk)");
    }
}

void Vtestbench___024root___timing_resume(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___timing_resume\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h08c4dc9b__0.resume(
                                                   "@(posedge testbench.clk)");
    }
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
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
    Vtestbench___024root___timing_commit(vlSelf);
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
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 2, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtestbench___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_100838/lemmings4/5_CGA/iter_3/driver.v", 2, "", "Active region did not converge after 100 tries");
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
