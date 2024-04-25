//
// File: state_derivatives.cpp
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
#include "state_derivatives.h"
#include <cmath>
#include "rtwtypes.h"

// Model step function
void state_derivatives::step()
{
  real_T rtb_MinMax;
  real_T rtb_uT;

  // Outputs for Atomic SubSystem: '<Root>/state_derivatives'
  // DiscreteIntegrator: '<S13>/Integrator' incorporates:
  //   Inport: '<Root>/x_in'

  if (rtDW.Integrator_IC_LOADING != 0) {
    rtDW.Integrator_DSTATE = rtU.x_in;
  }

  if (rtDW.Integrator_PrevResetState != 0) {
    rtDW.Integrator_DSTATE = rtU.x_in;
  }

  // Product: '<S3>/1//T' incorporates:
  //   Constant: '<S9>/Time constant'
  //   DiscreteIntegrator: '<S13>/Integrator'
  //   Gain: '<S9>/Minimum sampling to time constant ratio'
  //   Inport: '<Root>/x_in'
  //   MinMax: '<S9>/MinMax'
  //   Sum: '<S3>/Sum1'

  rtb_uT = 1.0 / std::fmax(10.0 * rtDW.Probe[0], 0.02) * (rtU.x_in -
    rtDW.Integrator_DSTATE);

  // DiscreteIntegrator: '<S8>/Integrator' incorporates:
  //   Inport: '<Root>/q_in'

  if (rtDW.Integrator_IC_LOADING_p != 0) {
    rtDW.Integrator_DSTATE_l = rtU.q_in;
  }

  if (rtDW.Integrator_PrevResetState_i != 0) {
    rtDW.Integrator_DSTATE_l = rtU.q_in;
  }

  // Product: '<S2>/1//T' incorporates:
  //   Constant: '<S4>/Time constant'
  //   DiscreteIntegrator: '<S8>/Integrator'
  //   Gain: '<S4>/Minimum sampling to time constant ratio'
  //   Inport: '<Root>/q_in'
  //   MinMax: '<S4>/MinMax'
  //   Sum: '<S2>/Sum1'

  rtb_MinMax = 1.0 / std::fmax(10.0 * rtDW.Probe_b[0], 0.02) * (rtU.q_in -
    rtDW.Integrator_DSTATE_l);

  // Update for DiscreteIntegrator: '<S13>/Integrator'
  rtDW.Integrator_IC_LOADING = 0U;
  rtDW.Integrator_DSTATE += 0.001 * rtb_uT;
  rtDW.Integrator_PrevResetState = 0;

  // Update for DiscreteIntegrator: '<S8>/Integrator'
  rtDW.Integrator_IC_LOADING_p = 0U;
  rtDW.Integrator_DSTATE_l += 0.001 * rtb_MinMax;
  rtDW.Integrator_PrevResetState_i = 0;

  // End of Outputs for SubSystem: '<Root>/state_derivatives'

  // Outport: '<Root>/x' incorporates:
  //   Inport: '<Root>/x_in'

  rtY.x = rtU.x_in;

  // Outport: '<Root>/x_dot'
  rtY.x_dot = rtb_uT;

  // Outport: '<Root>/q' incorporates:
  //   Inport: '<Root>/q_in'

  rtY.q = rtU.q_in;

  // Outport: '<Root>/q_dot'
  rtY.q_dot = rtb_MinMax;
}

// Model initialize function
void state_derivatives::initialize()
{
  // SystemInitialize for Atomic SubSystem: '<Root>/state_derivatives'
  // Start for Probe: '<S9>/Probe'
  rtDW.Probe[0] = 0.001;
  rtDW.Probe[1] = 0.0;

  // Start for Probe: '<S4>/Probe'
  rtDW.Probe_b[0] = 0.001;
  rtDW.Probe_b[1] = 0.0;

  // InitializeConditions for DiscreteIntegrator: '<S13>/Integrator'
  rtDW.Integrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S8>/Integrator'
  rtDW.Integrator_IC_LOADING_p = 1U;

  // End of SystemInitialize for SubSystem: '<Root>/state_derivatives'
}

// Constructor
state_derivatives::state_derivatives():
  rtU(),
  rtY(),
  rtDW()
{
  // Currently there is no constructor body generated.
}

// Destructor
state_derivatives::~state_derivatives()
{
  // Currently there is no destructor body generated.
}

//
// File trailer for generated code.
//
// [EOF]
//
