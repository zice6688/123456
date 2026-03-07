// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_module_tb.h for the primary calling header

#include "Vtop_module_tb__pch.h"

VlCoroutine Vtop_module_tb___024root___eval_initial__TOP__Vtiming__0(Vtop_module_tb___024root* vlSelf);
VlCoroutine Vtop_module_tb___024root___eval_initial__TOP__Vtiming__1(Vtop_module_tb___024root* vlSelf);

void Vtop_module_tb___024root___eval_initial(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_initial\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop_module_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtop_module_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vtop_module_tb___024root___eval_initial__TOP__Vtiming__0(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top_module_tb__DOT__clk = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                             19);
        vlSelfRef.top_module_tb__DOT__clk = (1U & (~ (IData)(vlSelfRef.top_module_tb__DOT__clk)));
        ++(vlSymsp->__Vcoverage[6]);
    }
    if ((1U & (~ (IData)(vlSelfRef.top_module_tb__DOT__clk)))) {
        ++(vlSymsp->__Vcoverage[4]);
    }
    if (vlSelfRef.top_module_tb__DOT__clk) {
        ++(vlSymsp->__Vcoverage[5]);
    }
    ++(vlSymsp->__Vcoverage[7]);
    co_return;}

VlCoroutine Vtop_module_tb___024root___eval_initial__TOP__Vtiming__1(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ top_module_tb__DOT__file;
    top_module_tb__DOT__file = 0;
    IData/*31:0*/ top_module_tb__DOT__scenario;
    top_module_tb__DOT__scenario = 0;
    // Body
    top_module_tb__DOT__file = VL_FOPEN_NN("TBout.txt"s
                                           , "w"s);
    ;
    if (VL_UNLIKELY(((0U == top_module_tb__DOT__file)))) {
        VL_WRITEF_NX("Error: Unable to open file TBout.txt\n",0);
        VL_FINISH_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 28, "");
        ++(vlSymsp->__Vcoverage[8]);
    } else {
        ++(vlSymsp->__Vcoverage[9]);
    }
    top_module_tb__DOT__scenario = 1U;
    vlSelfRef.top_module_tb__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         34);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         36);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    top_module_tb__DOT__scenario = 2U;
    vlSelfRef.top_module_tb__DOT__in = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         42);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         44);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    top_module_tb__DOT__scenario = 3U;
    vlSelfRef.top_module_tb__DOT__in = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         50);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         52);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    top_module_tb__DOT__scenario = 4U;
    vlSelfRef.top_module_tb__DOT__in = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         58);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 
                                         60);
    VL_FWRITEF_NX(top_module_tb__DOT__file,"scenario: %11d, in = %1#, out = %1#\n",0,
                  32,top_module_tb__DOT__scenario,1,
                  (IData)(vlSelfRef.top_module_tb__DOT__in),
                  1,vlSelfRef.top_module_tb__DOT__in);
    VL_FCLOSE_I(top_module_tb__DOT__file); VL_FINISH_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 65, "");
    ++(vlSymsp->__Vcoverage[10]);
    co_return;}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop_module_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vtop_module_tb___024root___eval_triggers__act(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_triggers__act\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(vlSelfRef.__VdlySched.awaitingCurrentTime()));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop_module_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vtop_module_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___trigger_anySet__act\n"); );
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

void Vtop_module_tb___024root___act_sequent__TOP__0(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___act_sequent__TOP__0\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.top_module_tb__DOT__in) 
         ^ (IData)(vlSelfRef.top_module_tb__DOT____Vtogcov__in))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.top_module_tb__DOT__in, vlSelfRef.top_module_tb__DOT____Vtogcov__in);
        vlSelfRef.top_module_tb__DOT____Vtogcov__in 
            = vlSelfRef.top_module_tb__DOT__in;
    }
    if (((IData)(vlSelfRef.top_module_tb__DOT__clk) 
         ^ (IData)(vlSelfRef.top_module_tb__DOT____Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.top_module_tb__DOT__clk, vlSelfRef.top_module_tb__DOT____Vtogcov__clk);
        vlSelfRef.top_module_tb__DOT____Vtogcov__clk 
            = vlSelfRef.top_module_tb__DOT__clk;
    }
}

void Vtop_module_tb___024root___eval_act(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_act\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        if (((IData)(vlSelfRef.top_module_tb__DOT__in) 
             ^ (IData)(vlSelfRef.top_module_tb__DOT____Vtogcov__in))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.top_module_tb__DOT__in, vlSelfRef.top_module_tb__DOT____Vtogcov__in);
            vlSelfRef.top_module_tb__DOT____Vtogcov__in 
                = vlSelfRef.top_module_tb__DOT__in;
        }
        if (((IData)(vlSelfRef.top_module_tb__DOT__clk) 
             ^ (IData)(vlSelfRef.top_module_tb__DOT____Vtogcov__clk))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.top_module_tb__DOT__clk, vlSelfRef.top_module_tb__DOT____Vtogcov__clk);
            vlSelfRef.top_module_tb__DOT____Vtogcov__clk 
                = vlSelfRef.top_module_tb__DOT__clk;
        }
    }
}

void Vtop_module_tb___024root___eval_nba(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_nba\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (((IData)(vlSelfRef.top_module_tb__DOT__in) 
             ^ (IData)(vlSelfRef.top_module_tb__DOT____Vtogcov__in))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.top_module_tb__DOT__in, vlSelfRef.top_module_tb__DOT____Vtogcov__in);
            vlSelfRef.top_module_tb__DOT____Vtogcov__in 
                = vlSelfRef.top_module_tb__DOT__in;
        }
        if (((IData)(vlSelfRef.top_module_tb__DOT__clk) 
             ^ (IData)(vlSelfRef.top_module_tb__DOT____Vtogcov__clk))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.top_module_tb__DOT__clk, vlSelfRef.top_module_tb__DOT____Vtogcov__clk);
            vlSelfRef.top_module_tb__DOT____Vtogcov__clk 
                = vlSelfRef.top_module_tb__DOT__clk;
        }
    }
}

void Vtop_module_tb___024root___timing_resume(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___timing_resume\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtop_module_tb___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtop_module_tb___024root___eval_phase__act(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_phase__act\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop_module_tb___024root___eval_triggers__act(vlSelf);
    Vtop_module_tb___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtop_module_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        Vtop_module_tb___024root___timing_resume(vlSelf);
        Vtop_module_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vtop_module_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtop_module_tb___024root___eval_phase__nba(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_phase__nba\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtop_module_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtop_module_tb___024root___eval_nba(vlSelf);
        Vtop_module_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtop_module_tb___024root___eval(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop_module_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop_module_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vtop_module_tb___024root___eval_phase__act(vlSelf));
    } while (Vtop_module_tb___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vtop_module_tb___024root___eval_debug_assertions(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_debug_assertions\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
