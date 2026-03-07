// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTOP_MODULE_TB__SYMS_H_
#define VERILATED_VTOP_MODULE_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtop_module_tb.h"

// INCLUDE MODULE CLASSES
#include "Vtop_module_tb___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtop_module_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtop_module_tb* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtop_module_tb___024root       TOP;

    // COVERAGE
    uint32_t __Vcoverage[11];

    // CONSTRUCTORS
    Vtop_module_tb__Syms(VerilatedContext* contextp, const char* namep, Vtop_module_tb* modelp);
    ~Vtop_module_tb__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
