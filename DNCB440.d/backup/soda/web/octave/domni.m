
y = [
15 16 25 14 9 11 3 1 0 2 2 9 5 3 11 11 14 22 13 20 9 15 11 31
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