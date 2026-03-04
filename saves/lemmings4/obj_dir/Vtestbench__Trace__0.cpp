// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vtestbench__Syms.h"


void Vtestbench___024root__trace_chg_0_sub_0(Vtestbench___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtestbench___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root__trace_chg_0\n"); );
    // Body
    Vtestbench___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtestbench___024root*>(voidSelf);
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtestbench___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtestbench___024root__trace_chg_0_sub_0(Vtestbench___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root__trace_chg_0_sub_0\n"); );
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity
                      [2U])))) {
        bufp->chgBit(oldp+0,(vlSelfRef.testbench__DOT__areset));
        bufp->chgBit(oldp+1,(vlSelfRef.testbench__DOT__bump_left));
        bufp->chgBit(oldp+2,(vlSelfRef.testbench__DOT__bump_right));
        bufp->chgBit(oldp+3,(vlSelfRef.testbench__DOT__ground));
        bufp->chgBit(oldp+4,(vlSelfRef.testbench__DOT__dig));
        bufp->chgIData(oldp+5,(vlSelfRef.testbench__DOT__scenario),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgBit(oldp+6,((0U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))));
        bufp->chgBit(oldp+7,((1U == (IData)(vlSelfRef.testbench__DOT__DUT__DOT__state))));
        bufp->chgBit(oldp+8,(vlSelfRef.testbench__DOT__DUT__DOT__aaah));
        bufp->chgBit(oldp+9,(vlSelfRef.testbench__DOT__DUT__DOT__digging));
        bufp->chgCData(oldp+10,(vlSelfRef.testbench__DOT__DUT__DOT__state),3);
    }
    bufp->chgBit(oldp+11,(vlSelfRef.testbench__DOT__clk));
    bufp->chgIData(oldp+12,(vlSelfRef.testbench__DOT__file),32);
    bufp->chgCData(oldp+13,(vlSelfRef.testbench__DOT__DUT__DOT__next),3);
    bufp->chgCData(oldp+14,(vlSelfRef.testbench__DOT__DUT__DOT__fall_counter),5);
}

void Vtestbench___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtestbench___024root__trace_cleanup\n"); );
    // Body
    Vtestbench___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtestbench___024root*>(voidSelf);
    Vtestbench__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
