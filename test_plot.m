clear, clc, close all;

%% data prep
RSHAC = load("RSHAC_30_deg.mat").out;
HAC = load("HAC_thayLe_30_deg.mat").out;
LQR = load("LQR_cartPend_30deg.mat").out;

% get time
t = RSHAC.data_HAC.Time';

% RSHAC
data_RSHAC = RSHAC.data_HAC.Data;
x_RSHAC   = data_RSHAC(:, 1);
x_d_RSHAC = data_RSHAC(:, 2);
q_RSHAC   = data_RSHAC(:, 3);
q_d_RSHAC = data_RSHAC(:, 4);
u_RSHAC   = data_RSHAC(:, 5);

% HAC
data_HAC = HAC.data_HAC.Data;
x_HAC   = data_HAC(:, 1);
x_d_HAC = data_HAC(:, 2);
q_HAC   = data_HAC(:, 3);
q_d_HAC = data_HAC(:, 4);
u_HAC   = data_HAC(:, 5);

% LQR
data_LQR = LQR.data_energy_LQR.Data;
x_LQR   = data_LQR(:, 1);
x_d_LQR = data_LQR(:, 2);
q_LQR   = data_LQR(:, 3);
q_d_LQR = data_LQR(:, 4);
u_LQR   = data_LQR(:, 5);

% ref signal
ref_step = 0.2.*heaviside(t - 4);
ref_zero = zeros(size(t));
%% plot prep
tiledlayout(3, 2, "TileIndexing","rowmajor", "TileSpacing","tight", "Padding","tight");
scaleCoeff = 2;
fig = gcf;
fig.Position(1) = 0;
fig.Position(2) = -100;
fig.Position(3) = 2 * fig.Position(3);
fig.Position(4) = scaleCoeff * fig.Position(4);

%% plotting
nexttile;
plot(t, x_RSHAC, t, x_HAC, t, x_LQR, t, ref_step,"k--", "LineWidth", 1.5);
legend("x_{RSHAC}","x_{HAC}", "x_{LQR}", "x_{ref}",'NumColumns',2);
title('Cart position');
xlabel("time (s)");
ylabel("(m)");
grid on;

nexttile;
plot(t, x_d_RSHAC, t, x_d_HAC, t, x_d_LQR, t, ref_zero,"k--","LineWidth", 1.5);
legend("x_{d RSHAC}", "x_{d HAC}", "x_{d LQR}", "x_{d ref}",'NumColumns',2);
title('Cart velocity');
xlabel("time (s)");
ylabel("(m/s)");
grid on;

nexttile;
plot(t, rad2deg(q_RSHAC), t, rad2deg(q_HAC), t, rad2deg(q_LQR), t, ref_zero,"k--", "LineWidth", 1.5);
legend("q_{RSHAC}", "q_{HAC}", "q_{LQR}", "q_{ref}",'NumColumns',2);
title('Pendulum angle');
xlabel("time (s)");
ylabel("(deg)");
grid on;

nexttile;
plot(t, rad2deg(q_d_RSHAC), t, rad2deg(q_d_HAC), t, rad2deg(q_d_LQR), t, ref_zero,"k--", "LineWidth", 1.5);
legend("q_{d RSHAC}", "q_{d HAC}", "q_{d LQR}", "q_{d ref}",'NumColumns',2);
title('Pendulum angular velocity');
xlabel("time (s)");
ylabel("(deg/s)");
grid on;

nexttile;
plot(t, u_RSHAC, t, u_HAC, t, u_LQR, "LineWidth", 1.5);
legend("u_{RSHAC}", "u_{HAC}", "u_{LQR}",'NumColumns',2);
title('Input');
xlabel("time (s)");
ylabel("(m/s2)");
grid on;
