clear,clc, close all;
addpath(pathdef)

import casadi.*

%% Simulation Params
T = 0.001;          % sampling time
sim_time = 7;    % maximum simulation time (sec)

% initial condition [x; x_d; q; q_d]
x0 = [0; 0; -5/180*pi; 0];   % initial pose

% target condition
xs = [0; 0; 0; 0];   % reference pose

%% HAC params
x_max = 0.43; % m
x_min = -x_max;
xd_max = 2.0; % m/s
xd_min = -xd_max;
q_max = 15/180*pi;  % rad
q_min = -q_max;
qd_max = inf; % rad/s
qd_min = -qd_max;
u_max = 3 * 9.80665;
u_min = -u_max;

alpha = 15/180*pi;
beta = 50/180*pi; % beta > alpha

w_low = 0.25;
w_high = 1;

a_sigmoid_q = 8;
a_sigmoid_q_d = 0.45;

%% HA SQMs values %TODO: decide on which ones are OptVars
n_rules_x = 5; fuzzyDeg_x = 0.5; fuzzyDeg_u_x_s = 0.3;
n_rules_xd = 5; fuzzyDeg_xd = 0.5; fuzzyDeg_u_xd_s = 0.75;
n_rules_q = 5; fuzzyDeg_q = 0.5; fuzzyDeg_u_q_s = 0.725;
n_rules_qd = 7; fuzzyDeg_qd = 0.5; fuzzyDeg_u_qd_s = 0.8; %TODO: increase this to quickly stablize the system
%
x_sqm = zeros(1, n_rules_x);
x_sqm(:, (n_rules_x-1)/2+1) = 0.5;
u_x_sqm = zeros(1, n_rules_x);
u_x_sqm(:, (n_rules_x-1)/2+1) = 0.5;

xd_sqm = zeros(1, n_rules_xd);
xd_sqm(:, (n_rules_xd-1)/2+1) = 0.5;
u_xd_sqm = zeros(1, n_rules_xd);
u_xd_sqm(:, (n_rules_xd-1)/2+1) = 0.5;

q_sqm = zeros(1, n_rules_q);
q_sqm(:, (n_rules_q-1)/2+1) = 0.5;
u_q_sqm = zeros(1, n_rules_q);
u_q_sqm(:, (n_rules_q-1)/2+1) = 0.5;

qd_sqm = zeros(1, n_rules_qd);
qd_sqm(:, (n_rules_qd-1)/2+1) = 0.5;
u_qd_sqm = zeros(1, n_rules_qd);
u_qd_sqm(:, (n_rules_qd-1)/2+1) = 0.5;
%
for k = 1:(n_rules_x-1)/2
    x_sqm(:, k) = 0.5*(1 - fuzzyDeg_x^k);
    x_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_x^k);
    u_x_sqm(:, k) = 0.5*(1 - fuzzyDeg_u_x_s^k);
    u_x_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_u_x_s^k);
end

for k = 1:(n_rules_xd-1)/2
    xd_sqm(:, k) = 0.5*(1 - fuzzyDeg_xd^k);
    xd_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_xd^k);
    u_xd_sqm(:, k) = 0.5*(1 - fuzzyDeg_u_xd_s^k);
    u_xd_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_u_xd_s^k);
end

for k = 1:(n_rules_q-1)/2
    q_sqm(:, k) = 0.5*(1 - fuzzyDeg_q^k);
    q_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_q^k);
    u_q_sqm(:, k) = 0.5*(1 - fuzzyDeg_u_q_s^k);
    u_q_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_u_q_s^k);
end

for k = 1:(n_rules_qd-1)/2
    qd_sqm(:, k) = 0.5*(1 - fuzzyDeg_qd^k);
    qd_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_qd^k);
    u_qd_sqm(:, k) = 0.5*(1 - fuzzyDeg_u_qd_s^k);
    u_qd_sqm(:, end + 1 - k) = 0.5*(1 + fuzzyDeg_u_qd_s^k);
end

%% params for HAC function
% constant params
params = struct();
params.alpha = alpha;
params.beta = beta;
params.w_low = w_low;
params.w_high = w_high;
params.X_min = [x_min, xd_min, q_min, qd_min];
params.X_max = [x_max, xd_max, q_max, qd_max];
params.u_min = u_min;
params.u_max = u_max;

% changeable params
params.a_sigmoid_q = a_sigmoid_q;
params.a_sigmoid_q_d = a_sigmoid_q_d;

params.x_sqm = x_sqm;
params.xd_sqm = xd_sqm;
params.q_sqm = q_sqm;
params.qd_sqm = qd_sqm;

params.u_x_sqm = u_x_sqm;
params.u_xd_sqm = u_xd_sqm;
params.u_q_sqm = u_q_sqm;
params.u_qd_sqm = u_qd_sqm;

%% state space representation

% states
x = SX.sym('x');
x_d = SX.sym('x_d');
q = SX.sym('q');
q_d = SX.sym('q_d');
states = [x; x_d; q; q_d];
n_states = length(states);

% controls
u = SX.sym('u');
controls = u;
n_controls = length(controls);

% continuous state space sys
X_dot = continuous_cartpend(states, u);
f_continuous = Function('f_continuous', {states, controls}, {X_dot}, ...
    {'states', 'controls'}, {'X_dot'}); % function to compute state derivative

