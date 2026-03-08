// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtestbench.h for the primary calling header

#include "Vtestbench__pch.h"

VL_ATTR_COLD void Vtestbench___024root___eval_static(Vtestbench___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root___eval_static\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__testbench__DOT__areset__0 
        = vlSelfRef.testbench__DOT__areset;
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
    ++(vlSymsp->__Vcoverage[24]);
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
            VL_FATAL_MT("/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 1, "", "Settle region did not converge after 100 tries");
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
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter))) {
        VL_COV_TOGGLE_CHG_ST_I(5, vlSymsp->__Vcoverage + 49, vlSelfRef.testbench__DOT__DUT__DOT__fall_counter, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter);
        vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__fall_counter 
            = vlSelfRef.testbench__DOT__DUT__DOT__fall_counter;
    }
    vlSelfRef.testbench__DOT__aaah = ((2U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
                                      | (3U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
    vlSelfRef.testbench__DOT__digging = ((4U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)) 
                                         | (5U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state)));
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
    if (((IData)(vlSelfRef.testbench__DOT__DUT__DOT__next) 
         ^ (IData)(vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 43, vlSelfRef.testbench__DOT__DUT__DOT__next, vlSelfRef.testbench__DOT__DUT__DOT____Vtogcov__next);
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
        Vtestbench___024root___stl_sequent__TOP__0(vlSelf);
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
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge testbench.areset)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge testbench.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
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
    vlSelf->testbench__DOT__areset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2645019655275921768ull);
    vlSelf->testbench__DOT__bump_left = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4793007128555379957ull);
    vlSelf->testbench__DOT__bump_right = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16473995248314993705ull);
    vlSelf->testbench__DOT__ground = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17287223969388921196ull);
    vlSelf->testbench__DOT__dig = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8245410645329477109ull);
    vlSelf->testbench__DOT__aaah = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17782440349791787156ull);
    vlSelf->testbench__DOT__digging = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 802399176527442066ull);
    vlSelf->testbench__DOT__file = 0;
    vlSelf->testbench__DOT____Vtogcov__clk = 0;
    vlSelf->testbench__DOT____Vtogcov__areset = 0;
    vlSelf->testbench__DOT____Vtogcov__bump_left = 0;
    vlSelf->testbench__DOT____Vtogcov__bump_right = 0;
    vlSelf->testbench__DOT____Vtogcov__ground = 0;
    vlSelf->testbench__DOT____Vtogcov__dig = 0;
    vlSelf->testbench__DOT____Vtogcov__walk_left = 0;
    vlSelf->testbench__DOT____Vtogcov__walk_right = 0;
    vlSelf->testbench__DOT____Vtogcov__aaah = 0;
    vlSelf->testbench__DOT____Vtogcov__digging = 0;
    vlSelf->testbench__DOT__DUT__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 1982745243627793178ull);
    vlSelf->testbench__DOT__DUT__DOT__next = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5395185007444239501ull);
    vlSelf->testbench__DOT__DUT__DOT__fall_counter = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7808806420138621459ull);
    vlSelf->testbench__DOT__DUT__DOT____Vtogcov__state = 0;
    vlSelf->testbench__DOT__DUT__DOT____Vtogcov__next = 0;
    vlSelf->testbench__DOT__DUT__DOT____Vtogcov__fall_counter = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__testbench__DOT__areset__0 = 0;
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
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 2, 6, ".testbench", "v_toggle/testbench", "clk");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[2]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 3, 6, ".testbench", "v_toggle/testbench", "areset");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[4]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 4, 6, ".testbench", "v_toggle/testbench", "bump_left");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[6]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 5, 6, ".testbench", "v_toggle/testbench", "bump_right");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[8]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 6, 6, ".testbench", "v_toggle/testbench", "ground");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[10]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 7, 6, ".testbench", "v_toggle/testbench", "dig");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[12]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 8, 7, ".testbench", "v_toggle/testbench", "walk_left");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[14]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 9, 7, ".testbench", "v_toggle/testbench", "walk_right");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[16]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 10, 7, ".testbench", "v_toggle/testbench", "aaah");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[18]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 11, 7, ".testbench", "v_toggle/testbench", "digging");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 30, 22, ".testbench", "v_expr/testbench", "(clk==0) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 30, 22, ".testbench", "v_expr/testbench", "(clk==1) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 30, 5, ".testbench", "v_line/testbench", "block", "30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[23]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 28, 1, ".testbench", "v_line/testbench", "block", "28-29");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[24]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 33, 1, ".testbench", "v_line/testbench", "block", "33-34");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[25]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 82, 5, ".testbench", "v_line/testbench", "block", "82-83");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[26]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 94, 5, ".testbench", "v_line/testbench", "block", "94-95");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[27]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 99, 5, ".testbench", "v_line/testbench", "block", "99-100");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[28]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 111, 5, ".testbench", "v_line/testbench", "block", "111-112");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[29]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 133, 5, ".testbench", "v_line/testbench", "block", "133-134");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[30]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 150, 5, ".testbench", "v_line/testbench", "block", "150-151");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[31]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 155, 5, ".testbench", "v_line/testbench", "block", "155-156");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[32]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 170, 5, ".testbench", "v_line/testbench", "block", "170");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[33]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 173, 5, ".testbench", "v_line/testbench", "block", "173");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[34]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 181, 5, ".testbench", "v_line/testbench", "block", "181");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[35]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 188, 5, ".testbench", "v_line/testbench", "block", "188");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[36]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/driver.v", 37, 1, ".testbench", "v_line/testbench", "block", "37,39-46,49-56,59-66,69-76,79-82,85-88,91-94,97-99,102-105,108-111,114-117,120-127,130-133,136-144,147-150,153-155,158-161,163,165-166,169-171,173,176,179,181,183-184,188,190,194-195");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 2, 8, ".testbench.DUT", "v_toggle/top_module", "clk");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[2]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 3, 8, ".testbench.DUT", "v_toggle/top_module", "areset");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[4]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 4, 8, ".testbench.DUT", "v_toggle/top_module", "bump_left");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[6]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 5, 8, ".testbench.DUT", "v_toggle/top_module", "bump_right");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[8]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 6, 8, ".testbench.DUT", "v_toggle/top_module", "ground");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[10]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 7, 8, ".testbench.DUT", "v_toggle/top_module", "dig");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[12]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 8, 9, ".testbench.DUT", "v_toggle/top_module", "walk_left");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[14]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 9, 9, ".testbench.DUT", "v_toggle/top_module", "walk_right");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[16]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 10, 9, ".testbench.DUT", "v_toggle/top_module", "aaah");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[18]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 11, 9, ".testbench.DUT", "v_toggle/top_module", "digging");
    vlSelf->__vlCoverToggleInsert(0, 2, 1, &(vlSymsp->__Vcoverage[37]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 14, 12, ".testbench.DUT", "v_toggle/top_module", "state");
    vlSelf->__vlCoverToggleInsert(0, 2, 1, &(vlSymsp->__Vcoverage[43]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 15, 12, ".testbench.DUT", "v_toggle/top_module", "next");
    vlSelf->__vlCoverToggleInsert(0, 4, 1, &(vlSymsp->__Vcoverage[49]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 17, 15, ".testbench.DUT", "v_toggle/top_module", "fall_counter");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[59]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 23, 10, ".testbench.DUT", "v_line/top_module", "if", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[60]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 23, 11, ".testbench.DUT", "v_line/top_module", "else", "24");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[61]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 22, 10, ".testbench.DUT", "v_line/top_module", "elsif", "22");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[62]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 21, 8, ".testbench.DUT", "v_line/top_module", "elsif", "21");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[63]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 21, 12, ".testbench.DUT", "v_expr/top_module", "(ground==0) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[64]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 21, 12, ".testbench.DUT", "v_expr/top_module", "(ground==1) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[65]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 21, 6, ".testbench.DUT", "v_line/top_module", "case", "21");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[66]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 28, 10, ".testbench.DUT", "v_line/top_module", "if", "28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[67]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 28, 11, ".testbench.DUT", "v_line/top_module", "else", "29");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[68]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 27, 10, ".testbench.DUT", "v_line/top_module", "elsif", "27");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[69]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 26, 5, ".testbench.DUT", "v_line/top_module", "elsif", "26");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[70]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 26, 9, ".testbench.DUT", "v_expr/top_module", "(ground==0) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[71]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 26, 9, ".testbench.DUT", "v_expr/top_module", "(ground==1) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[72]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 25, 6, ".testbench.DUT", "v_line/top_module", "case", "25");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[73]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 30, 18, ".testbench.DUT", "v_expr/top_module", "(ground==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[74]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 30, 18, ".testbench.DUT", "v_expr/top_module", "(ground==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[75]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 30, 49, ".testbench.DUT", "v_branch/top_module", "cond_then", "30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[76]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 30, 50, ".testbench.DUT", "v_branch/top_module", "cond_else", "30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[77]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 30, 47, ".testbench.DUT", "v_branch/top_module", "cond_then", "30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[78]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 30, 48, ".testbench.DUT", "v_branch/top_module", "cond_else", "30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[79]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 30, 9, ".testbench.DUT", "v_line/top_module", "case", "30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[80]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 31, 18, ".testbench.DUT", "v_expr/top_module", "(ground==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[81]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 31, 18, ".testbench.DUT", "v_expr/top_module", "(ground==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[82]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 31, 49, ".testbench.DUT", "v_branch/top_module", "cond_then", "31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[83]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 31, 50, ".testbench.DUT", "v_branch/top_module", "cond_else", "31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[84]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 31, 47, ".testbench.DUT", "v_branch/top_module", "cond_then", "31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[85]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 31, 48, ".testbench.DUT", "v_branch/top_module", "cond_else", "31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[86]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 31, 9, ".testbench.DUT", "v_line/top_module", "case", "31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[87]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 32, 17, ".testbench.DUT", "v_expr/top_module", "(ground==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[88]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 32, 17, ".testbench.DUT", "v_expr/top_module", "(ground==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[89]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 32, 26, ".testbench.DUT", "v_branch/top_module", "cond_then", "32");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[90]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 32, 27, ".testbench.DUT", "v_branch/top_module", "cond_else", "32");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[91]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 32, 8, ".testbench.DUT", "v_line/top_module", "case", "32");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[92]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 33, 17, ".testbench.DUT", "v_expr/top_module", "(ground==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[93]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 33, 17, ".testbench.DUT", "v_expr/top_module", "(ground==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[94]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 33, 26, ".testbench.DUT", "v_branch/top_module", "cond_then", "33");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[95]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 33, 27, ".testbench.DUT", "v_branch/top_module", "cond_else", "33");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[96]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 33, 8, ".testbench.DUT", "v_line/top_module", "case", "33");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[97]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 34, 8, ".testbench.DUT", "v_line/top_module", "case", "34");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[98]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 19, 5, ".testbench.DUT", "v_line/top_module", "block", "19-20");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[99]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 39, 3, ".testbench.DUT", "v_branch/top_module", "if", "39");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[100]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 39, 4, ".testbench.DUT", "v_branch/top_module", "else", "40");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[101]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 38, 5, ".testbench.DUT", "v_line/top_module", "block", "38");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[102]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 45, 4, ".testbench.DUT", "v_branch/top_module", "if", "45-46");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[103]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 45, 5, ".testbench.DUT", "v_branch/top_module", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[104]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 44, 3, ".testbench.DUT", "v_branch/top_module", "if", "44");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[105]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 44, 4, ".testbench.DUT", "v_branch/top_module", "else", "49");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[106]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 44, 22, ".testbench.DUT", "v_expr/top_module", "((state == FALLR)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[107]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 44, 22, ".testbench.DUT", "v_expr/top_module", "((state == FALLL)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[108]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 44, 22, ".testbench.DUT", "v_expr/top_module", "((state == FALLL)==0 && (state == FALLR)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[109]), first, "/home/zhang/CorrectBench/saves/0302~0308/Main_Results/CorrectBench/NO_20260307_152424/lemmings4/5_CGA/iter_1/DUT.v", 43, 2, ".testbench.DUT", "v_line/top_module", "block", "43");
}
