function u = my_HAC_improved(X, params) 

% define switch range for angle (rad)
alpha = params.alpha;
beta = params.beta; % beta > alpha

% dynamics weights params
w_low = params.w_low;
w_high = params.w_high;

% Extract states variables range
X_min = params.X_min;
X_max = params.X_max;

x_min = X_min(1);
xd_min = X_min(2);
q_min = X_min(3);
qd_min = X_min(4);

x_max = X_max(1);
xd_max = X_max(2);
q_max = X_max(3);
qd_max = X_max(4);

u_min = params.u_min;
u_max = params.u_max;

% Extract states variables
x = X(1);
x_dot = X(2);
q = X(3);
q_dot = X(4);

% Normalization (calculate semantic value of each state variables)
x_s = (x - x_min)/(x_max - x_min);  % linear normalization (known range)
xd_s = (x_dot - xd_min)/(xd_max - xd_min); % linear normalization (known range)

q_s = sigmf(q, [params.a_sigmoid_q 0]); % using sigmoid function to linearize (unknown range)
qd_s = sigmf(q_dot, [params.a_sigmoid_q_d 0]); % using sigmoid function to linearize (unknown range)

% intermediate controller interpolation
u_x_s  = interp1(params.x_sqm, params.u_x_sqm, x_s, 'linear', 'extrap');
u_xd_s = interp1(params.xd_sqm, params.u_xd_sqm, xd_s, 'linear', 'extrap');
u_q_s  = interp1(params.q_sqm, params.u_q_sqm, q_s, 'linear', 'extrap');
u_qd_s = interp1(params.qd_sqm, params.u_qd_sqm, qd_s, 'linear', 'extrap');

% denormalization
u_x = u_x_s * (u_max - u_min) + u_min;
u_xd = u_xd_s * (u_max - u_min) + u_min;
u_q = u_q_s * (u_max - u_min) + u_min;
u_qd = u_qd_s * (u_max - u_min) + u_min;

% global control input (combine intermediate control signals)
if abs(q) <= alpha
    w1 = 0.25;
    w2 = 0.25;
    w3 = 0.25;
    w4 = 0.25;
elseif abs(q) >= beta
    w1 = 0;
    w2 = 0;
    w3 = 1;
    w4 = 0;
else
    w3 = w_low + (abs(q) - alpha) * ((w_high - w_low)/(beta - alpha)); % q
    w4 = (1 - w3) / 2;                                                 % qd
    w1 = (1 - w3 - w4) / 2;                                            % x
    w2 = w1;                                                           % xd
end
u = w1 * u_x + w2 * u_xd + w3 * u_q + w4 * u_qd;
end
