function MSE = TSHA_SYSTEM_ID(x)
% Du lieu VAO RA, cho truoc uka(1)=-1.0;yka(1)=0.0. Co the chon ngau nhien
uka=[-1.0;-0.9;-0.8;-0.7;-0.6;-0.5;-0.4;-0.3;-0.2;-0.1;0.0; ...
    0.1;0.2;0.3;0.4;0.5;0.6;0.7;0.8;0.9;1.0];
yka=[0.0;-1.0;-1.4;-1.273;-1.186;-1.093;-0.998;-0.9;-0.797;-0.687;-0.567; ...
    -0.429;-0.262;-0.045;0.255;0.639;0.954;1.099;1.198;1.292;1.384];
ykacong=[-1.0;-1.4;-1.273;-1.186;-1.093;-0.998;-0.9;-0.797;-0.687;-0.567; ...
    -0.429;-0.262;-0.045;0.255;0.639;0.954;1.099;1.198;1.292;1.384;1.475];
%Luu y ykacong=y(k+1)
n=21;
% Chon 2 gia tri ngon ngu Small=teta*(1-anpha) va Big=teta*(1-anpha)+anpha
% cho ca hai bien ngon ngu uka va yka 
% Khoang xac dinh uka=[-2 2];yka=[-2 2] voi phep ngu nghia hoa xs=(x+2)/4
% Tao cac an so nhu sau
teta1=x(1);% Khoang xac dinh [0.4 0.6] cho uka
anpha1=x(2);% ...[0.25 0.75] cho uka
teta2=x(3); % nt cho yka
anpha2=x(4);% nt cho yka
p0ss=x(5);% KXD [-1.5 1.5] theo Tai Lieu Tham Khao [ ]
p1ss=x(6);% nhu tren
p2ss=x(7);
p0sb=x(8);
p1sb=x(9);
p2sb=x(10);
p0bs=x(11);
p1bs=x(12);
p2bs=x(13);
p0bb=x(14);
p1bb=x(15);
p2bb=x(16);% nhu tren
lb=[0.4;0.25;0.4;0.25;-1.5;-1.5;-1.5;-1.5;-1.5;-1.5;-1.5;-1.5;-1.5;-1.5;-1.5;-1.5];
ub=[0.6;0.75;0.6;0.75;1.5;1.5;1.5;1.5;1.5;1.5;1.5;1.5;1.5;1.5;1.5;1.5];
% TINH TOAN gia tri ngu nghia ukas(i) va ykas(i) tren co so cac du lieu
% vao uka va yka theo cong thuc xs=(x+5)/10 chung cho uka va yka 
for i=1:n
    % normalization
    ukas(i)=(uka(i)+5)/10;
    ykas(i)=(yka(i)+5)/10;
    % TODO: interpolation here (wrong formulas)
    etaukasmall(i)=(teta1*(1-anpha1)+anpha1-ukas(i))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaukabig(i)=(ukas(i)-teta1*(1-anpha1))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    
    etaykasmall(i)=(teta2*(1-anpha2)+anpha2-ykas(i))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    etaykabig(i)=(ykas(i)-teta2*(1-anpha2))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    
    % Tren co so du lieu VAO uka va yka
    %TINH TOAN CAC GIA TRI THE HIEN MUC DO GAN CAC GIA TRI NGON NGU 
    %etauka cua uka va etayka cua yka. 
    yTSHA1(i)=p0ss+p1ss*uka(i)+p2ss*yka(i);
    yTSHA2(i)=p0sb+p1sb*uka(i)+p2sb*yka(i);
    yTSHA3(i)=p0bs+p1bs*uka(i)+p2bs*yka(i);
    yTSHA4(i)=p0bb+p1bb*uka(i)+p2bb*yka(i);
    %Ket nhap 4 luat de co yTSHA (i) tong hop theo cac trong so w1,w2,w3,w4
    w1(i)=etaukasmall(i)*etaykasmall(i);
    w2(i)=etaukasmall(i)*etaykabig(i);
    w3(i)=etaukabig(i)*etaykasmall(i);
    w4(i)=etaukabig(i)*etaykabig(i);
    yTSHA(i)=(w1(i)*yTSHA1(i)+w2(i)*yTSHA2(i)+w3(i)*yTSHA3(i)+w4(i)*yTSHA4(i))/(w1(i)+w2(i)+w3(i)+w4(i));
    error1(i)=ykacong(i)-yTSHA(i);
    error2(i)=error1(i)^2;
end
MSE=(1/n)*sum(error2);% Ham toi uu theo GA
end
