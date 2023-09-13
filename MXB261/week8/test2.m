k1 = 1;
k2 = 2;
N = 50;
T = 5;
t0 = 0;
C0 = 5;
P0 = N - C0;

M = 100;

[countC, countP] = ionStoch(k1,k2,C0,N,T,M);

figure
hold on
plot(countP);
plot(countC);
