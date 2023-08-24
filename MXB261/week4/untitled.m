%% Space Cows
%% Sim
%    F   WH  NH
T = [0.5 0.2 0.35; % F
     0.1 0.4 0.55; % WH
     0.4 0.4 0.1]; % NH

n = 100000;

locations = zeros(1, n+1);

locations(1) = 1;

for i = 1:n
    u = rand;
    
    probs = cumsum(T(:,locations(i)));

    if u < probs(1)
        locations(i+1) = 1;
    elseif u < probs(2)
        locations(i+1) = 2;
    else
        locations(i+1) = 3;
    end
end

figure
h = histogram(locations(2:end));
xsim = h.Values/N;
disp(xsim)

%% Analytical

%    F   WH  NH
T = [0.5 0.2 0.35; % F
     0.1 0.4 0.55; % WH
     0.4 0.4 0.1]; % NH

n = 100000;
x0 = [1 0 0];
XN = T^n .* x0;
XN(:,1)

%% Random Walks

%   1   2   3    4    5   6
T = [
    0   1/3 0.25 0    0   0   % 1
    0.5 0   0.25 0.25 0   0   % 2
    0.5 1/3 0    0.25 1/3 0   % 3
    0   1/3 0.25 0    1/3 0.5 % 4
    0   0   0.25 0.25 0   0.5 % 5
    0   0   0    0.25 1/3 0   % 6
];

n = 100000;

locations = zeros(1, n+1);

locations(1) = 1;

for i = 1:n
    u = rand;
    
    probs = cumsum(T(:,locations(i)));

    if u < probs(1)
        locations(i+1) = 1;
    elseif u < probs(2)
        locations(i+1) = 2;
    elseif u < probs(3)
        locations(i+1) = 3;
    elseif u < probs(4)
        locations(i+1) = 4;
    elseif u < probs(5)
        locations(i+1) = 5;
    elseif u < probs(6)
        locations(i+1) = 6;
    end
end

figure
h = histogram(locations(2:end));
xsim = h.Values/N;
disp(xsim)


%% Analytical

%   1   2   3    4    5   6
T = [
    0   1/3 0.25 0    0   0   % 1
    0.5 0   0.25 0.25 0   0   % 2
    0.5 1/3 0    0.25 1/3 0   % 3
    0   1/3 0.25 0    1/3 0.5 % 4
    0   0   0.25 0.25 0   0.5 % 5
    0   0   0    0.25 1/3 0   % 6
];

n = 1000000;

x0 = [1; 0; 0; 0; 0; 0];
XN = T^n * x0;
XN(:,1)

%% Chalange









