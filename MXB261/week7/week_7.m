simulations = 500;
grid_size = 100;
number_of_particals = 2;
steps = 200;

particals_pos = randi([1, grid_size], number_of_particals, 3);
particals_pos(:, 3) = 1;

data_simulation = zeros(steps + 1, simulations);

for i = 1:simulations
    data_simulation(:, i) = randomWalk(steps, particals_pos, number_of_particals, grid_size);
end

%%
% figure, plot(data_simulation(:, 1), "LineWidth", 2)

%%
% figure, plot(data_simulation(:, 1:50), "LineWidth", 2)

%%
% figure, plot(data_simulation(:, :), "LineWidth", 2)

%%
figure, plot(mean(data_simulation, 2), 'LineWidth', 2)
hold on
yline(number_of_particals/2, 'red')

