function X_next = discrete_cartpend(X, u)

M = 10;
Ts = 0.1; % sec

delta = Ts/M;
X_next = X;
for ct=1:M
    X_next = X_next + delta*continuous_cartpend(X_next,u);
end
end