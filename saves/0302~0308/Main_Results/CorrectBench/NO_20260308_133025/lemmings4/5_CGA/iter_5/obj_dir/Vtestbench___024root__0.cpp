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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
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
    IData/*31:0*/ testbench__DOT__unnamedblk1_12__DOT____Vrepeat11;
    testbench__DOT__unnamedblk1_12__DOT____Vrepeat11 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_13__DOT____Vrepeat12;
    testbench__DOT__unnamedblk1_13__DOT____Vrepeat12 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_14__DOT____Vrepeat13;
    testbench__DOT__unnamedblk1_14__DOT____Vrepeat13 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_15__DOT____Vrepeat14;
    testbench__DOT__unnamedblk1_15__DOT____Vrepeat14 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_16__DOT____Vrepeat15;
    testbench__DOT__unnamedblk1_16__DOT____Vrepeat15 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_17__DOT____Vrepeat16;
    testbench__DOT__unnamedblk1_17__DOT____Vrepeat16 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_18__DOT____Vrepeat17;
    testbench__DOT__unnamedblk1_18__DOT____Vrepeat17 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_19__DOT____Vrepeat18;
    testbench__DOT__unnamedblk1_19__DOT____Vrepeat18 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_20__DOT____Vrepeat19;
    testbench__DOT__unnamedblk1_20__DOT____Vrepeat19 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_21__DOT____Vrepeat20;
    testbench__DOT__unnamedblk1_21__DOT____Vrepeat20 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_22__DOT____Vrepeat21;
    testbench__DOT__unnamedblk1_22__DOT____Vrepeat21 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_23__DOT____Vrepeat22;
    testbench__DOT__unnamedblk1_23__DOT____Vrepeat22 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_24__DOT____Vrepeat23;
    testbench__DOT__unnamedblk1_24__DOT____Vrepeat23 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_25__DOT____Vrepeat24;
    testbench__DOT__unnamedblk1_25__DOT____Vrepeat24 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_26__DOT____Vrepeat25;
    testbench__DOT__unnamedblk1_26__DOT____Vrepeat25 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_27__DOT____Vrepeat26;
    testbench__DOT__unnamedblk1_27__DOT____Vrepeat26 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_28__DOT____Vrepeat27;
    testbench__DOT__unnamedblk1_28__DOT____Vrepeat27 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_29__DOT____Vrepeat28;
    testbench__DOT__unnamedblk1_29__DOT____Vrepeat28 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_30__DOT____Vrepeat29;
    testbench__DOT__unnamedblk1_30__DOT____Vrepeat29 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_31__DOT____Vrepeat30;
    testbench__DOT__unnamedblk1_31__DOT____Vrepeat30 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_32__DOT____Vrepeat31;
    testbench__DOT__unnamedblk1_32__DOT____Vrepeat31 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_33__DOT____Vrepeat32;
    testbench__DOT__unnamedblk1_33__DOT____Vrepeat32 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_34__DOT____Vrepeat33;
    testbench__DOT__unnamedblk1_34__DOT____Vrepeat33 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_35__DOT____Vrepeat34;
    testbench__DOT__unnamedblk1_35__DOT____Vrepeat34 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_36__DOT____Vrepeat35;
    testbench__DOT__unnamedblk1_36__DOT____Vrepeat35 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_37__DOT____Vrepeat36;
    testbench__DOT__unnamedblk1_37__DOT____Vrepeat36 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_38__DOT____Vrepeat37;
    testbench__DOT__unnamedblk1_38__DOT____Vrepeat37 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_39__DOT____Vrepeat38;
    testbench__DOT__unnamedblk1_39__DOT____Vrepeat38 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_40__DOT____Vrepeat39;
    testbench__DOT__unnamedblk1_40__DOT____Vrepeat39 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_41__DOT____Vrepeat40;
    testbench__DOT__unnamedblk1_41__DOT____Vrepeat40 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_42__DOT____Vrepeat41;
    testbench__DOT__unnamedblk1_42__DOT____Vrepeat41 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_43__DOT____Vrepeat42;
    testbench__DOT__unnamedblk1_43__DOT____Vrepeat42 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_44__DOT____Vrepeat43;
    testbench__DOT__unnamedblk1_44__DOT____Vrepeat43 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_45__DOT____Vrepeat44;
    testbench__DOT__unnamedblk1_45__DOT____Vrepeat44 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_46__DOT____Vrepeat45;
    testbench__DOT__unnamedblk1_46__DOT____Vrepeat45 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_47__DOT____Vrepeat46;
    testbench__DOT__unnamedblk1_47__DOT____Vrepeat46 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_48__DOT____Vrepeat47;
    testbench__DOT__unnamedblk1_48__DOT____Vrepeat47 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_49__DOT____Vrepeat48;
    testbench__DOT__unnamedblk1_49__DOT____Vrepeat48 = 0;
    IData/*31:0*/ testbench__DOT__unnamedblk1_50__DOT____Vrepeat49;
    testbench__DOT__unnamedblk1_50__DOT____Vrepeat49 = 0;
    // Body
    testbench__DOT__scenario = 1U;
    vlSelfRef.testbench__DOT__areset = 1U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 0U;
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"scenario:           1, clk = %1#, areset = 1, bump_left = 0, bump_right = 0, ground = 0, dig = 0, walk_left = %1#, walk_right = %1#, aaah = %1#, digging = %1#\n",0,
                  1,vlSelfRef.testbench__DOT__clk,1,
                  (0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         45);
    testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x0000000aU;
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             48);
        testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (testbench__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[25]);
    }
    testbench__DOT__scenario = 2U;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         55);
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         57);
    testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             60);
        testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (testbench__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[26]);
    }
    testbench__DOT__scenario = 3U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         67);
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         69);
    testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             72);
        testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (testbench__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[27]);
    }
    testbench__DOT__scenario = 4U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         78);
    testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_4__DOT____Vrepeat3)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             81);
        testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 
            = (testbench__DOT__unnamedblk1_4__DOT____Vrepeat3 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[28]);
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         84);
    testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_5__DOT____Vrepeat4)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             87);
        testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 
            = (testbench__DOT__unnamedblk1_5__DOT____Vrepeat4 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[29]);
    }
    testbench__DOT__scenario = 5U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         93);
    testbench__DOT__unnamedblk1_6__DOT____Vrepeat5 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_6__DOT____Vrepeat5)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             96);
        testbench__DOT__unnamedblk1_6__DOT____Vrepeat5 
            = (testbench__DOT__unnamedblk1_6__DOT____Vrepeat5 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[30]);
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         99);
    testbench__DOT__unnamedblk1_7__DOT____Vrepeat6 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_7__DOT____Vrepeat6)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             102);
        testbench__DOT__unnamedblk1_7__DOT____Vrepeat6 
            = (testbench__DOT__unnamedblk1_7__DOT____Vrepeat6 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[31]);
    }
    testbench__DOT__scenario = 6U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         108);
    testbench__DOT__unnamedblk1_8__DOT____Vrepeat7 = 0x00000019U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_8__DOT____Vrepeat7)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             111);
        testbench__DOT__unnamedblk1_8__DOT____Vrepeat7 
            = (testbench__DOT__unnamedblk1_8__DOT____Vrepeat7 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[32]);
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         114);
    testbench__DOT__unnamedblk1_9__DOT____Vrepeat8 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_9__DOT____Vrepeat8)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             117);
        testbench__DOT__unnamedblk1_9__DOT____Vrepeat8 
            = (testbench__DOT__unnamedblk1_9__DOT____Vrepeat8 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[33]);
    }
    testbench__DOT__scenario = 7U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         123);
    testbench__DOT__unnamedblk1_10__DOT____Vrepeat9 = 0x00000019U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_10__DOT____Vrepeat9)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             126);
        testbench__DOT__unnamedblk1_10__DOT____Vrepeat9 
            = (testbench__DOT__unnamedblk1_10__DOT____Vrepeat9 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[34]);
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         129);
    testbench__DOT__unnamedblk1_11__DOT____Vrepeat10 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_11__DOT____Vrepeat10)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             132);
        testbench__DOT__unnamedblk1_11__DOT____Vrepeat10 
            = (testbench__DOT__unnamedblk1_11__DOT____Vrepeat10 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[35]);
    }
    testbench__DOT__scenario = 8U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 1U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         138);
    testbench__DOT__unnamedblk1_12__DOT____Vrepeat11 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_12__DOT____Vrepeat11)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             141);
        testbench__DOT__unnamedblk1_12__DOT____Vrepeat11 
            = (testbench__DOT__unnamedblk1_12__DOT____Vrepeat11 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[36]);
    }
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         144);
    testbench__DOT__unnamedblk1_13__DOT____Vrepeat12 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_13__DOT____Vrepeat12)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             147);
        testbench__DOT__unnamedblk1_13__DOT____Vrepeat12 
            = (testbench__DOT__unnamedblk1_13__DOT____Vrepeat12 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[37]);
    }
    testbench__DOT__scenario = 9U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 1U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         153);
    testbench__DOT__unnamedblk1_14__DOT____Vrepeat13 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_14__DOT____Vrepeat13)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             156);
        testbench__DOT__unnamedblk1_14__DOT____Vrepeat13 
            = (testbench__DOT__unnamedblk1_14__DOT____Vrepeat13 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[38]);
    }
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         159);
    testbench__DOT__unnamedblk1_15__DOT____Vrepeat14 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_15__DOT____Vrepeat14)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             162);
        testbench__DOT__unnamedblk1_15__DOT____Vrepeat14 
            = (testbench__DOT__unnamedblk1_15__DOT____Vrepeat14 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[39]);
    }
    testbench__DOT__scenario = 0x0000000aU;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         168);
    testbench__DOT__unnamedblk1_16__DOT____Vrepeat15 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_16__DOT____Vrepeat15)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             171);
        testbench__DOT__unnamedblk1_16__DOT____Vrepeat15 
            = (testbench__DOT__unnamedblk1_16__DOT____Vrepeat15 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[40]);
    }
    testbench__DOT__scenario = 0x0000000bU;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         177);
    testbench__DOT__unnamedblk1_17__DOT____Vrepeat16 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_17__DOT____Vrepeat16)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             180);
        testbench__DOT__unnamedblk1_17__DOT____Vrepeat16 
            = (testbench__DOT__unnamedblk1_17__DOT____Vrepeat16 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[41]);
    }
    testbench__DOT__scenario = 0x0000000cU;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    vlSelfRef.testbench__DOT__ground = 0U;
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         186);
    testbench__DOT__unnamedblk1_18__DOT____Vrepeat17 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_18__DOT____Vrepeat17)) {
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
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                             189);
        testbench__DOT__unnamedblk1_18__DOT____Vrepeat17 
            = (testbench__DOT__unnamedblk1_18__DOT____Vrepeat17 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[42]);
    }
    testbench__DOT__scenario = 0x00000065U;
    vlSelfRef.testbench__DOT__areset = 0U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         195);
    vlSelfRef.testbench__DOT__areset = 1U;
    testbench__DOT__unnamedblk1_19__DOT____Vrepeat18 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_19__DOT____Vrepeat18)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             199);
        testbench__DOT__unnamedblk1_19__DOT____Vrepeat18 
            = (testbench__DOT__unnamedblk1_19__DOT____Vrepeat18 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[43]);
    }
    vlSelfRef.testbench__DOT__areset = 0U;
    testbench__DOT__unnamedblk1_20__DOT____Vrepeat19 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_20__DOT____Vrepeat19)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             202);
        testbench__DOT__unnamedblk1_20__DOT____Vrepeat19 
            = (testbench__DOT__unnamedblk1_20__DOT____Vrepeat19 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[44]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 1U;
    testbench__DOT__unnamedblk1_21__DOT____Vrepeat20 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_21__DOT____Vrepeat20)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             208);
        testbench__DOT__unnamedblk1_21__DOT____Vrepeat20 
            = (testbench__DOT__unnamedblk1_21__DOT____Vrepeat20 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[45]);
    }
    testbench__DOT__unnamedblk1_22__DOT____Vrepeat21 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_22__DOT____Vrepeat21)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             210);
        testbench__DOT__unnamedblk1_22__DOT____Vrepeat21 
            = (testbench__DOT__unnamedblk1_22__DOT____Vrepeat21 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[46]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 1U;
    testbench__DOT__unnamedblk1_23__DOT____Vrepeat22 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_23__DOT____Vrepeat22)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             216);
        testbench__DOT__unnamedblk1_23__DOT____Vrepeat22 
            = (testbench__DOT__unnamedblk1_23__DOT____Vrepeat22 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[47]);
    }
    testbench__DOT__unnamedblk1_24__DOT____Vrepeat23 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_24__DOT____Vrepeat23)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             218);
        testbench__DOT__unnamedblk1_24__DOT____Vrepeat23 
            = (testbench__DOT__unnamedblk1_24__DOT____Vrepeat23 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[48]);
    }
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[CGA-1] walk_left, walk_right, aaah, digging = %b, %b, %b, %b\n",0,
                  1,(0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    testbench__DOT__scenario = 0x00000066U;
    vlSelfRef.testbench__DOT__areset = 0U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         226);
    vlSelfRef.testbench__DOT__areset = 1U;
    testbench__DOT__unnamedblk1_25__DOT____Vrepeat24 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_25__DOT____Vrepeat24)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             230);
        testbench__DOT__unnamedblk1_25__DOT____Vrepeat24 
            = (testbench__DOT__unnamedblk1_25__DOT____Vrepeat24 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[49]);
    }
    vlSelfRef.testbench__DOT__areset = 0U;
    testbench__DOT__unnamedblk1_26__DOT____Vrepeat25 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_26__DOT____Vrepeat25)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             233);
        testbench__DOT__unnamedblk1_26__DOT____Vrepeat25 
            = (testbench__DOT__unnamedblk1_26__DOT____Vrepeat25 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[50]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    testbench__DOT__unnamedblk1_27__DOT____Vrepeat26 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_27__DOT____Vrepeat26)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             239);
        testbench__DOT__unnamedblk1_27__DOT____Vrepeat26 
            = (testbench__DOT__unnamedblk1_27__DOT____Vrepeat26 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[51]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    testbench__DOT__unnamedblk1_28__DOT____Vrepeat27 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_28__DOT____Vrepeat27)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             245);
        testbench__DOT__unnamedblk1_28__DOT____Vrepeat27 
            = (testbench__DOT__unnamedblk1_28__DOT____Vrepeat27 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[52]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_left = 1U;
    testbench__DOT__unnamedblk1_29__DOT____Vrepeat28 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_29__DOT____Vrepeat28)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             251);
        testbench__DOT__unnamedblk1_29__DOT____Vrepeat28 
            = (testbench__DOT__unnamedblk1_29__DOT____Vrepeat28 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[53]);
    }
    vlSelfRef.testbench__DOT__ground = 0U;
    testbench__DOT__unnamedblk1_30__DOT____Vrepeat29 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_30__DOT____Vrepeat29)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             254);
        testbench__DOT__unnamedblk1_30__DOT____Vrepeat29 
            = (testbench__DOT__unnamedblk1_30__DOT____Vrepeat29 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[54]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    testbench__DOT__unnamedblk1_31__DOT____Vrepeat30 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_31__DOT____Vrepeat30)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             259);
        testbench__DOT__unnamedblk1_31__DOT____Vrepeat30 
            = (testbench__DOT__unnamedblk1_31__DOT____Vrepeat30 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[55]);
    }
    testbench__DOT__unnamedblk1_32__DOT____Vrepeat31 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_32__DOT____Vrepeat31)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             263);
        testbench__DOT__unnamedblk1_32__DOT____Vrepeat31 
            = (testbench__DOT__unnamedblk1_32__DOT____Vrepeat31 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[56]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 1U;
    testbench__DOT__unnamedblk1_33__DOT____Vrepeat32 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_33__DOT____Vrepeat32)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             267);
        testbench__DOT__unnamedblk1_33__DOT____Vrepeat32 
            = (testbench__DOT__unnamedblk1_33__DOT____Vrepeat32 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[57]);
    }
    vlSelfRef.testbench__DOT__dig = 0U;
    testbench__DOT__unnamedblk1_34__DOT____Vrepeat33 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_34__DOT____Vrepeat33)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             270);
        testbench__DOT__unnamedblk1_34__DOT____Vrepeat33 
            = (testbench__DOT__unnamedblk1_34__DOT____Vrepeat33 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[58]);
    }
    vlSelfRef.testbench__DOT__bump_right = 1U;
    testbench__DOT__unnamedblk1_35__DOT____Vrepeat34 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_35__DOT____Vrepeat34)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             273);
        testbench__DOT__unnamedblk1_35__DOT____Vrepeat34 
            = (testbench__DOT__unnamedblk1_35__DOT____Vrepeat34 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[59]);
    }
    vlSelfRef.testbench__DOT__dig = 1U;
    testbench__DOT__unnamedblk1_36__DOT____Vrepeat35 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_36__DOT____Vrepeat35)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             276);
        testbench__DOT__unnamedblk1_36__DOT____Vrepeat35 
            = (testbench__DOT__unnamedblk1_36__DOT____Vrepeat35 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[60]);
    }
    vlSelfRef.testbench__DOT__dig = 0U;
    testbench__DOT__unnamedblk1_37__DOT____Vrepeat36 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_37__DOT____Vrepeat36)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             279);
        testbench__DOT__unnamedblk1_37__DOT____Vrepeat36 
            = (testbench__DOT__unnamedblk1_37__DOT____Vrepeat36 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[61]);
    }
    testbench__DOT__unnamedblk1_38__DOT____Vrepeat37 = 1U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_38__DOT____Vrepeat37)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             283);
        testbench__DOT__unnamedblk1_38__DOT____Vrepeat37 
            = (testbench__DOT__unnamedblk1_38__DOT____Vrepeat37 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[62]);
    }
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[CGA-2] walk_left, walk_right, aaah, digging = %b, %b, %b, %b\n",0,
                  1,(0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
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
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         291);
    vlSelfRef.testbench__DOT__areset = 1U;
    testbench__DOT__unnamedblk1_39__DOT____Vrepeat38 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_39__DOT____Vrepeat38)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             295);
        testbench__DOT__unnamedblk1_39__DOT____Vrepeat38 
            = (testbench__DOT__unnamedblk1_39__DOT____Vrepeat38 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[63]);
    }
    vlSelfRef.testbench__DOT__areset = 0U;
    testbench__DOT__unnamedblk1_40__DOT____Vrepeat39 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_40__DOT____Vrepeat39)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             298);
        testbench__DOT__unnamedblk1_40__DOT____Vrepeat39 
            = (testbench__DOT__unnamedblk1_40__DOT____Vrepeat39 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[64]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         303);
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         308);
    testbench__DOT__unnamedblk1_41__DOT____Vrepeat40 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_41__DOT____Vrepeat40)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             310);
        testbench__DOT__unnamedblk1_41__DOT____Vrepeat40 
            = (testbench__DOT__unnamedblk1_41__DOT____Vrepeat40 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[65]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         315);
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         320);
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[CGA-3] walk_left, walk_right, aaah, digging = %b, %b, %b, %b\n",0,
                  1,(0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    testbench__DOT__scenario = 0x00000069U;
    vlSelfRef.testbench__DOT__areset = 0U;
    vlSelfRef.testbench__DOT__bump_left = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    vlSelfRef.testbench__DOT__ground = 0U;
    vlSelfRef.testbench__DOT__dig = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         328);
    vlSelfRef.testbench__DOT__areset = 1U;
    testbench__DOT__unnamedblk1_42__DOT____Vrepeat41 = 2U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_42__DOT____Vrepeat41)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             332);
        testbench__DOT__unnamedblk1_42__DOT____Vrepeat41 
            = (testbench__DOT__unnamedblk1_42__DOT____Vrepeat41 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[66]);
    }
    vlSelfRef.testbench__DOT__areset = 0U;
    testbench__DOT__unnamedblk1_43__DOT____Vrepeat42 = 3U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_43__DOT____Vrepeat42)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             335);
        testbench__DOT__unnamedblk1_43__DOT____Vrepeat42 
            = (testbench__DOT__unnamedblk1_43__DOT____Vrepeat42 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[67]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         344);
    vlSelfRef.testbench__DOT__dig = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         347);
    vlSelfRef.testbench__DOT__bump_right = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         350);
    testbench__DOT__unnamedblk1_44__DOT____Vrepeat43 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_44__DOT____Vrepeat43)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             353);
        testbench__DOT__unnamedblk1_44__DOT____Vrepeat43 
            = (testbench__DOT__unnamedblk1_44__DOT____Vrepeat43 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[68]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         365);
    testbench__DOT__unnamedblk1_45__DOT____Vrepeat44 = 0x00000014U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_45__DOT____Vrepeat44)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             369);
        testbench__DOT__unnamedblk1_45__DOT____Vrepeat44 
            = (testbench__DOT__unnamedblk1_45__DOT____Vrepeat44 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[69]);
    }
    testbench__DOT__unnamedblk1_46__DOT____Vrepeat45 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_46__DOT____Vrepeat45)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             372);
        testbench__DOT__unnamedblk1_46__DOT____Vrepeat45 
            = (testbench__DOT__unnamedblk1_46__DOT____Vrepeat45 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[70]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 0U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         383);
    testbench__DOT__unnamedblk1_47__DOT____Vrepeat46 = 0x00000014U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_47__DOT____Vrepeat46)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             386);
        testbench__DOT__unnamedblk1_47__DOT____Vrepeat46 
            = (testbench__DOT__unnamedblk1_47__DOT____Vrepeat46 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[71]);
    }
    testbench__DOT__unnamedblk1_48__DOT____Vrepeat47 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_48__DOT____Vrepeat47)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             389);
        testbench__DOT__unnamedblk1_48__DOT____Vrepeat47 
            = (testbench__DOT__unnamedblk1_48__DOT____Vrepeat47 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[72]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 1U;
    vlSelfRef.testbench__DOT__bump_right = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         399);
    testbench__DOT__unnamedblk1_49__DOT____Vrepeat48 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_49__DOT____Vrepeat48)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             402);
        testbench__DOT__unnamedblk1_49__DOT____Vrepeat48 
            = (testbench__DOT__unnamedblk1_49__DOT____Vrepeat48 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[73]);
    }
    vlSelfRef.testbench__DOT__ground = 1U;
    vlSelfRef.testbench__DOT__dig = 1U;
    vlSelfRef.testbench__DOT__bump_right = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                         412);
    testbench__DOT__unnamedblk1_50__DOT____Vrepeat49 = 5U;
    while (VL_LTS_III(32, 0U, testbench__DOT__unnamedblk1_50__DOT____Vrepeat49)) {
        co_await vlSelfRef.__VtrigSched_h08c4dc9b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge testbench.clk)", 
                                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 
                                                             415);
        testbench__DOT__unnamedblk1_50__DOT____Vrepeat49 
            = (testbench__DOT__unnamedblk1_50__DOT____Vrepeat49 
               - (IData)(1U));
        ++(vlSymsp->__Vcoverage[74]);
    }
    VL_FWRITEF_NX(vlSelfRef.testbench__DOT__file,"[CGA-5] walk_left, walk_right, aaah, digging = %b, %b, %b, %b\n",0,
                  1,(0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)),
                  1,(IData)(vlSelfRef.testbench__DOT__aaah),
                  1,vlSelfRef.testbench__DOT__digging);
    VL_FCLOSE_I(vlSelfRef.testbench__DOT__file); VL_FINISH_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 425, "");
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
                ++(vlSymsp->__Vcoverage[100]);
            } else if (vlSelfRef.testbench__DOT__bump_left) {
                ++(vlSymsp->__Vcoverage[98]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            } else {
                ++(vlSymsp->__Vcoverage[99]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[101]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        }
        ++(vlSymsp->__Vcoverage[104]);
    } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        if (vlSelfRef.testbench__DOT__ground) {
            if (vlSelfRef.testbench__DOT__dig) {
                ++(vlSymsp->__Vcoverage[107]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 5U;
            } else if (vlSelfRef.testbench__DOT__bump_right) {
                ++(vlSymsp->__Vcoverage[105]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            } else {
                ++(vlSymsp->__Vcoverage[106]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[108]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        }
        ++(vlSymsp->__Vcoverage[111]);
    } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[116]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[114]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[115]);
                            }(), 0U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[117]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[118]);
    } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[123]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[121]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[122]);
                            }(), 1U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[124]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[125]);
    } else if ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[128]);
                    }(), 4U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[129]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[130]);
    } else if ((5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[133]);
                    }(), 5U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[134]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[135]);
    } else if ((6U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[136]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 6U;
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[102]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[103]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[109]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[110]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[112]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[113]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[119]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[120]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[126]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[127]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[131]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[132]);
    }
    ++(vlSymsp->__Vcoverage[137]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 82, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
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
            ++(vlSymsp->__Vcoverage[141]);
        } else {
            ++(vlSymsp->__Vcoverage[142]);
        }
        ++(vlSymsp->__Vcoverage[143]);
    } else {
        ++(vlSymsp->__Vcoverage[144]);
        vlSelfRef.testbench__DOT__DUT__DOT__fall_counter = 0U;
    }
    if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[145]);
    }
    if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[146]);
    }
    if (((2U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         & (3U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
        ++(vlSymsp->__Vcoverage[147]);
    }
    ++(vlSymsp->__Vcoverage[148]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter))) {
        VL_COV_TOGGLE_CHG_ST_I(5, vlSymsp->__Vcoverage + 88, vlSelfRef.testbench__DOT__DUT__DOT__fall_counter, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter);
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
        ++(vlSymsp->__Vcoverage[138]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = 0U;
    } else {
        ++(vlSymsp->__Vcoverage[139]);
        vlSelfRef.testbench__DOT__DUT__DOT__state = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
    ++(vlSymsp->__Vcoverage[140]);
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
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 76, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
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
                ++(vlSymsp->__Vcoverage[100]);
            } else if (vlSelfRef.testbench__DOT__bump_left) {
                ++(vlSymsp->__Vcoverage[98]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            } else {
                ++(vlSymsp->__Vcoverage[99]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[101]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        }
        ++(vlSymsp->__Vcoverage[104]);
    } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        if (vlSelfRef.testbench__DOT__ground) {
            if (vlSelfRef.testbench__DOT__dig) {
                ++(vlSymsp->__Vcoverage[107]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 5U;
            } else if (vlSelfRef.testbench__DOT__bump_right) {
                ++(vlSymsp->__Vcoverage[105]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 0U;
            } else {
                ++(vlSymsp->__Vcoverage[106]);
                vlSelfRef.testbench__DOT__DUT__DOT__next = 1U;
            }
        } else {
            ++(vlSymsp->__Vcoverage[108]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        }
        ++(vlSymsp->__Vcoverage[111]);
    } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[116]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[114]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[115]);
                            }(), 0U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[117]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[118]);
    } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[123]);
                    }(), ((0x14U <= (IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[121]);
                            }(), 6U) : ([&]() {
                                ++(vlSymsp->__Vcoverage[122]);
                            }(), 1U))) : ([&]() {
                        ++(vlSymsp->__Vcoverage[124]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[125]);
    } else if ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[128]);
                    }(), 4U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[129]);
                    }(), 2U)));
        ++(vlSymsp->__Vcoverage[130]);
    } else if ((5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (7U & ((IData)(vlSelfRef.testbench__DOT__ground)
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[133]);
                    }(), 5U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[134]);
                    }(), 3U)));
        ++(vlSymsp->__Vcoverage[135]);
    } else if ((6U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[136]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 6U;
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[102]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[103]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[109]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[110]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[112]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[113]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[119]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[120]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[126]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[127]);
    }
    if (vlSelfRef.testbench__DOT__ground) {
        ++(vlSymsp->__Vcoverage[131]);
    }
    if ((1U & (~ (IData)(vlSelfRef.testbench__DOT__ground)))) {
        ++(vlSymsp->__Vcoverage[132]);
    }
    ++(vlSymsp->__Vcoverage[137]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 82, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
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
                ++(vlSymsp->__Vcoverage[141]);
            } else {
                ++(vlSymsp->__Vcoverage[142]);
            }
            ++(vlSymsp->__Vcoverage[143]);
        } else {
            ++(vlSymsp->__Vcoverage[144]);
            vlSelfRef.testbench__DOT__DUT__DOT__fall_counter = 0U;
        }
        if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[145]);
        }
        if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[146]);
        }
        if (((2U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             & (3U != (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)))) {
            ++(vlSymsp->__Vcoverage[147]);
        }
        ++(vlSymsp->__Vcoverage[148]);
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter))) {
            VL_COV_TOGGLE_CHG_ST_I(5, vlSymsp->__Vcoverage + 88, vlSelfRef.testbench__DOT__DUT__DOT__fall_counter, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter);
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
            ++(vlSymsp->__Vcoverage[138]);
            vlSelfRef.testbench__DOT__DUT__DOT__state = 0U;
        } else {
            ++(vlSymsp->__Vcoverage[139]);
            vlSelfRef.testbench__DOT__DUT__DOT__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__next;
        }
        ++(vlSymsp->__Vcoverage[140]);
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
            VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 76, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
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
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 2, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtestbench___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260308_133025/lemmings4/5_CGA/iter_5/driver.v", 2, "", "Active region did not converge after 100 tries");
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
