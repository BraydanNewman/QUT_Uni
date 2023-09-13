k1 = 1;
k2 = 2;
Ns = 1000;
t0 = 0;
C0 = 5;

T = 5;

for n = [50, 100, 400, 1000]
    hold on
    P0 = n - C0;
    
    [t,y] = ode45(@(t,y)ionChannelFn(t, y, k1,k2), [t0, T], [C0, P0]);


    plot(t,y,"*-")
end

%%





