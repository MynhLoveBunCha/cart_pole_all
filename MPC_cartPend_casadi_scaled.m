clear,clc, close all;
addpath(pathdef)

import casadi.*

% Params
T = 0.1;          % sampling time
N = 10;           % prediction horizon
sim_time = 5;    % maximum simulation time (sec)

% states limit
x_max = 0.43; % m
x_min = -x_max;
xd_max = 2.0; % m/s
xd_min = -xd_max;
q_max = 2*pi;  % rad
q_min = -q_max;
qd_max = 13; % rad/s
qd_min = -qd_max;
u_max = 3 * 9.81;
u_min = -u_max;

X_max = [x_max; xd_max; q_max; qd_max];
X_min = [x_min; xd_min; q_min; qd_min];
% cost function penalties
Q = diag([15, 0, 5, 0]);   % states penalty
R = 0.1;     % controls penalty

% initial condition [x; x_d; q; q_d]
x0 = [0; 0; 180/180*pi; 0];   % initial pose
disp(x0);

% target condition
xs = [0; 0; 0; 0];   % reference pose

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

% optimization problem setup
U = SX.sym('U', n_controls, N);   % decision variable (controls)
P = SX.sym('P', n_states*2);      % hold initial states and reference states
X = SX.sym('X', n_states, (N+1)); % rollouts of states during prediction horizon

% calculate objective function and dynamics constraints
obj = 0;              % objective function
g = [];               % constraints vector

st = X(:, 1); % initial states
g = [g; st - P(1:n_states)]; % initial condition constraint

for k = 1:N 
    st = X(:,k); % current state
    con = U(:,k); % current control
    obj = obj + (st-P(n_states+1:end))'*Q*(st-P(n_states+1:end)) + con'*R*con; % calculate objective function
    st_next = X(:, k+1); % next states to optimized
    st_next_RK4 = RK4(st, con, f_continuous, T);
    g = [g; st_next - st_next_RK4]; % dynamics constraints
end

% define solver
optVar = [reshape(X, n_states*(N+1), 1); ...
          reshape(U, n_controls*N, 1)]; % both X and U are optimization variable

% define nonlinear programming problem
nlpProb = struct();
nlpProb.f = obj;
nlpProb.x = optVar;
nlpProb.g = g;
nlpProb.p = P;

% define solver options
opts.ipopt.max_iter = 100;
opts.ipopt.print_level = 0; % 0 -> 3
opts.ipopt.acceptable_tol = 1e-8;
opts.ipopt.acceptable_obj_change_tol = 1e-6;

% define plugin options
opts.print_time = 0; % 0, 1

% define solver
solver = nlpsol('solver', 'ipopt', nlpProb, opts);

% define constraints
args = struct;

args.lbg(1:n_states*(N+1)) = 0; % dynamics contraints (equality constraints)
args.ubg(1:n_states*(N+1)) = 0;

args.lbx(1:n_states:n_states*(N+1), 1) = x_min;            % state x lower bound
args.lbx(2:n_states:n_states*(N+1), 1) = xd_min;            % state x_d lower bound
args.lbx(3:n_states:n_states*(N+1), 1) = q_min;          % state q lower bound
args.lbx(4:n_states:n_states*(N+1), 1) = qd_min;          % state q_d lower bound

args.ubx(1:n_states:n_states*(N+1), 1) = x_max;             % state x upper bound
args.ubx(2:n_states:n_states*(N+1), 1) = xd_max;             % state x_d upper bound
args.ubx(3:n_states:n_states*(N+1), 1) = q_max;           % state q upper bound
args.ubx(4:n_states:n_states*(N+1), 1) = qd_max;           % state q_d upper bound

args.lbx(n_states*(N+1)+1:(n_states*(N+1)+n_controls*N), 1) = u_min;     % lower bound for u
args.ubx(n_states*(N+1)+1:(n_states*(N+1)+n_controls*N), 1) = u_max;     % upper bound for u

% Simulation loop
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------

t0 = 0;

xx(:, 1) = x0;                 % keep history of states during the whole simulation
u0 = zeros(N, n_controls);     % two control inputs
X0 = repmat(x0, 1, N+1);       % init states variables along first prediction window
t(1) = t0;                     % keep history of time

% start MPC
mpcIter = 0;
xx1 = []; % to store predicted states
u_cl = []; % to store predicted controls we take (the first one in the all optimal controls)

main_loop = tic;
while((norm((x0 - xs), 2) > 1e-6) && ((mpcIter * T) < sim_time)) % terminate when the robot is within 1 cm of the destination or sim time is over
    args.p = [x0; xs]; % params containing init state and ref state
    args.x0 = [reshape(X0', n_states*(N+1), 1); ...
               reshape(u0, n_controls*N, 1)]; % initial value of the optimization variables
    
    % solution consists of both optimal control (u_opt) and optimal trajectory (X_opt)
    sol = solver('x0', args.x0, 'lbx', args.lbx, 'ubx', args.ubx, ...
        'lbg', args.lbg, 'ubg', args.ubg, 'p', args.p);

    % get only opt control from the solution
    u = reshape(full(sol.x(n_states*(N+1)+1:end))', n_controls, N)';

    % get only opt traj from the solution
    xx1(:, 1:n_states, mpcIter + 1) = reshape(full(sol.x(1:n_states*(N+1)))', n_states, N+1)';

    u_cl = [u_cl; u(1, :)]; % store only the first control

    t(mpcIter + 1) = t0;

    [t0, x0, u0] = shift(T, t0, x0, u + randn()/10, f_continuous); % apply only the first control
    % [t0, x0, u0] = shift(T, t0, x0, u, f_continuous); % apply only the first control
    
    xx(:, mpcIter + 2) = x0;

    X0 = reshape(full(sol.x(1:n_states*(N+1)))', n_states, N+1)';
    X0 = [X0(2:end,:);X0(end,:)];

    mpcIter = mpcIter + 1;
end
main_loop_time = toc(main_loop);
disp(main_loop_time/mpcIter);
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------
% ------------------------------------------------------------------------------------

%%% ANIMATION
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
    filename = "MPC_cartPend_casadi.gif"; % Specify the output file name
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

%%%% function

function X_scaled = scale_state(X, X_max, X_min)
    denominator = X_max - X_min;
    X_scaled = (X - X_min)./denominator;
end

function X_unscaled = unscale_state(X_scaled, X_max, X_min)
    denominator = X_max - X_min;
    X_unscaled = X_scaled.*denominator + X_min;
end