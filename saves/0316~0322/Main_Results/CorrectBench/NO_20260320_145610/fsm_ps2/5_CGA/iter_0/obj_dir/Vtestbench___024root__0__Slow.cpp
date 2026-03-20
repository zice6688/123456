// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtestbench.h for the primary calling header

#include "Vtestbench__pch.h"

VL_ATTR_COLD void Vtestbench___024root___eval_static(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_static\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__testbench__DOT__clk__0 
        = vlSelfRef.testbench__DOT__clk;
}

VL_ATTR_COLD void Vtestbench___024root___eval_initial__TOP(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_initial__TOP\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.testbench__DOT__file = VL_FOPEN_NN("TBout.txt"s
                                                 , "w"s);
    ;
    ++(vlSymsp->__Vcoverage[26]);
}

VL_ATTR_COLD void Vtestbench___024root___eval_final(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_final\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtestbench___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtestbench___024root___eval_phase__stl(Vtestbench___024root* vlSelf);

VL_ATTR_COLD void Vtestbench___024root___eval_settle(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_settle\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtestbench___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 2, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vtestbench___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vtestbench___024root___eval_triggers__stl(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_triggers__stl\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtestbench___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vtestbench___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtestbench___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtestbench___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtestbench___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtestbench___024root___stl_sequent__TOP__0(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___stl_sequent__TOP__0\n"); );
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
    if (((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
         ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__done))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 20, 
                               (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__done);
        vlSelfRef.testbench__DOT____Vtogcov__done = 
            (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
    }
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 28, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
            = vlSelfRef.testbench__DOT__DUT__DOT__state;
    }
    if ((1U & (((IData)(vlSelfRef.testbench__DOT__in) 
                >> 3U) ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3)))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 36, 
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
                        ++(vlSymsp->__Vcoverage[40]);
                    }(), 1U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[41]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[42]);
    } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[43]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
    } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        ++(vlSymsp->__Vcoverage[44]);
        vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
    } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
        vlSelfRef.testbench__DOT__DUT__DOT__next = 
            (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                    ? ([&]() {
                        ++(vlSymsp->__Vcoverage[47]);
                    }(), 1U) : ([&]() {
                        ++(vlSymsp->__Vcoverage[48]);
                    }(), 0U)));
        ++(vlSymsp->__Vcoverage[49]);
    }
    if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
        ++(vlSymsp->__Vcoverage[38]);
    }
    if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                  >> 3U)))) {
        ++(vlSymsp->__Vcoverage[39]);
    }
    if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
        ++(vlSymsp->__Vcoverage[45]);
    }
    if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                  >> 3U)))) {
        ++(vlSymsp->__Vcoverage[46]);
    }
    ++(vlSymsp->__Vcoverage[50]);
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 32, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
            = vlSelfRef.testbench__DOT__DUT__DOT__next;
    }
}

VL_ATTR_COLD void Vtestbench___024root___eval_stl(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_stl\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
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
        if (((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
             ^ (IData)(vlSelfRef.testbench__DOT____Vtogcov__done))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 20, 
                                   (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)), vlSelfRef.testbench__DOT____Vtogcov__done);
            vlSelfRef.testbench__DOT____Vtogcov__done 
                = (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state));
        }
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__state) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state))) {
            VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 28, vlSelfRef.testbench__DOT__DUT__DOT__state, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__state 
                = vlSelfRef.testbench__DOT__DUT__DOT__state;
        }
        if ((1U & (((IData)(vlSelfRef.testbench__DOT__in) 
                    >> 3U) ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__in3)))) {
            VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 36, 
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
                            ++(vlSymsp->__Vcoverage[40]);
                        }(), 1U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[41]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[42]);
        } else if ((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[43]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 2U;
        } else if ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            ++(vlSymsp->__Vcoverage[44]);
            vlSelfRef.testbench__DOT__DUT__DOT__next = 3U;
        } else if ((3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))) {
            vlSelfRef.testbench__DOT__DUT__DOT__next 
                = (3U & ((8U & (IData)(vlSelfRef.testbench__DOT__in))
                          ? ([&]() {
                            ++(vlSymsp->__Vcoverage[47]);
                        }(), 1U) : ([&]() {
                            ++(vlSymsp->__Vcoverage[48]);
                        }(), 0U)));
            ++(vlSymsp->__Vcoverage[49]);
        }
        if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
            ++(vlSymsp->__Vcoverage[38]);
        }
        if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                      >> 3U)))) {
            ++(vlSymsp->__Vcoverage[39]);
        }
        if ((8U & (IData)(vlSelfRef.testbench__DOT__in))) {
            ++(vlSymsp->__Vcoverage[45]);
        }
        if ((1U & (~ ((IData)(vlSelfRef.testbench__DOT__in) 
                      >> 3U)))) {
            ++(vlSymsp->__Vcoverage[46]);
        }
        ++(vlSymsp->__Vcoverage[50]);
        if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
             ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
            VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 32, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
            vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next 
                = vlSelfRef.testbench__DOT__DUT__DOT__next;
        }
    }
}