%% Simulation loop
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------

t0 = 0;

xx(:, 1) = x0;                 % keep history of states during the whole simulation
u0 = 0;     % control inputs
t(1) = t0;                     % keep history of time

% start MPC
mpcIter = 0;
u_cl = []; % to store predicted controls we take (the first one in the all optimal controls)

main_loop = tic;
while((norm((x0 - xs), 2) > 1e-6) && ((mpcIter * T) < sim_time)) % terminate when the system is within 1 cm of the destination or sim time is over

    u0 = my_HAC_improved(x0, params);
    u_cl = [u_cl; u0]; % store only the first control

    t(mpcIter + 1) = t0;
    
    % [t0, x0, u0] = shift(T, t0, x0, u + randn()/10, f_continuous); % apply only the first control
    % [t0, x0, u0] = shift(T, t0, x0, u, f_continuous); % apply only the first control
    st = x0;
    con = u0;
    N = 1;
    
    for i = 1:N
        st = full(RK4(st,con,f_continuous,T/N));
    end
    
    t0 = t0 + T;
    x0 = st;

    xx(:, mpcIter + 2) = x0;

    mpcIter = mpcIter + 1;
end
main_loop_time = toc(main_loop);
disp(main_loop_time/mpcIter);
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------

%% ANIMATION
% Physical Parameters  (big mass and inertia for "slow" physics)
p.m1 = 0.28;  % (kg) Cart mass
p.m2 = 0.116527;  % (kg) pole mass
p.g = 9.80665;  % (m/s^2) gravity
p.l = 0.3000;   % (m) pendulum (pole) length

% Convert states to cartesian positions:
pos = cartPolePosition(xx,p);
x1 = pos(1,:);
y1 = pos(2,:);
x2 = pos(3,:);
y2 = pos(4,:);

% Plotting parameters:
p.w = 0.4*p.l;  %Width of the cart
p.h = 0.2*p.l;  %Height of the cart
p.r = 0*p.l;  % Radius of the pendulum bob

% Compute the extents of the drawing, keeping everything in view
padding = 0.2*p.l;  %Free space around edges
xLow = -0.55;
xUpp = 0.55;
yLow = -0.35;
yUpp = 0.35;
extents = [xLow,xUpp,yLow,yUpp];

% Create and clear a figure:
figure(1); clf;
hold on;    %  <-- This is important!
set(gcf,'DoubleBuffer','on');   % Prevents flickering (maybe??)
scaleCoeff = 1.5;
fig = gcf;
fig.Position(1) = fig.Position(1) / scaleCoeff;
fig.Position(2) = fig.Position(2) / scaleCoeff;
fig.Position(3) = scaleCoeff * fig.Position(3);
fig.Position(4) = scaleCoeff * fig.Position(4);

time = 0;
pos = pos(:, 1:end-1);
plotHandles = struct;
plotHandles.railHandle = [];
plotHandles.cartHandle = [];
plotHandles.poleHandle = [];

frameLst = [];
timeLst = [];
saveGIF = false;

tic;
while time < t(end)
    
    % Compute the position of the system at the current real world time
    posDraw = interp1(t',pos',time')';
    
    % Redraw the image
    plotHandles = drawCartPole(time, posDraw, extents, p, plotHandles);

    % create video
    frame = getframe(fig);
    frameLst = [frameLst; frame];
    timeLst = [timeLst; time];

    % Update current time
    time = toc;
end
timeLst = [timeLst; time];

if saveGIF
    filename = "HAC_cartPend_casadi.gif"; % Specify the output file name
    for idx = 1:size(frameLst)
        [A,map] = rgb2ind(frame2im(frameLst(idx,:)),256);
        if idx == 1
            imwrite(A,map,filename,"gif","LoopCount",Inf,"DelayTime",timeLst(idx+1,:)-timeLst(idx,:));
        else
            imwrite(A,map,filename,"gif","WriteMode","append","DelayTime",timeLst(idx+1,:)-timeLst(idx,:));
        end
    end
end


clf;
tiledlayout(4, 2, "TileIndexing","rowmajor");
nexttile;
plot(t, xx(1,1:end-1), "LineWidth", 1, "Color", [0 0 0]);
title('Cart position');
xlabel("time (s)");
ylabel("(m)");
grid on;

nexttile;
plot(t, xx(2,1:end-1), "LineWidth", 1, "Color", [0 0 0]);
title('Cart velocity');
xlabel("time (s)");
ylabel("(m/s)");
grid on;

nexttile;
plot(t, rad2deg(xx(3,1:end-1)), "LineWidth", 1, "Color", [0 0 0]);
title('Pendulum angle');
xlabel("time (s)");
ylabel("(deg)");
grid on;

nexttile;
plot(t, rad2deg(xx(4,1:end-1)), "LineWidth", 1, "Color", [0 0 0]);
title('Pendulum angular velocity');
xlabel("time (s)");
ylabel("(deg/s)");
grid on;

nexttile;
plot(t, u_cl, "LineWidth", 1, "Color", [0 0 0]);
title('Input');
xlabel("time (s)");
ylabel("(m/s2)");
grid on;

% TODO: sampling time of HAC must be fast enough to maintain numerical
% stability