
y = [
763 619 457 244 172 137 80 75 107 114 174 319 529 509 574 587 693 754 825 1037 1114 1006 952 865
]';
t = [0:23]';
X = [ones(size(t)) sin(pi/12*t) cos(pi/12*t)];
a = X\y;
T = [0:.1:23.9]';
Y = [ones(size(T)) sin(T*pi/12) cos(T*pi/12)]*a
Yc = [ones(size(t)) sin(t*pi/12) cos(t*pi/12)]*a;
e = (y-Yc) ./ a(1);
r = 1-sqrt(sum(e.^2)/24)
alpha = a(1)
beta = sqrt(a(2)^2 + a(3)^2)
omega = pi/12;
if (sign(a(2)*a(3)) > 0)
phi = abs(atan(a(3)/a(2)) / omega - 24)
else
phi = abs(atan(a(3)/a(2)) / omega - 12)
endif 
