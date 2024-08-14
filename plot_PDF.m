clear,clc,close all
fileName = 'analysis_exp2.pdf';

sigmoid_func = @(x) sigmf(x,[1,0]);
tanh_func = @(x) tanh(x);

sigmoid_der = @(x) sigmoid_func(x).*(1-sigmoid_func(x));
tanh_der = @(x) 1 - tanh(x).^2;

range = [-10 10];

f1 = figure;
fplot(sigmoid_func, range, LineWidth=2)
hold on;
fplot(tanh_func, range, LineWidth=2)
grid on;
legend(["sigmoid", "tanh"]);
title("Sigmoid and Tanh");

f2 = figure;
fplot(sigmoid_der, range, LineWidth=2)
hold on;
fplot(tanh_der, range, LineWidth=2)
grid on;
legend(["sigmoid prime", "tanh prime"]);
title("Derivatives of Sigmoid and Tanh");

exportgraphics(f1, "sig_vs_tanh.pdf", "ContentType","vector");
exportgraphics(f2, "der_sig_vs_der_tanh.pdf", "ContentType","vector");