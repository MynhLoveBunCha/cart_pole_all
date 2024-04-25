function u = my_HAC(X, X_range) % apply for each X (not for whole trajectory)
% Extract states variables range
x_min = X_range.x_min;
x_max = X_range.x_max;
xd_min = X_range.xd_min;
xd_max = X_range.xd_max;
q_min = X_range.q_min;
q_max = X_range.q_max;
qd_min = X_range.qd_min;
qd_max = X_range.qd_max;
u_min = X_range.u_min;
u_max = X_range.u_max;

% Extract states variables
x = X(1);
x_dot = X(2);
q = X(3);
q_dot = X(4);

% Normalization (calculate semantic value of each state variables)
xs = (x - x_min)/(x_max - x_min);
x_dots = (x_dot - xd_min)/(xd_max - xd_min);
qs = (q - q_min)/(q_max - q_min);
q_dots = (q_dot - qd_min)/(qd_max - qd_min);

% prod
x_star=qs*q_dots*xs*x_dots;%*Ws;

% interpolation for semantic output
us_out = Interpolation(x_star);

% denormalization
u = us_out * (u_max - u_min) + u_min;
end


%  function interpolation
function us_out = Interpolation(x_star)
x_sqm = [0 0.00390625 0.0078125 0.01171875 0.015625 0.0234375 0.03125 ...
    0.03515625 0.046875 0.0625 0.0703125 0.09375 0.10546875 0.140625 0.2109375 0.31640625];
% y_sqm =[0 0.18	0.18	0.3	0.3	0.38	0.38	0.5	0.5	0.5	0.62	0.62	0.7	0.7	0.82	0.82];
y_sqm = [0 0.15 0.15 0.25 0.25 0.375 0.375 0.5 0.5 ...
    0.5 0.625 0.625 0.75 0.75 0.825 0.825];

us_out = interp1(x_sqm, y_sqm, x_star, 'spline');  %TODO: define value for the case x_star is outside of x_sqm
end                                                %TODO: maybe "spline" is not the correct option