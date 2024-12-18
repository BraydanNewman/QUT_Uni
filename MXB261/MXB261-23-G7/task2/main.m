% Set Up variables 
k1 = 1;
k2 = 2;
k5 = 3;

T = 20;
tspan = [0 20];

X1_start = 1;
X2_start = 1;

TOL = 0.1;

scale_factor = 200;

col_row_n = 25000;

% Get the samples from the lhs funtion
samples = lhs(col_row_n);

k3_case1_Array = [];
k3_case2_Array = [];
k3_case3_Array = [];
k4_case1_Array = [];
k4_case2_Array = [];
k4_case3_Array = [];


% Run the simulation on all the samples
for sample_index = 1:length(samples)
%     Scale all the points to the correct values
    k3 = samples(1,sample_index) * scale_factor;
    k4 = samples(2,sample_index) * scale_factor;
    
% Run sample though ODE45
    [t_ode_1,x_ode_1] = ode45(@(t1,x1)odeMethod(t1,x1,k1,k2,k3,k4,k5),tspan,[X1_start X2_start]);
    for j = 1:length(x_ode_1)
        case1 = x_ode_1(j,2) <= 2+TOL && x_ode_1(j,2) >= 2-TOL;
        case2 = x_ode_1(j,1) <= 0+TOL && x_ode_1(j,1) >= 0;
    end
    
%     Sort sample into correct cases
    if(case1 && case2)
        k3_case3_Array = cat(2,k3_case3_Array,k3);
        k4_case3_Array = cat(2,k4_case3_Array,k4);
    elseif(case1 && ~case2)
        k3_case1_Array = cat(2,k3_case1_Array,k3);
        k4_case1_Array = cat(2,k4_case1_Array,k4);
    elseif(~case1 && case2)
        k3_case2_Array = cat(2,k3_case2_Array,k3);
        k4_case2_Array = cat(2,k4_case2_Array,k4);
    end
end

% Plot the samples
figure
hold on
scatter(k3_case1_Array,k4_case1_Array,'blue','filled',DisplayName= "case 1")
scatter(k3_case2_Array,k4_case2_Array,'red','filled',DisplayName= "case 2")
scatter(k3_case3_Array,k4_case3_Array,'green','filled',DisplayName= "Both cases satisified")

title("Latin Hypercube Sampling in 2D", "Point Count: " + col_row_n, "FontSize", 20)
xlabel('k3 value', 'FontSize',20)
ylabel('k4 value', 'FontSize', 20)
lgd = legend;
lgd.Location = 'southoutside';
lgd.NumColumns = 2;
lgd.FontSize = 6;

%% Functions

function odeSystem = odeMethod(t, x, k1,k2,k3,k4,k5)
X1 = x(1);
X2 = x(2);
odeSystem = [k1*X1*X2 - k2*X1;k3-k4*X2-k5*X1];
end

