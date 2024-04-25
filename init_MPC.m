clear,clc;

%% cart pend params
%-----------------READ ONLY----------------------------
m = 0.116527;     % pend mass (kg)
M = 0.28;     % cart mass (kg)
L = 0.3000/2;    % pend's length from rotational hinge to center of gravity (m)
I = (1/3)*m*L^2;   % moment of inertia around center of gravity (kg.m2)
g = 9.80665;     % gravitational accel (m/s2)

uMax = 3*g;    % maximum input (m/s2)
x1_max = 0.43;% track limit (m)
x2_max = 2; % cart vel max (m/s)

kd = 0.000161;   % damping const (N.s/rad)
kdr = 0.000001; 
kt = 150;
Fc = 0.00040;

init_angle = -20/180*pi;  % initial condition
%-----------------READ ONLY----------------------------

%% linearized plant about upright position

% x, x_d, q, q_d
A = zeros(4, 4);
B = zeros(4, 1);
C = eye(4, 4);
D = 0;

A(1, 2) = 1;
A(3, 4) = 1;
A(4, 3) = m*g*L/(m*L^2 + I);
A(4, 4) = -(kd)/(m*L^2 + I);

B(2,:) = 1;
B(4,:) = -m*L/(m*L^2 + I);

myCartPend = ss(A,B,C,D);  % continuous plant
plant = setmpcsignals(myCartPend, 'mv', 1, 'mo', [1 2 3 4]);

%% MPC design
Ts = 0.01;
PredHorizon = 50;
CtrlHorizon = 5;

mpcObj = mpc(plant, Ts, PredHorizon, CtrlHorizon);

mpcObj.Weights.OutputVariables = [5 0 5 0];  % x; x_d; q; q_d
mpcObj.Weights.ManipulatedVariablesRate = 1;

mpcObj.MV.Min = -3*g;  % u
mpcObj.MV.Max = 3*g;

mpcObj.OV(1).Min = -0.43;  % x
mpcObj.OV(1).Max = 0.43;

mpcObj.OV(2).Min = -2.0;  % x_d
mpcObj.OV(2).Max = 2.0;

mpcObj.MV.ScaleFactor = 3*g;
mpcObj.OV(1).ScaleFactor = 0.43;
mpcObj.OV(2).ScaleFactor = 2.0;

%% Explicit MPC generation

% range = generateExplicitRange(mpcObj);
% range.State.Min(:) = [-0.43, -2.0, deg2rad(-20), deg2rad(-100), 0, 0, 0];
% range.State.Max(:) = [0.43, 2.0, deg2rad(20), deg2rad(100), 0, 0, 0];
% range.Reference.Min = [-0.43, 0, 0, 0];
% range.Reference.Max = [0.43, 0, 0, 0];
% range.ManipulatedVariable.Min = -3*g;
% range.ManipulatedVariable.Max = 3*g;
% 
% mpcobjExplicit = generateExplicitMPC(mpcObj,range);

%% simulation
mdl = "linear_MPC_sim.slx";
open_system(mdl);
