clear,clc;

m = 0.116527;     % pend mass (kg)
M = 0.28;     % cart mass (kg)
L = 0.2908/2;    % pend's length from rotational hinge to center of gravity (m)
I = (1/3)*m*L^2;   % moment of inertia around center of gravity (kg.m2)
g = 9.80665;     % gravitational accel (m/s2)

uMax = 20;    % maximum input (m/s2)
x1_max = 0.43;% track limit (m)
x3_max = 1.8; % cart vel max (m/s)

kd = 0.00016;   % damping const (N.s/rad)
kdr = 0.00001; 
kt = 100;
Fc = 0.00046;
%% LQR design
k_lqr = discrete_lqr(m, M, L, I, g, kd);

%% load sys
open_system("real_sys_controller");