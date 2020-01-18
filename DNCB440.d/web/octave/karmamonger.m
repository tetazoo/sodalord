
y = [
34 29 38 26 27 27 14 12 21 14 18 24 24 25 27 24 18 21 16 29 26 38 18 44
]';
t = [0:23]';
X = [ones(size(t)) sin(pi/12*t) cos(pi/12*t)];
a = X\y;
T = [0:.1:23.9]';
Y = [ones(size(T)) sin(T*pi/12) cos(T*pi/12)]*a
Yc = [ones(size(t)) sin(t*pi/12) cos(t*pi/12)]*a;
r = sum((Yc-a(1)).^2)/sum((y-a(1)).^2)
alpha = a(1)
beta = sqrt(a(2)^2 + a(3)^2)
omega = pi/12;
phi = atan(-a(3)/a(2)) / omega;
if sign(a(2)) < 0
phi = phi + 12;
endif
if phi < 0
phi = phi + 24
else
phi = phi
endif 
