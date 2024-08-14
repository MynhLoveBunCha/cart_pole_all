clear,clc, close all;

k=2;
xMax=2;

u =@(x) k.*sign(x).*log(1-abs(x)/xMax);
fplot(u,[-2.5,2.5], "LineWidth", 2, "Color","red");
ylim([-10,10]);
legend("$k_{vL}=2$, $\dot{x}_{max}=2$", "Location","northeast", "Interpreter","latex", "FontSize",14)
title("Cart velocity potential well", "FontSize",14);
xlabel("$\dot{x}$ (m/s)", "Interpreter","latex", "FontSize",14);
ylabel("$u_{\dot{x}Lim}$ (N)", "Interpreter","latex", "FontSize",14);
grid on

exportgraphics(gcf,'cart_vel_pot_well.pdf','ContentType','vector')