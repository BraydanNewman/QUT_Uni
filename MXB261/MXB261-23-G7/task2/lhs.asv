function [samples] = lhs(col_row_n)
%     Setup arrays and values for LHS
    samples = zeros(2, col_row_n);
    
    taken_x = zeros(1, col_row_n);
    taken_y = zeros(1, col_row_n);

    bin_width = 1/col_row_n;
    
%     Loop for all samples
    for i = 1:col_row_n
%         Find place for x dimension of sample
        x_not_used = true;
        while x_not_used
            x = rand();
            x_index = fix(x/bin_width) + 1;
            if taken_x(x_index) == 0
                x_not_used = false;
                taken_x(x_index) = 1;
            end
        end

%         Find place for y dimension of sample
        y_not_used = true;
        while y_not_used
            y = rand();
            y_index = fix(y/bin_width) + 1;
            if taken_y(y_index) == 0
                y_not_used = false;
                taken_y(y_index) = 1;
            end
        end
        samples(1, i) = x;
        samples(2, i) = y;
    end
end
