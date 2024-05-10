function samples = orthogonal_lhs_3d(n, param_ranges)
    P = size(param_ranges, 1);
    
    % Find midpoints for each parameter
    midpoints = mean(param_ranges, 2);
    
    % Find intervals for each parameter, to divide into 8 sectors
    intervals = [param_ranges(:,1), midpoints, param_ranges(:,2)];
    
    % Determine samples per sector
    samples_per_sector = floor(n / 8);
    
    % Determine how many sectors need an extra sample to make up n
    extra_samples = mod(n, 8);
    
    samples = zeros(n, P);
    
    index = 1;
    
    % Loop through 8 sectors
    for i = 1:2
        for j = 1:2
            for k = 1:2
                % Define sub-ranges for each parameter
                sub_ranges = [intervals(1, i), intervals(1, i+1); ...
                              intervals(2, j), intervals(2, j+1); ...
                              intervals(3, k), intervals(3, k+1)];
                
                % Define samples for this sector
                if extra_samples > 0
                    samples_this_sector = samples_per_sector + 1;
                    extra_samples = extra_samples - 1;
                else
                    samples_this_sector = samples_per_sector;
                end
                
                % find Sub sample values of the secootr
                sub_samples = lhs_3d_sub(samples_this_sector, sub_ranges, samples_per_sector);
                
                % Add to the main sample matrix
                samples(index:index+samples_this_sector-1, :) = sub_samples;
                
                % Update sample index
                index = index + samples_this_sector;
            end
        end
    end
end

function sub_samples = lhs_3d_sub(n, sub_ranges, mesh_size)
    P = size(sub_ranges, 1);
    sub_samples = zeros(n, P);
    for i = 1:P
        min = sub_ranges(i, 1);
        max = sub_ranges(i, 2);
        intervals = linspace(min, max, mesh_size +1);
        for j = 1:mesh_size
            sub_samples(j, i) = intervals(j) + rand * (intervals(j+1) - intervals(j));
        end
        sub_samples(:, i) = sub_samples(randperm(n), i);
    end
end