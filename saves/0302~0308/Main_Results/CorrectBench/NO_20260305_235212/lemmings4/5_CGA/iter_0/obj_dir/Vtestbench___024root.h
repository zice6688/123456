// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtestbench.h for the primary calling header

#ifndef VERILATED_VTESTBENCH___024ROOT_H_
#define VERILATED_VTESTBENCH___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"


class Vtestbench__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtestbench___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ testbench__DOT__clk;
    CData/*0:0*/ testbench__DOT__areset;
    CData/*0:0*/ testbench__DOT__bump_left;
    CData/*0:0*/ testbench__DOT__bump_right;
    CData/*0:0*/ testbench__DOT__ground;
    CData/*0:0*/ testbench__DOT__dig;
    CData/*0:0*/ testbench__DOT__aaah;
    CData/*0:0*/ testbench__DOT__digging;
    CData/*0:0*/ testbench__DOT____Vtogcov__clk;
    CData/*0:0*/ testbench__DOT____Vtogcov__areset;
    CData/*0:0*/ testbench__DOT____Vtogcov__bump_left;
    CData/*0:0*/ testbench__DOT____Vtogcov__bump_right;
    CData/*0:0*/ testbench__DOT____Vtogcov__ground;
    CData/*0:0*/ testbench__DOT____Vtogcov__dig;
    CData/*0:0*/ testbench__DOT____Vtogcov__walk_left;
    CData/*0:0*/ testbench__DOT____Vtogcov__walk_right;
    CData/*0:0*/ testbench__DOT____Vtogcov__aaah;
    CData/*0:0*/ testbench__DOT____Vtogcov__digging;
    CData/*2:0*/ testbench__DOT__DUT__DOT__state;
    CData/*2:0*/ testbench__DOT__DUT__DOT__next;
    CData/*4:0*/ testbench__DOT__DUT__DOT__fall_counter;
    CData/*2:0*/ testbench__DOT__DUT__DOT____Vtogcov__state;
    CData/*2:0*/ testbench__DOT__DUT__DOT____Vtogcov__next;
    CData/*4:0*/ testbench__DOT__DUT__DOT____Vtogcov__fall_counter;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__testbench__DOT__areset__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__testbench__DOT__clk__0;
    IData/*31:0*/ testbench__DOT__file;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDelayScheduler __VdlySched;

    // INTERNAL VARIABLES
    Vtestbench__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtestbench___024root(Vtestbench__Syms* symsp, const char* namep);
    ~Vtestbench___024root();
    VL_UNCOPYABLE(Vtestbench___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
