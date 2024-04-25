function [t0, x0, u0] = shift(T, t0, x0, u,f)
st = x0;
con = u(1,:)';
N = 1;

for i = 1:N
    st = full(RK4(st,con,f,T/N));
end

t0 = t0 + T;
x0 = st;
u0 = [u(2:size(u,1),:);u(size(u,1),:)];
end