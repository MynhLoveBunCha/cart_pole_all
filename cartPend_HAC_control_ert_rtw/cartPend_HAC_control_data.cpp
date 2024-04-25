//
// File: cartPend_HAC_control_data.cpp
//
// Code generated for Simulink model 'cartPend_HAC_control'.
//
// Model version                  : 1.6
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Mon Feb 26 17:32:52 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "cartPend_HAC_control.h"

// Constant parameters (default storage)
const cartPend_HAC_control::ConstP rtConstP{
  // Expression: interp_y
  //  Referenced by: '<S4>/1-D Lookup Table'

  { 0.0, 0.15, 0.15, 0.25, 0.25, 0.375, 0.375, 0.5, 0.5, 0.5, 0.625, 0.625, 0.75,
    0.75, 0.825, 0.825 },

  // Expression: interp_x
  //  Referenced by: '<S4>/1-D Lookup Table'

  { 0.0, 0.00390625, 0.0078125, 0.01171875, 0.015625, 0.0234375, 0.03125,
    0.03515625, 0.046875, 0.0625, 0.0703125, 0.09375, 0.10546875, 0.140625,
    0.2109375, 0.31640625 },

  // Computed Parameter: uDLookupTable_maxIndex
  //  Referenced by: '<S4>/1-D Lookup Table'

  15U,

  // Computed Parameter: uDLookupTable_dimSizes
  //  Referenced by: '<S4>/1-D Lookup Table'

  1U,

  // Computed Parameter: uDLookupTable_numYWorkElts
  //  Referenced by: '<S4>/1-D Lookup Table'

  { 1U, 0U }
};

//
// File trailer for generated code.
//
// [EOF]
//
