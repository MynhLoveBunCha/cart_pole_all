//
// File: MPC_controller_data.cpp
//
// Code generated for Simulink model 'MPC_controller'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Fri Mar  1 15:04:28 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "MPC_controller.h"

// Constant parameters (default storage)
const MPC_controller::ConstP rtConstP{
  // Expression: min(3,PredictionHorizon+1):(PredictionHorizon+1)
  //  Referenced by: '<S3>/Constant'

  { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0 },

  // Expression: 2:max(2,PredictionHorizon)
  //  Referenced by: '<S3>/Constant1'

  { 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 }
};

//
// File trailer for generated code.
//
// [EOF]
//
