
%Parameters
Tol = 0.1;
tspan = [0 20]; 
time_grid = linspace(0, 30, 100);
initX = [1; 1]; %Initial Populations   
k1 = 1; %Parasite Birth Rate
k2 = 2; %Parasite Death Rate 
num_samples = 25000; 
param_ranges = [0 50; 
                0 50; 
                0 50]; 
rng(4007)
                
% Generating Latin Hypercube Samples
lhs = lhs_3d(num_samples, param_ranges);
param_samples = zeros(num_samples, 3);

for i = 1:3
    param_samples(:, i) = lhs(:, i);
end


% Loop through all the LHS samples and simulate the ODEs
both_conditions = [];
unsuccessful_samples = [];
X1_conditions = [];
X2_conditions = [];
pop_ends=[];
for i = 1:num_samples
    k3 = param_samples(i, 1);
    k4 = param_samples(i, 2);
    k5 = param_samples(i, 3);

    params = [k3 k4 k5];
    [t, X] = ode45(@(t, y) parasiteModel(t, y, k1, k2, k3, k4, k5), tspan, initX);
    X1 = X(:, 1);
    X2 = X(:, 2);
    X1_end = X1(end);
    X2_end = X2(end);

     % Success Conditions
     condition_X1 = (0 <= X1_end) && (X1_end <= Tol);
     condition_X2 = (2 - Tol <= X2_end) && (X2_end <= 2 + Tol);
     condition_all_positive_pops = all(X1 >= 0) && all(X2 >= 0);

      % Store Sample
      if (condition_X1 || condition_X2) && condition_all_positive_pops
          if(condition_X1 && condition_X2)
            both_conditions = [both_conditions; params];
          elseif(condition_X1)
            X1_conditions = [X1_conditions; params];
          elseif(condition_X2)
            X2_conditions = [X2_conditions; params];
          end
          pop_ends = [pop_ends; params X1_end X2_end condition_X1 condition_X2];
      else
          unsuccessful_samples = [unsuccessful_samples; params];
      end

end

% Create a 3D scatter plot
figure('Color', 'w', 'Position', [100, 100, 800, 600]);
hold on; 

% Plot both conditions samples in green
scatter3(both_conditions(:,1), both_conditions(:,2), both_conditions(:,3), ...
    50, 'g', 'filled', 'MarkerEdgeColor', 'k'); % Adjusted size and added edge color

% Plot X1 condition samples in red
scatter3(X1_conditions(:,1), X1_conditions(:,2), X1_conditions(:,3), ...
    50, 'r', 'filled', 'MarkerEdgeColor', 'k'); % Adjusted size and added edge color

% Plot X2 conditions samples in blue
scatter3(X2_conditions(:,1), X2_conditions(:,2), X2_conditions(:,3), ...
    50, 'b', 'filled', 'MarkerEdgeColor', 'k'); % Adjusted size and added edge color



% Labels and title
xlabel('Rate of Food Growth(k3)', 'FontSize', 14);
ylabel('Rate of Food Decay(k4)', 'FontSize', 14);
zlabel('Rate of Parasite Food Consumption (k5)', 'FontSize', 14);
title('LHS Succesful Paramater Samples', 'FontSize', 16);

% Legend
legend('Both Cases Satisfied', 'Case 1', 'Case 2', 'Location', 'southoutside', 'FontSize', 12);

% Adjusting legend position
set(gca, 'Position', [0.1, 0.3, 0.8, 0.6]);
legendPos = get(legend, 'Position'); 
legendPos(2) = legendPos(2) - 0.08;  
set(legend, 'Position', legendPos);  

% Grid, Box, and view angle
grid on;
box on;
view(45, 25);

hold off;

