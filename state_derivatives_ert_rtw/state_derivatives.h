//
// File: state_derivatives.h
//
// Code generated for Simulink model 'state_derivatives'.
//
// Model version                  : 1.14
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Sat Feb  3 17:57:53 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef RTW_HEADER_state_derivatives_h_
#define RTW_HEADER_state_derivatives_h_
#include "rtwtypes.h"

// Class declaration for model state_derivatives
class state_derivatives final
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
    real_T x_dot;                      // '<Root>/x_dot'
    real_T q;                          // '<Root>/q'
    real_T q_dot;                      // '<Root>/q_dot'
  };

  // Copy Constructor
  state_derivatives(state_derivatives const&) = delete;

  // Assignment Operator
  state_derivatives& operator= (state_derivatives const&) & = delete;

  // Move Constructor
  state_derivatives(state_derivatives &&) = delete;

  // Move Assignment Operator
  state_derivatives& operator= (state_derivatives &&) = delete;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  state_derivatives();

  // Destructor
  ~state_derivatives();

  // private data and function members
 private:
  // Block states
  DW rtDW;
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
//  Note that this particular code originates from a subsystem build,
//  and has its own system numbers different from the parent model.
//  Refer to the system hierarchy for this subsystem below, and use the
//  MATLAB hilite_system command to trace the generated code back
//  to the parent model.  For example,
//
//  hilite_system('derivative_test/state_derivatives')    - opens subsystem derivative_test/state_derivatives
//  hilite_system('derivative_test/state_derivatives/Kp') - opens and selects block Kp
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

#endif                                 // RTW_HEADER_state_derivatives_h_

//
// File trailer for generated code.
//
// [EOF]
//
