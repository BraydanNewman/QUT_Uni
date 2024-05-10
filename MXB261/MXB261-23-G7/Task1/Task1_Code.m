 %% Assignment 2 - Task 1 MATLAB solution

%% Initialise Parameters
T = 20; % Maximum time [units]
tspan = [0 T]; % define time span to simulate over
h = 0.01; % step size
X1_0 = 1; % intial population of parasites
X2_0 = 1; % intial population of food
k1 = 1; % parasite birth rate
k2 = 2; % parasite death rate
k5 = 3; % food consumption rate

%% Part B Comparison of Euler model vs ode45 model
k3 = 20; % simulate with given food growth rate
k4 = 4; % simulate with given food decay rate

% Call Euler method function 
[t_euler,X1_euler,X2_euler] = EulerMethod(X1_0,X2_0,k3,k4,h,T);

% Call ode method function as an input to ode45
[t_ode,x_ode] = ode45(@(t,x)odeMethod(t,x,k1,k2,k3,k4,k5),tspan,[X1_0 X2_0]);

% Plotting code
figure 
hold on
plot(t_euler,X1_euler,'r-'); 
plot(t_euler,X2_euler,'r--');
plot(t_ode,x_ode(:,1),'b-');
plot(t_ode,x_ode(:,2),'b--');
legend('X1 Euler Approximation','X2 Euler Approximation','X1 ODE45 solution','X2 ODE45 solution')
xlabel('Time [units]');
ylabel('Population Size');
title('Comparison of ode45 solution to Eulers Method solution')

% measure of accuracy
% Take the mean of the maximum absolute error between solutions 
rmse_X1 = mean(sqrt(mean((X1_euler - x_ode(:,1)).^2)));
rmse_X2 = mean(sqrt(mean((X2_euler - x_ode(:,2)).^2)));

