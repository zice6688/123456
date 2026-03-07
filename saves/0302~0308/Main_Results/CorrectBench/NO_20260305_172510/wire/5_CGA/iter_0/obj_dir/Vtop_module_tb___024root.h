// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop_module_tb.h for the primary calling header

#ifndef VERILATED_VTOP_MODULE_TB___024ROOT_H_
#define VERILATED_VTOP_MODULE_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"


class Vtop_module_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop_module_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ top_module_tb__DOT__in;
    CData/*0:0*/ top_module_tb__DOT__clk;
    CData/*0:0*/ top_module_tb__DOT____Vtogcov__in;
    CData/*0:0*/ top_module_tb__DOT____Vtogcov__clk;
    CData/*0:0*/ __VstlFirstIteration;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDelayScheduler __VdlySched;

    // INTERNAL VARIABLES
    Vtop_module_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtop_module_tb___024root(Vtop_module_tb__Syms* symsp, const char* namep);
    ~Vtop_module_tb___024root();
    VL_UNCOPYABLE(Vtop_module_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
