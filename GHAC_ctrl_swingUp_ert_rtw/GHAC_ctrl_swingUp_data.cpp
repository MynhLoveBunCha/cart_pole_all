//
// File: GHAC_ctrl_swingUp_data.cpp
//
// Code generated for Simulink model 'GHAC_ctrl_swingUp'.
//
// Model version                  : 1.7
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 17:10:01 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "GHAC_ctrl_swingUp.h"

// Constant parameters (default storage)
const GHAC_ctrl_swingUp::ConstP rtConstP{
  // Expression: u_x_sqm
  //  Referenced by: '<S4>/x lookup'

  { 0.35, 0.455, 0.5, 0.545, 0.65 },

  // Pooled Parameter (Mixed Expressions)
  //  Referenced by:
  //    '<S4>/q lookup'
  //    '<S4>/x lookup'
  //    '<S4>/xd lookup'

  { 0.25, 0.375, 0.5, 0.625, 0.75 },

  // Expression: u_xd_sqm
  //  Referenced by: '<S4>/xd lookup'

  { 0.125, 0.21875, 0.5, 0.78125, 0.875 },

  // Expression: u_q_sqm
  //  Referenced by: '<S4>/q lookup'

  { 0.1375, 0.2371875, 0.5, 0.7628125, 0.8625 },

  // Expression: u_qd_sqm
  //  Referenced by: '<S4>/qd lookup'

  { 0.099999999999999978, 0.17999999999999994, 0.24399999999999994, 0.5, 0.756,
    0.82000000000000006, 0.9 },

  // Expression: qd_sqm
  //  Referenced by: '<S4>/qd lookup'

  { 0.25, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.75 }
};

//
// File trailer for generated code.
//
// [EOF]
//
