// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_module_tb.h for the primary calling header

#include "Vtop_module_tb__pch.h"

VL_ATTR_COLD void Vtop_module_tb___024root___eval_static(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_static\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop_module_tb___024root___eval_final(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_final\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop_module_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop_module_tb___024root___eval_phase__stl(Vtop_module_tb___024root* vlSelf);

VL_ATTR_COLD void Vtop_module_tb___024root___eval_settle(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_settle\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop_module_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 3, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vtop_module_tb___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vtop_module_tb___024root___eval_triggers__stl(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_triggers__stl\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop_module_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vtop_module_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop_module_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop_module_tb___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtop_module_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtop_module_tb___024root___eval_stl(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_stl\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
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

VL_ATTR_COLD bool Vtop_module_tb___024root___eval_phase__stl(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___eval_phase__stl\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop_module_tb___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vtop_module_tb___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtop_module_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtop_module_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop_module_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop_module_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop_module_tb___024root___ctor_var_reset(Vtop_module_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___ctor_var_reset\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->top_module_tb__DOT__in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7470190814086532193ull);
    vlSelf->top_module_tb__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7349863392941421477ull);
    vlSelf->top_module_tb__DOT____Vtogcov__in = 0;
    vlSelf->top_module_tb__DOT____Vtogcov__clk = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}

VL_ATTR_COLD void Vtop_module_tb___024root___configure_coverage(Vtop_module_tb___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_module_tb___024root___configure_coverage\n"); );
    Vtop_module_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 4, 9, ".top_module_tb", "v_toggle/top_module_tb", "in");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 5, 10, ".top_module_tb", "v_toggle/top_module_tb", "out");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[2]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 6, 9, ".top_module_tb", "v_toggle/top_module_tb", "clk");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 19, 26, ".top_module_tb", "v_expr/top_module_tb", "(clk==0) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 19, 26, ".top_module_tb", "v_expr/top_module_tb", "(clk==1) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 19, 9, ".top_module_tb", "v_line/top_module_tb", "block", "19");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 17, 5, ".top_module_tb", "v_line/top_module_tb", "block", "17-18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 26, 9, ".top_module_tb", "v_branch/top_module_tb", "if", "26-28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 26, 10, ".top_module_tb", "v_branch/top_module_tb", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/driver.v", 23, 5, ".top_module_tb", "v_line/top_module_tb", "block", "23,25,32-37,40-45,48-53,56-61,64-65");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/DUT.v", 2, 8, ".top_module_tb.DUT", "v_toggle/top_module", "in");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260305_172510/wire/5_CGA/iter_0/DUT.v", 3, 9, ".top_module_tb.DUT", "v_toggle/top_module", "out");
}