VL_ATTR_COLD bool Vtestbench___024root___eval_phase__stl(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_phase__stl\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtestbench___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vtestbench___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtestbench___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtestbench___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtestbench___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtestbench___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge testbench.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtestbench___024root___ctor_var_reset(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___ctor_var_reset\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->testbench__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6000971430642848038ull);
    vlSelf->testbench__DOT__in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15811953225661715487ull);
    vlSelf->testbench__DOT__reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7469142288805494519ull);
    vlSelf->testbench__DOT__file = 0;
    vlSelf->testbench__DOT____Vtogcov__clk = 0;
    vlSelf->testbench__DOT____Vtogcov__in = 0;
    vlSelf->testbench__DOT____Vtogcov__reset = 0;
    vlSelf->testbench__DOT____Vtogcov__done = 0;
    vlSelf->testbench__DOT__DUT__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1982745243627793178ull);
    vlSelf->testbench__DOT__DUT__DOT__next = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5395185007444239501ull);
    vlSelf->testbench__DOT__DUT__DOT____Vtogcov__state = 0;
    vlSelf->testbench__DOT__DUT__DOT____Vtogcov__next = 0;
    vlSelf->testbench__DOT__DUT__DOT____Vtogcov__in3 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__testbench__DOT__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}

VL_ATTR_COLD void Vtestbench___024root___configure_coverage(Vtestbench___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___configure_coverage\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 3, 6, ".testbench", "v_toggle/testbench", "clk");
    vlSelf->__vlCoverToggleInsert(0, 7, 1, &(vlSymsp->__Vcoverage[2]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 4, 11, ".testbench", "v_toggle/testbench", "in");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[18]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 5, 6, ".testbench", "v_toggle/testbench", "reset");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[20]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 6, 7, ".testbench", "v_toggle/testbench", "done");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 19, 22, ".testbench", "v_expr/testbench", "(clk==0) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[23]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 19, 22, ".testbench", "v_expr/testbench", "(clk==1) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[24]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 19, 5, ".testbench", "v_line/testbench", "block", "19");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[25]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 17, 1, ".testbench", "v_line/testbench", "block", "17-18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[26]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 22, 1, ".testbench", "v_line/testbench", "block", "22-23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[27]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/driver.v", 26, 1, ".testbench", "v_line/testbench", "block", "26,29-35,38-45,48-52,55-60,63-68,71-76,79-84,87-92,95-100,103-108,110-111");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 2, 8, ".testbench.DUT", "v_toggle/top_module", "clk");
    vlSelf->__vlCoverToggleInsert(0, 7, 1, &(vlSymsp->__Vcoverage[2]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 3, 14, ".testbench.DUT", "v_toggle/top_module", "in");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[18]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 4, 8, ".testbench.DUT", "v_toggle/top_module", "reset");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[20]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 5, 9, ".testbench.DUT", "v_toggle/top_module", "done");
    vlSelf->__vlCoverToggleInsert(0, 1, 1, &(vlSymsp->__Vcoverage[28]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 8, 12, ".testbench.DUT", "v_toggle/top_module", "state");
    vlSelf->__vlCoverToggleInsert(0, 1, 1, &(vlSymsp->__Vcoverage[32]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 9, 12, ".testbench.DUT", "v_toggle/top_module", "next");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[36]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 11, 10, ".testbench.DUT", "v_toggle/top_module", "in3");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[38]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 15, 18, ".testbench.DUT", "v_expr/top_module", "(in3==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[39]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 15, 18, ".testbench.DUT", "v_expr/top_module", "(in3==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[40]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 15, 24, ".testbench.DUT", "v_branch/top_module", "cond_then", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[41]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 15, 25, ".testbench.DUT", "v_branch/top_module", "cond_else", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[42]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 15, 9, ".testbench.DUT", "v_line/top_module", "case", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[43]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 16, 9, ".testbench.DUT", "v_line/top_module", "case", "16");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[44]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 17, 9, ".testbench.DUT", "v_line/top_module", "case", "17");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[45]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 18, 17, ".testbench.DUT", "v_expr/top_module", "(in3==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[46]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 18, 17, ".testbench.DUT", "v_expr/top_module", "(in3==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[47]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 18, 23, ".testbench.DUT", "v_branch/top_module", "cond_then", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[48]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 18, 24, ".testbench.DUT", "v_branch/top_module", "cond_else", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[49]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 18, 8, ".testbench.DUT", "v_line/top_module", "case", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[50]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 13, 5, ".testbench.DUT", "v_line/top_module", "block", "13-14");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[51]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 23, 3, ".testbench.DUT", "v_branch/top_module", "if", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[52]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 23, 4, ".testbench.DUT", "v_branch/top_module", "else", "24");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[53]), first, "/home/zhang/CorrectBench/saves/0316~0322/Main_Results/CorrectBench/NO_20260320_145610/fsm_ps2/5_CGA/iter_0/DUT.v", 22, 5, ".testbench.DUT", "v_line/top_module", "block", "22");
}
