function[y]=TSHA_MPC(x)% Dieu khien du bao toi uu
%Dieu kien ban dau
r=0.5
Hc=3
Hp=5
 
%Cac tham so cua mo hinh du bao TSHA
p0ss=-0.595
p1ss=1.401
p2ss=-0.894
p0sb=0.880
p1sb=1.186
p2sb=0.993
p0bs=0.235
p1bs=0.872
p2bs=1.355
p0bb=-0.253
p1bb=0.784
p2bb=0.647
teta1=0.427
anpha1=0.252
teta2=0.483
anpha2=0.373
% Tim Chuoi dieu khien toi uu 
%n=5;
%m=3;
% Tinh toan lan luot 
lb=[-1.5;-1.5;-1.5];
ub=[1.5;1.5;1.5];
% Dieu kien ban dau cua 2 input
% buoc 1 tinh toan voi dieu kien 2 input ban dau uka va yka
uka=0.3;% du lieu dau tien 
yka=0.4;% du lieu dau tien 
ukas=(uka(1)+5)/10;
ykas=(yka(1)+5)/10;
       
    etaukasmall0=(teta1*(1-anpha1)+anpha1-ukas)/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaukabig0=(ukas-teta1*(1-anpha1))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaykasmall0=(teta2*(1-anpha2)+anpha2-ykas)/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    etaykabig0=(ykas-teta2*(1-anpha2))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    yTSHA10=p0ss+p1ss*uka+p2ss*yka;
    yTSHA20=p0sb+p1sb*uka+p2sb*yka;
    yTSHA30=p0bs+p1bs*uka+p2bs*yka;
    yTSHA40=p0bb+p1bb*uka+p2bb*yka;
    
    w10=etaukasmall0*etaykasmall0;
    w20=etaukasmall0*etaykabig0;
    w30=etaukabig0*etaykasmall0;
    w40=etaukabig0*etaykabig0;
    yTSHA0=(w10*yTSHA10+w20*yTSHA20+w30*yTSHA30+w40*yTSHA40)/(w10+w20+w30+w40);
    
    % Tinh toan buoc 2 lap lai nhu tren voi 2 input moi ykacong (1)=yTSHA0
    % va ukacong(1)=x(1), bien tham so dieu khien toi uu thu nhat
    ykacong(1)=yTSHA0;
    ukacong(1)=x(1);
    ykacongs(1)=(ykacong(1)+5)/10;
    ukacongs(1)=(ukacong(1)+5)/10;
    
    etaukasmall(1)=(teta1*(1-anpha1)+anpha1-ukacongs(1))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaukabig(1)=(ukacongs(1)-teta1*(1-anpha1))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaykasmall(1)=(teta2*(1-anpha2)+anpha2-ykacongs(1))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    etaykabig(1)=(ykacongs(1)-teta2*(1-anpha2))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    yTSHA1(1)=p0ss+p1ss*ukacong(1)+p2ss*ykacong(1);
    yTSHA2(1)=p0sb+p1sb*ukacong(1)+p2sb*ykacong(1);
    yTSHA3(1)=p0bs+p1bs*ukacong(1)+p2bs*ykacong(1);
    yTSHA4(1)=p0bb+p1bb*ukacong(1)+p2bb*ykacong(1);
    
    w1(1)=etaukasmall(1)*etaykasmall(1);
    w2(1)=etaukasmall(1)*etaykabig(1);
    w3(1)=etaukabig(1)*etaykasmall(1);
    w4(1)=etaukabig(1)*etaykabig(1);
    yTSHA(1)=(w1(1)*yTSHA1(1)+w2(1)*yTSHA2(1)+w3(1)*yTSHA3(1)+w4(1)*yTSHA4(1))/(w1(1)+w2(1)+w3(1)+w4(1));
   % Tinh toan buoc 3 nhu buoc truoc voi 2 iuput moi ykacong(2)=yTSHA(1) và
    % ukacong(2)=x(2)
    ykacong(2)=yTSHA(1);
    ukacong(2)=x(2);
    ykacongs(2)=(ykacong(2)+5)/10;
    ukacongs(2)=(ukacong(2)+5)/10;
    
    etaukasmall(2)=(teta1*(1-anpha1)+anpha1-ukacongs(2))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaukabig(2)=(ukacongs(2)-teta1*(1-anpha1))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaykasmall(2)=(teta2*(1-anpha2)+anpha2-ykacongs(2))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    etaykabig(2)=(ykacongs(2)-teta2*(1-anpha2))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    yTSHA1(2)=p0ss+p1ss*ukacong(2)+p2ss*ykacong(2);
    yTSHA2(2)=p0sb+p1sb*ukacong(2)+p2sb*ykacong(2);
    yTSHA3(2)=p0bs+p1bs*ukacong(2)+p2bs*ykacong(2);
    yTSHA4(2)=p0bb+p1bb*ukacong(2)+p2bb*ykacong(2);
    
    w1(2)=etaukasmall(2)*etaykasmall(2);
    w2(2)=etaukasmall(2)*etaykabig(2);
    w3(2)=etaukabig(2)*etaykasmall(2);
    w4(2)=etaukabig(2)*etaykabig(2);
    yTSHA(2)=(w1(2)*yTSHA1(2)+w2(2)*yTSHA2(2)+w3(2)*yTSHA3(2)+w4(2)*yTSHA4(2))/(w1(2)+w2(2)+w3(2)+w4(2));
    % Tinh buoc 3 nhu buoc 2 voi 2 input moi ykacong (3)=ySTHA(2) va %ukacong(3)=x(3)
    ykacong(3)=yTSHA(2);
    ukacong(3)=x(3);
    ykacongs(3)=(ykacong(3)+5)/10;
    ukacongs(3)=(ukacong(3)+5)/10;
    
    etaukasmall(3)=(teta1*(1-anpha1)+anpha1-ukacongs(3))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaukabig(3)=(ukacongs(3)-teta1*(1-anpha1))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaykasmall(3)=(teta2*(1-anpha2)+anpha2-ykacongs(3))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    etaykabig(3)=(ykacongs(3)-teta2*(1-anpha2))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    yTSHA1(3)=p0ss+p1ss*ukacong(3)+p2ss*ykacong(3);
    yTSHA2(3)=p0sb+p1sb*ukacong(3)+p2sb*ykacong(3);
    yTSHA3(3)=p0bs+p1bs*ukacong(3)+p2bs*ykacong(3);
    yTSHA4(3)=p0bb+p1bb*ukacong(3)+p2bb*ykacong(3);
    
    w1(3)=etaukasmall(3)*etaykasmall(3);
    w2(3)=etaukasmall(3)*etaykabig(3);
    w3(3)=etaukabig(3)*etaykasmall(3);
    w4(3)=etaukabig(3)*etaykabig(3);
    yTSHA(3)=(w1(3)*yTSHA1(3)+w2(3)*yTSHA2(3)+w3(3)*yTSHA3(3)+w4(3)*yTSHA4(3))/(w1(3)+w2(3)+w3(3)+w4(3));
    %Buoc 4 khac mot chut voi buoc 3 vi 2 input moi lai la
    %ykacong(4)=yTSHA(3) nhung ukacong(4)=x(3)
    
    ykacong(4)=yTSHA(3);
    ukacong(4)=x(3);
    ykacongs(4)=(ykacong(4)+5)/10;
    ukacongs(4)=(ukacong(4)+5)/10;
    
    etaukasmall(4)=(teta1*(1-anpha1)+anpha1-ukacongs(4))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaukabig(4)=(ukacongs(4)-teta1*(1-anpha1))/(teta1*(1-anpha1)+anpha1-teta1*(1-anpha1));
    etaykasmall(4)=(teta2*(1-anpha2)+anpha2-ykacongs(4))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    etaykabig(4)=(ykacongs(4)-teta2*(1-anpha2))/(teta2*(1-anpha2)+anpha2-teta2*(1-anpha2));
    yTSHA1(4)=p0ss+p1ss*ukacong(4)+p2ss*ykacong(4);
    yTSHA2(4)=p0sb+p1sb*ukacong(4)+p2sb*ykacong(4);
    yTSHA3(4)=p0bs+p1bs*ukacong(4)+p2bs*ykacong(4);
    yTSHA4(4)=p0bb+p1bb*ukacong(4)+p2bb*ykacong(4);
    
    w1(4)=etaukasmall(4)*etaykasmall(4);
    w2(4)=etaukasmall(4)*etaykabig(4);
    w3(4)=etaukabig(4)*etaykasmall(4);
    w4(4)=etaukabig(4)*etaykabig(4);
    yTSHA(4)=(w1(4)*yTSHA1(4)+w2(4)*yTSHA2(4)+w3(4)*yTSHA3(4)+w4(4)*yTSHA4(4))/(w1(4)+w2(4)+w3(4)+w4(4));
    %Buoc 5 tinh nhu buoc 4 voi 2 input moi ykacong(5)=yTSHA(4) va
    %ukacong(5)=x(3)
    ykacong(5)=yTSHA(4);
    ukacong(5)=x(3);
    
        
    %Tinh dieu khien du bao toi uu y=JTSHA  
    error1(1)=(r-ykacong(1))^2;
    error1(2)=(r-ykacong(2))^2;
    error1(3)=(r-ykacong(3))^2;
    error1(4)=(r-ykacong(4))^2;
    error1(5)=(r-ykacong(5))^2;
    
    error2(1)=(ukacong(1))^2;
    error2(2)=(ukacong(2))^2;
    error2(3)=(ukacong(3))^2;
    error2(4)=(ukacong(4))^2;
    error2(5)=(ukacong(5))^2;
        
    y1=sum(error1);
    y2=sum(error2);
    y=y1+y2;   
end
