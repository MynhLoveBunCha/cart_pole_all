clear, clc, close all;

%% data prep
initial_angle = 0; %deg [10, 20, 30]
experiment_num = 2; %1-balance, 2-move

RSHAC = load(sprintf("RSHAC_init_%d_deg_experiment_%d_full.mat", initial_angle, experiment_num)).out;
FC = load(sprintf("FC_init_%d_deg_experiment_%d_full.mat", initial_angle, experiment_num)).out;
LQR = load(sprintf("LQR_init_%d_deg_experiment_%d_full.mat", initial_angle, experiment_num)).out;

% RSHAC
t_RSHAC    = RSHAC.data_RSHAC.Time(1:8000);
data_RSHAC = RSHAC.data_RSHAC.Data;
x_RSHAC    = data_RSHAC(1:8000, 1);
x_d_RSHAC  = data_RSHAC(1:8000, 2);
q_RSHAC    = data_RSHAC(1:8000, 3);
q_d_RSHAC  = data_RSHAC(1:8000, 4);
u_RSHAC    = data_RSHAC(1:8000, 5);

% FC
t_FC    = FC.data_RSHAC.Time(1:8000);
data_FC = FC.data_RSHAC.Data;
x_FC    = data_FC(1:8000, 1);
x_d_FC  = data_FC(1:8000, 2);
q_FC    = data_FC(1:8000, 3);
q_d_FC  = data_FC(1:8000, 4);
u_FC    = data_FC(1:8000, 5);

% LQR
t_LQR    = LQR.data_RSHAC.Time(1:8000);
data_LQR = LQR.data_RSHAC.Data;
x_LQR    = data_LQR(1:8000, 1);
x_d_LQR  = data_LQR(1:8000, 2);
q_LQR    = data_LQR(1:8000, 3);
q_d_LQR  = data_LQR(1:8000, 4);
u_LQR    = data_LQR(1:8000, 5);

% ref signal
if experiment_num == 1
    x_ref = @(t) 0.*t;
else
    x_ref = @(t) 0.2.*heaviside(t-1);
end
ref_zero = @(t) 0.*t;

%% plot prep
tiledlayout(3, 2, "TileIndexing","rowmajor", "TileSpacing","tight", "Padding","tight");
scaleCoeff = 2;
fig = gcf;
fig.Position(1) = 0;
fig.Position(2) = -100;
fig.Position(3) = 2 * fig.Position(3);
fig.Position(4) = scaleCoeff * fig.Position(4);

lineWidth = 1.5;
if experiment_num==1
    legendLoc = 'northeast';
else
    legendLoc = 'southeast';
end

%% plotting
nexttile;
plot(t_RSHAC, x_RSHAC, ...
    t_FC, x_FC, ...
    t_LQR, x_LQR, ...
    "LineWidth", lineWidth);
hold on;
fplot(x_ref, [0 8], "k--", "LineWidth", lineWidth);
legend("x_{RSHAC}","x_{FC}", "x_{LQR}", "x_{ref}",'NumColumns',2,'Location', legendLoc);
title('Cart position');
xlabel("time (s)");
ylabel("(m)");
grid on;
hold off;

nexttile;
plot(t_RSHAC, x_d_RSHAC, ...
    t_FC, x_d_FC, ...
    t_LQR, x_d_LQR, ...
    "LineWidth", lineWidth);
hold on;
fplot(ref_zero, [0 8], "k--", "LineWidth", lineWidth);
legend("x_{d RSHAC}", "x_{d FC}", "x_{d LQR}", "x_{d ref}",'NumColumns',2,'Location', legendLoc);
title('Cart velocity');
xlabel("time (s)");
ylabel("(m/s)");
grid on;
hold off;

nexttile;
plot(t_RSHAC, rad2deg(q_RSHAC), ...
    t_FC, rad2deg(q_FC), ...
    t_LQR, rad2deg(q_LQR), ...
    "LineWidth", lineWidth);
hold on;
fplot(ref_zero, [0 8], "k--", "LineWidth", lineWidth);
legend("q_{RSHAC}", "q_{FC}", "q_{LQR}", "q_{ref}",'NumColumns',2,'Location', legendLoc);
title('Pendulum angle');
xlabel("time (s)");
ylabel("(deg)");
grid on;
hold off;

nexttile;
plot(t_RSHAC, rad2deg(q_d_RSHAC), ...
    t_FC, rad2deg(q_d_FC), ...
    t_LQR, rad2deg(q_d_LQR), ...
    "LineWidth", lineWidth);
hold on;
fplot(ref_zero, [0 8], "k--", "LineWidth", lineWidth);
legend("q_{d RSHAC}", "q_{d FC}", "q_{d LQR}", "q_{d ref}",'NumColumns',2,'Location', legendLoc);
title('Pendulum angular velocity');
xlabel("time (s)");
ylabel("(deg/s)");
grid on;
hold off;

nexttile;
plot(t_RSHAC, u_RSHAC, ...
    t_FC, u_FC, ...
    t_LQR, u_LQR, ...
    "LineWidth", lineWidth);
legend("u_{RSHAC}", "u_{FC}", "u_{LQR}",'NumColumns',2,'Location', legendLoc);
title('Input');
xlabel("time (s)");
ylabel("(m/s2)");
grid on;

%% save fig as PDF
fileName = 'RSHAC_FC_LQR_experiment_2.pdf';
exportgraphics(gcf, fileName, 'ContentType', 'vector');