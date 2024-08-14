clear,clc;

m = 0.116527;     % pend mass (kg)
M = 0.28;     % cart mass (kg)
L = 0.3000/2;    % pend's length from rotational hinge to center of gravity (m)
I = (1/3)*m*L^2;   % moment of inertia around center of gravity (kg.m2)
g = 9.80665;     % gravitational accel (m/s2)

% swing-up control params (main)
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

% friction
kd = 0.000161;   % damping const (N.s/rad)
kdr = 0.000001; 
kt = 150;
Fc = 0.00040;

%% LQR design
k_lqr = discrete_lqr(m, M, L, I, g, kd, kt, Fc);

%% initial condition
init_angle = 181/180*pi;
%% open sys
mdl = "my_cart_pend.slx";
open_system(mdl);
out = sim(mdl);

%% ANIMATION
% Physical Parameters  (big mass and inertia for "slow" physics)
p.m1 = 0.28;  % (kg) Cart mass
p.m2 = 0.116527;  % (kg) pole mass
p.g = 9.80665;  % (m/s^2) gravity
p.l = 0.3000;   % (m) pendulum (pole) length

% Reshape data
t = out.data_energy_LQR.Time';
data = out.data_energy_LQR.Data;
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
    filename = "LQR_cartPend.gif"; % Specify the output file name
    for idx = 1:size(frameLst)
        [A,map] = rgb2ind(frame2im(frameLst(idx,:)),256);
        if idx == 1
            imwrite(A,map,filename,"gif","LoopCount",Inf,"DelayTime",timeLst(idx+1,:)-timeLst(idx,:));
        else
            imwrite(A,map,filename,"gif","WriteMode","append","DelayTime",timeLst(idx+1,:)-timeLst(idx,:));
        end
    end
end

close Figure 2;