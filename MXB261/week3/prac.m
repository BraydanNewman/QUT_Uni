%% Needle thing

n = 10000;
m = 10;

figure
hold on

yline(pi, 'k', 'LineWidth', 1.5, 'LineStyle','--')

for j = 0:m
    l = 0;
    approx = zeros(n/10);
    for i = 0:n
        u1 = rand * (1 / 2);
        u2 = rand * (pi / 2);
    
        if u1<=0.5*sin(u2)
            l = l + 1;
        end
    
        if mod(i, 10) == 0 && i ~= 0
            approx(i/10) = 2 * i / l;
        end
    end
    plot(approx)
end
ylim([1.5 5])

%% Box-Muller

figure
hold on

n = 10000;

normalStuff = zeros(2*n, 1);


for i = 1:n
    u1 = rand;
    u2 = rand;
       
    X = sqrt(-2 * log(u1)) * cos(2 * pi * u2);
    Y = sqrt(-2 * log(u1)) * sin(2 * pi * u2);
    normalStuff(2 * i - 1)= X;
    normalStuff(2 * i) = Y;
end

histogram(normalStuff)

%% Polar Marsaglia

n = 1000000;

normalStuff = zeros(2*n, 1);

tic;

for i = 1:n
    w = 0;
    while 0 >= w || w > 1
        u1 = rand;
        u2 = rand;
    
        v1 = 2 * u1 - 1;
        v2 = 2 * u2 - 1;
    
        w = v1^2 + v2^2;
    
        if 0 < w && w <= 1
            X = v1 * sqrt(-2 * log(w)/w);
            Y = v2 * sqrt(-2 * log(w)/w);
        
            normalStuff(2 * i - 1)= X;
            normalStuff(2 * i) = Y;
        end
    end
end

toc


histogram(normalStuff)

