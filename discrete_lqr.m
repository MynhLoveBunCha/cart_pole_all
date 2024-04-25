function k_lqr = discrete_lqr(m,M,L,I,g,kd, kt, Fc)

A = zeros(4, 4);
B = zeros(4, 1);
C = eye(4, 4);
D = 0;

A(1, 2) = 1;
A(3, 4) = 1;
A(4, 3) = m*g*L/(m*L^2 + I);
A(4, 4) = -(kd)/(m*L^2 + I);

B(2,:) = 1;
B(4,:) = -m*L/(m*L^2 + I);
myCartPend = ss(A,B,C,D);

my_discrete_cartpend = c2d(myCartPend,0.001);  % discretize system

A_discrete = my_discrete_cartpend.A;
B_discrete = my_discrete_cartpend.B;
C_discrete = my_discrete_cartpend.C;
D_discrete = my_discrete_cartpend.D;

Q = diag([4 0.1 11 0.2 ]); % [x xd q qd]
R = 0.02;

[k_lqr, ~, poles] = dlqr(A_discrete,B_discrete,Q,R);
disp(k_lqr);
disp(poles);
end