clear,clc,close all;

%% System params
m = 0.116527;     % pend mass (kg)
M = 0.28;     % cart mass (kg)
L = 0.3/2;    % pend's length from rotational hinge to center of gravity (m)
I = (1/3)*m*L^2;   % moment of inertia around center of gravity (kg.m2)
g = 9.80665;     % gravitational accel (m/s2)

% friction
kd = 0.000161;   % damping const (N.s/rad)
kdr = 0.000001; 
kt = 150;
Fc = 0.00040;

%% HAC params
useThayLe = false;
if useThayLe
    x_max = 0.43; % m
    x_min = -x_max;
    xd_max = 2.0; % m/s
    xd_min = -xd_max;
    q_max = 10/180*pi;  % rad
    q_min = -q_max;
    qd_max = 4; % rad/s
    qd_min = -qd_max;
    u_max = 3 * g;
    u_min = -u_max;
    
else
    x_max = 0.43; % m
    x_min = -x_max;
    xd_max = 2.0; % m/s
    xd_min = -xd_max;

    q_max = 15/180*pi;  % rad
    q_min = -q_max;
    qd_max = 5; % rad/s
    qd_min = -qd_max;

    u_max = 3 * g;
    u_min = -u_max;
end

%thay Le ---------------------
n_rules = 5;
theta = 0.5;
alpha_state = 0.5;
alpha_u = 0.5;

SQMs_state = zeros(1,n_rules);
SQMs_u = zeros(1,n_rules);

SQMs_state(1) = theta*(1-alpha_state);
SQMs_state(2) = theta*(1-alpha_state+alpha_state^2);
SQMs_state(3) = theta;
SQMs_state(4) = theta+alpha_state*(1-theta)*(1-alpha_state);
SQMs_state(5) = theta+alpha_state*(1-theta);

SQMs_u(1) = theta*(1-alpha_u);
SQMs_u(2) = theta*(1-alpha_u+alpha_u^2);
SQMs_u(3) = theta;
SQMs_u(4) = theta+alpha_u*(1-theta)*(1-alpha_u);
SQMs_u(5) = theta+alpha_u*(1-theta);
%thay Le ---------------------

alpha = 15/180*pi;
beta = 50/180*pi; % beta > alpha

w_low = 0.25;
w_high = 1;

a_sigmoid_q = 8;
a_sigmoid_q_d = 0.45;



%% video saver
filename = "RSHAC_cartPend.gif"; % Specify the output file name
saveGIF = false;
%% swing-up control params (main)
k_su = 2;
k_cw = 6;
k_vw = 2.5;
k_em = 10;
eta  = 1.3;
angle_threshold = deg2rad(25);  % degree
uMax = 3*g;    % maximum input (m/s2)
x1_max = 0.43;% track limit (m)
x2_max = 2; % cart vel max (m/s)
E_up = m*g*L*cos(0);

%% HA SQMs values
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

%% initial condition
init_angle = 20/180*pi;

%% open sys
mdl = "cartPend_HAC.slx";
open_system(mdl);
out = sim(mdl);

%% ANIMATION
% Physical Parameters  (big mass and inertia for "slow" physics)
p.m1 = 0.28;  % (kg) Cart mass
p.m2 = 0.116527;  % (kg) pole mass
p.g = 9.80665;  % (m/s^2) gravity
p.l = 0.3000;   % (m) pendulum (pole) length

% Reshape data
t = out.data_HAC.Time';
data = out.data_HAC.Data;
xx = data(:, 1:4)';
u_cl = data(:, 5);

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
figure(2); clf;
hold on;    %  <-- This is important!
set(gcf,'DoubleBuffer','on');   % Prevents flickering (maybe??)
scaleCoeff = 1.5;
fig = gcf;
fig.Position(1) = fig.Position(1) / scaleCoeff;
fig.Position(2) = fig.Position(2) / scaleCoeff;
fig.Position(3) = scaleCoeff * fig.Position(3);
fig.Position(4) = scaleCoeff * fig.Position(4);

time = 0;

plotHandles = struct;
plotHandles.railHandle = [];
plotHandles.cartHandle = [];
plotHandles.poleHandle = [];

frameLst = [];
timeLst = [];


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
    for idx = 1:size(frameLst)
        [A,map] = rgb2ind(frame2im(frameLst(idx,:)),256);
        if idx == 1
            imwrite(A,map,filename,"gif","LoopCount",Inf,"DelayTime",timeLst(idx+1,:)-timeLst(idx,:));
        else
            imwrite(A,map,filename,"gif","WriteMode","append","DelayTime",timeLst(idx+1,:)-timeLst(idx,:));
        end
    end
end

%% plot HA inference for intermediate controllers
clf;

plot(x_sqm, u_x_sqm, "LineWidth", 2, "Marker", "diamond");
hold on

plot(xd_sqm, u_xd_sqm, "LineWidth", 2, "Marker", "o");
hold on

plot(q_sqm, u_q_sqm, "LineWidth", 2, "Marker", "*");
hold on

plot(qd_sqm, u_qd_sqm, "LineWidth", 2, "Marker", "square");
hold off
grid on;
title("SQSM lines", "FontSize", 20);
xlabel("Semantic state", "FontSize", 15);
ylabel("Semantic intermediate input", "FontSize", 15);
legend(["x", "x_d", "q", "qd"], "Location","southeast", "FontSize", 12);