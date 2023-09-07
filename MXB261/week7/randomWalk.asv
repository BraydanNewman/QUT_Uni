function [total_particals] = randomWalk(steps, particals_pos, number_of_particals, grid_size)
    total_particals = zeros(steps + 1, 1);
    total_particals(1) = number_of_particals;

    health = zeros(number_of_particals, 1);

    for i = 1:steps
        u = rand(size(particals_pos, 1),1);
        
        % Move all particals
        particals_pos(u <= 0.25, 2) = particals_pos(u <= 0.25, 2) - 1; % South
        particals_pos(u <= 0.5 & u > 0.25 , 1) = particals_pos(u <= 0.5 & u > 0.25 , 1) + 1; % East
        particals_pos(u <= 0.75 & u > 0.5, 2) = particals_pos(u <= 0.75 & u > 0.5, 2) + 1; % North
        particals_pos(u > 0.75, 1) = particals_pos(u > 0.75, 1, 1) + 1; % West
        
        % No Wrap Boundry
        particals_pos(particals_pos < 1) = 1;
        particals_pos(particals_pos > grid_size) = grid_size;
        


%         [~, ~, index] = unique(particals_pos(:, 1:2)) ;


        [~, ~, j] = unique(particals_pos(:, 1:2), 'first')

        dups = 


%         indexToDupes = find(not(ismember(1:numel(particals_pos),j)))


        
        damage = rand();
        
        health(index) = health(index) - damage;


        particals_pos = particals_pos(health > 0);
        health = health(health > 0);

        

        
        total_particals(i + 1) = size(particals_pos, 1);

%         scatter(particals_pos(:,1), particals_pos(:,2), 40, "filled", 'b')
%         ylim ([0.5, grid_size + 0.5])
%         pause(0.2)
    end
end