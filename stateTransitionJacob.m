function [A, Bmv] = stateTransitionJacob(X, u)
%-----------------READ ONLY----------------------------
m = 0.116527;     % pend mass (kg)
M = 0.28;     % cart mass (kg)
L = 0.3000/2;    % pend's length from rotational hinge to center of gravity (m)
I = (1/3)*m*L^2;   % moment of inertia around center of gravity (kg.m2)
g = 9.80665;     % gravitational accel (m/s2)

kd = 0.000161;   % damping const (N.s/rad)
kdr = 0.000001; 
kt = 150;
Fc = 0.00040;
%-----------------READ ONLY----------------------------

x   = X(1);
x_d = X(2);
q   = X(3);
q_d = X(4);

% TODO: this is the continuous Jacobian (we need to discretize this)
A = [0, 1, 0, 0; 
     0, 0, 0, 0; 
     0, 0, 0, 1; 
     0, 0, (L*g*m*cos(q) + L*m*u*sin(q))/(m*L^2 + I), -(kd + 2*kdr*q_d - Fc*kt*(tanh(kt*q_d)^2 - 1))/(m*L^2 + I)];

Bmv = [0;
       1;
       0;
       -(L*m*cos(q))/(m*L^2 + I)];
end