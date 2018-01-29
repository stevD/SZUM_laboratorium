%% zmierzyc wymiary drukarki
%% przyspieszyc komunikacje
%%


clf;
% clear;
tekst=['x=' num2str(0) ' y=' num2str(0) ' z=' num2str(0) ' a'];


x1=0;
y1=1;
z1=0;

x2=0;
y2=2;
z2=0;

x3=1.7;
y3=2;
z3=0;

xc=0.6;
yc=2.4;
zc=2;

r=2;

z1=zc+sqrt(r^2-(x1-xc)^2-(y1-yc)^2);
z2=zc+sqrt(r^2-(x2-xc)^2-(y2-yc)^2);
z3=zc+sqrt(r^2-(x3-xc)^2-(y3-yc)^2);

line([x1 x1],[y1 y1],[0 4]);
line([x2 x2],[y2 y2],[0 4]);
line([x3 x3],[y3 y3],[0 4]);
view(15,39);
axis([0 2 1 3 1 3]);
axis equal;
arm1=line([x1 xc],[y1 yc],[z1 zc]);
arm2=line([x2 xc],[y2 yc],[z2 zc]);
arm3=line([x3 xc],[y3 yc],[z3 zc]);

hold on
for t=0:0.1:40
    
xc=0.6+0.2*sin(t);
yc=2.4+0.2*cos(t);
zc=2+0.01*t;

z1=zc+sqrt(r^2-(x1-xc)^2-(y1-yc)^2);
z2=zc+sqrt(r^2-(x2-xc)^2-(y2-yc)^2);
z3=zc+sqrt(r^2-(x3-xc)^2-(y3-yc)^2);

if exist('z01','var')
    kroki1=z1-z01;
    kroki2=z2-z02;
    kroki3=z3-z03;
end

set(arm1,'xData',[x1 xc],'yData',[y1 yc],'zData',[z1 zc]);
set(arm2,'xData',[x2 xc],'yData',[y2 yc],'zData',[z2 zc]);
set(arm3,'xData',[x3 xc],'yData',[y3 yc],'zData',[z3 zc]);

plot3(xc,yc,zc,'.');
pause(0.1);
z01=z1;
z02=z2;
z03=z3;
if exist('kroki1','var')
tekst=['x=' num2str(round(kroki3*10000)) ' y=' num2str(round(kroki2*10000)) ' z=' num2str(round(kroki1*10000)) ' a\n']
end

fprintf(s,tekst);
end