% Add the error values to the graph
text(t_euler(end), X1_euler(end), ['mean RMSE X1: ', num2str(rmse_X1)], 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');
text(t_euler(end), X2_euler(end), ['mean RMSE X2: ', num2str(rmse_X2)], 'VerticalAlignment', 'top', 'HorizontalAlignment', 'right');

% Display RMSE values in the command window
disp(['Mean RMSE for X1: ', num2str(rmse_X1)]);
disp(['Mean RMSE for X2: ', num2str(rmse_X2)]);

%% Part C: Parameter sweep k3
k3_vect = 0:2:50; % set up k3 vector for values between 0 to 50 increasing by 2
TOL = 0.1; % define the tolerance

% define empty matrices used to store k3 that satisfy different conditions
case2_array = []; 
case1_array = [];
bothCase_array = [];

% Plot the dynamic behaviour of the system over time
figure;
for i = 1:length(k3_vect)
    hold on
    % use ode45 method to solve the equations with different k3
    [t_ode_1,x_ode_1] = ode45(@(t1,x1)odeMethod(t1,x1,k1,k2,k3_vect(i),k4,k5),tspan,[X1_0 X2_0]);
    for j = 1:length(x_ode_1)
        case2 = x_ode_1(j,1) <= 0+TOL && x_ode_1(j,1) >= 0; % define case 1
        case1 = x_ode_1(j,2) <= 2+TOL && x_ode_1(j,2) >= 2-TOL; % define case 2
        IsPositive = all(x_ode_1(:) >= 0); % make sure solution does not drop below 0
        % the all all(x_ode_1(:) >= 0) will return false if any element in
        % the whole array is negative
    end

    if(case2 && ~case1 && IsPositive) % check if case 1 is met
        % plot dynamic behaviour of system
        plot(t_ode_1,x_ode_1(:,1),'r-.','DisplayName',sprintf('X1 k3 = %d',k3_vect(i))) % parasites
        plot(t_ode_1,x_ode_1(:,2),'r--','DisplayName',sprintf('X2 k3 = %d',k3_vect(i))) % food
    elseif(~case2 && case1 && IsPositive) % check if case 2 met
        plot(t_ode_1,x_ode_1(:,1),'b-.','DisplayName',sprintf('X1 k3 = %d',k3_vect(i))) % parasite
        plot(t_ode_1,x_ode_1(:,2),'b--','DisplayName',sprintf('X2 k3 = %d',k3_vect(i))) % food
    elseif(case2 && case1 && IsPositive) % check if both cases are met
        plot(t_ode_1,x_ode_1(:,1),'g-.','DisplayName',sprintf('X1 k3 = %d',k3_vect(i))) % parasites
        plot(t_ode_1,x_ode_1(:,2),'g--','DisplayName',sprintf('X2 k3 = %d',k3_vect(i))) % food
    end

    % check which scenario k3 corresponds to and append it to appropriate
    % matrix
    if(~case2 && case1 && IsPositive)
       case2_array = cat(2,case2_array,k3_vect(i)); % concatenate case2 k3
    elseif(case2 && ~case1 && IsPositive) 
       case1_array = cat(2,case1_array,k3_vect(i)); % concatenate case1 k3
    elseif(case2 && case1 && IsPositive)
       bothCase_array = cat(2,bothCase_array,k3_vect(i)); % concatenate both case k3
    end
end
% plotting code for the trajectories
xlabel('time [units]');
ylabel('population size');
title('Parameter sweep of k3 plot trajectories')
lgd = legend;
lgd.Location = 'southoutside';
lgd.NumColumns = 5;
lgd.FontSize = 6;
hold off

% Ploting code for the number line representation of k3 values 
figure
hold on
plot(case1_array,zeros(length(case1_array),1),'r*', DisplayName= "case 1")
plot(case2_array,zeros(length(case2_array),1),'b*',DisplayName= "case 2")
plot(bothCase_array,zeros(length(bothCase_array),1),'g*',DisplayName= "Both cases satisified")
xticks(0:2:50);
set(gca,'ytick',[]) % remove y axis
set(gca,'yticklabel',[]) % remove y label
xlabel('k3 value')
title('Parameter sweep of k3 results')
legend

%% PART D //  parameter sweep k3 and k4
k3_vect = 0:2:50; % set up k3 vector for values between 0 to 50 increasing by 2
k4_vect = 0:2:50; % set up k4 vector for values between 0 to 50 increasing by 2
TOL = 0.1; % make sure tolerance is unchanged

% similar to part c set up empty arrays to store k3 and k4 values theat
% satisfy different cases
k3_case2 = [];
k3_case1 = [];
k3_case3 = [];
k4_case2 = [];
k4_case1 = [];
k4_case3 = [];

figure
for i = 1:length(k3_vect)
    hold on
    for ii = 1:length(k4_vect)
        [t_ode_1,x_ode_1] = ode45(@(t1,x1)odeMethod(t1,x1,k1,k2,k3_vect(i),k4_vect(ii),k5),tspan,[X1_0 X2_0]);
        for j = 1:length(x_ode_1)
            case1 = x_ode_1(j,1) <= 0+TOL && x_ode_1(j,1) >= 0; % define case 1
            case2 = x_ode_1(j,2) <= 2+TOL && x_ode_1(j,2) >= 2-TOL; % define case 2
            IsPositive = all(x_ode_1(:) >= 0); % make sure solution does not drop below 0
             % the all all(x_ode_1(:) >= 0) will return false if any element in
             % the whole array is negative
        end
    if(case2 && case1 && IsPositive)
        plot(t_ode_1, x_ode_1(:,1),'g');  % Plot X1
        plot(t_ode_1, x_ode_1(:,2),'g--');  % Plot X2
        % concatenate the successful values onto the respective arrays
        k3_case3 = cat(2,k3_case3,k3_vect(i));
        k4_case3 = cat(2,k4_case3,k4_vect(ii));
    elseif(case2 && ~case1 && IsPositive)
        plot(t_ode_1, x_ode_1(:,1),'b');  % Plot X1
        plot(t_ode_1, x_ode_1(:,2),'b-');  % Plot X2
        % concatenate the successful values onto the respective arrays
        k3_case2 = cat(2,k3_case2,k3_vect(i));
        k4_case2 = cat(2,k4_case2,k4_vect(ii));
    elseif(~case2 && case1 && IsPositive)
        plot(t_ode_1, x_ode_1(:,1),'r');  % Plot X1
        plot(t_ode_1, x_ode_1(:,2),'r-');  % Plot X2
        % concatenate the successful values onto the respective arrays
        k3_case1 = cat(2,k3_case1,k3_vect(i));
        k4_case1 = cat(2,k4_case1,k4_vect(ii));
    end
    end
end

% plotting code
% Note a legend was not included in this plot because it would have too many
% entries for MATLAB to handle
xlabel('time [units]');
ylabel('population size');
title('Independent parameter sweep of k3 & k4 plot trajectories')
hold off

% scatter plot to show k values corresponding to different cases
figure
hold on
scatter(k3_case1,k4_case1,'blue','*',DisplayName= "case 1 satisified")
scatter(k3_case2,k4_case2,'red','*',DisplayName= "case 2 satisified")
scatter(k3_case3,k4_case3,'green','*',DisplayName= "Both cases satisified")
xticks(-2:2:52);
yticks(-2:2:52);
xlabel('k3 value')
ylabel('k4 value')
lgd = legend;
lgd.Location = 'southoutside';
lgd.NumColumns = 3;
lgd.FontSize = 8;
title('Scatter plot for Parameter sweep of k3 and k4')

%% Functions

% Eulers Method function
function [t,X1,X2] = EulerMethod(X0_1,X0_2,k3,k4,h,T)
steps = T/h; % calculate the number of steps for the simulation
t = 0; % set start time to 0
X1 = X0_1; % intialise X1 vector
X2 = X0_2; % intialise X2 vector
for i = 1:steps
    t(i+1) = t(i)+h; % increment time
    X1(i+1) = X1(i)*(1+h*(X2(i)-2)); % solve for X1 at t+h
    X2(i+1) = X2(i)*(1-h*k4) + h*(k3-3*X1(i)); % solve for X2 at t+h
    %equations derived from part a
end
end

% ode solver function for ODE45 implementation
function odeSystem = odeMethod(t, x, k1,k2,k3,k4,k5)
X1 = x(1); % intialise X1
X2 = x(2); % intialise X2
dX1dt = k1*X1*X2 - k2*X1; % solve for dX1 using given equations
dX2dt = k3-k4*X2-k5*X1; % solve for dX2 using given equations
odeSystem = [dX1dt;dX2dt]; % return as matrix
end




