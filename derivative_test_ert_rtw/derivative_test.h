//
// File: derivative_test.h
//
// Code generated for Simulink model 'derivative_test'.
//
// Model version                  : 1.13
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Sat Feb  3 17:56:45 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef RTW_HEADER_derivative_test_h_
#define RTW_HEADER_derivative_test_h_
#include "rtwtypes.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Class declaration for model derivative_test
class derivative_test final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T Probe[2];                   // '<S9>/Probe'
    real_T Probe_b[2];                 // '<S4>/Probe'
    real_T Integrator_DSTATE;          // '<S13>/Integrator'
    real_T Integrator_DSTATE_l;        // '<S8>/Integrator'
    int8_T Integrator_PrevResetState;  // '<S13>/Integrator'
    int8_T Integrator_PrevResetState_i;// '<S8>/Integrator'
    uint8_T Integrator_IC_LOADING;     // '<S13>/Integrator'
    uint8_T Integrator_IC_LOADING_p;   // '<S8>/Integrator'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T x_in;                       // '<Root>/x_in'
    real_T q_in;                       // '<Root>/q_in'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T x;                          // '<Root>/x'
    real_T x_d;                        // '<Root>/x_d'
    real_T q;                          // '<Root>/q'
    real_T q_d;                        // '<Root>/q_d'
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  derivative_test(derivative_test const&) = delete;

  // Assignment Operator
  derivative_test& operator= (derivative_test const&) & = delete;

  // Move Constructor
  derivative_test(derivative_test &&) = delete;

  // Move Assignment Operator
  derivative_test& operator= (derivative_test &&) = delete;

  // Real-Time Model get method
  derivative_test::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  derivative_test();

  // Destructor
  ~derivative_test();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // Real-Time Model
  RT_MODEL rtM;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/Gain' : Eliminated nontunable gain of 1
//  Block '<S8>/Saturation' : Eliminated Saturate block
//  Block '<S2>/[A,B]' : Eliminated Saturate block
//  Block '<S3>/Gain' : Eliminated nontunable gain of 1
//  Block '<S13>/Saturation' : Eliminated Saturate block
//  Block '<S3>/[A,B]' : Eliminated Saturate block


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'derivative_test'
//  '<S1>'   : 'derivative_test/state_derivatives'
//  '<S2>'   : 'derivative_test/state_derivatives/high_pass_filter_q'
//  '<S3>'   : 'derivative_test/state_derivatives/high_pass_filter_x'
//  '<S4>'   : 'derivative_test/state_derivatives/high_pass_filter_q/Enable//disable time constant'
//  '<S5>'   : 'derivative_test/state_derivatives/high_pass_filter_q/Initialization'
//  '<S6>'   : 'derivative_test/state_derivatives/high_pass_filter_q/Integrator (Discrete or Continuous)'
//  '<S7>'   : 'derivative_test/state_derivatives/high_pass_filter_q/Initialization/Init_u'
//  '<S8>'   : 'derivative_test/state_derivatives/high_pass_filter_q/Integrator (Discrete or Continuous)/Discrete'
//  '<S9>'   : 'derivative_test/state_derivatives/high_pass_filter_x/Enable//disable time constant'
//  '<S10>'  : 'derivative_test/state_derivatives/high_pass_filter_x/Initialization'
//  '<S11>'  : 'derivative_test/state_derivatives/high_pass_filter_x/Integrator (Discrete or Continuous)'
//  '<S12>'  : 'derivative_test/state_derivatives/high_pass_filter_x/Initialization/Init_u'
//  '<S13>'  : 'derivative_test/state_derivatives/high_pass_filter_x/Integrator (Discrete or Continuous)/Discrete'

#endif                                 // RTW_HEADER_derivative_test_h_

//
// File trailer for generated code.
//
// [EOF]
//
