function [results] = ball_drop(s, w, e, N, P)
    start_y = 99;
    game_board = zeros(99, 99);
    
    for ball_index = 1:N

        if P == "rand"
            start_x = randi([1, 99]);
        elseif P == "1"
            start_x = 50;
        end

        current_x = start_x;
        current_y = start_y;
    
        next_x = current_x;
        next_y = current_y;
    
        stopped = false;
    
        while ~stopped
            u = rand;
            if u < w
    %             LEFT    
                temp = current_x - 1;
                if temp < 1
                    temp = 99;
                end
    
                if game_board(temp, current_y) ~= 1
                    next_x = temp;
                end
            elseif u < w + e
    %             RIGHT
                temp = current_x + 1;
                if temp > 99
                    temp = 1;
                end
    
                if game_board(temp, current_y) ~= 1
                    next_x = temp;
                end
            elseif u < w + e + s
    %             DOWN
                next_y = current_y - 1;
                if game_board(next_x, next_y) == 1 || next_y == 1
                    game_board(current_x, current_y) = 1;
                    stopped = true;
                end
            end
            current_x = next_x;
            current_y = next_y;
        end
    end

    results = zeros(1, 99);
    for i = 1:99
        results(i) = sum(game_board(i,:));
    end

end
