clear,clc, close all;

x_sqm = [0 0.00390625 0.0078125 0.01171875 0.015625 0.0234375 0.03125 ...
    0.03515625 0.046875 0.0625 0.0703125 0.09375 0.10546875 0.140625 0.2109375 0.31640625];
y_sqm = [0 0.15 0.15 0.25 0.25 0.375 0.375 0.5 0.5 ...
    0.5 0.625 0.625 0.75 0.75 0.825 0.825];

plot(x_sqm, y_sqm, 'Color', 'black', 'LineWidth', 1);
hold on;
scatter(x_sqm, y_sqm, "filled","o");
grid on;