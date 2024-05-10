function samples = lhs_3d(n, param_ranges)
    P = size(param_ranges, 1);  % Number of parameters
    
    samples = zeros(n, P);
    
    % Loop for each parameter
    for i = 1:P
        % Get the parameter range
        min = param_ranges(i, 1);
        max = param_ranges(i, 2);
        
        % Create a vector of n evenly spaced intervals within the parameter range
        intervals = linspace(min, max, n+1);
        
        % Generate a random value within each interval
        for j = 1:n
            samples(j, i) = intervals(j) + rand * (intervals(j+1) - intervals(j));
        end
        
        % Randomly permute the generated values
        samples(:, i) = samples(randperm(n), i);
    end
end