%% Plot 1
subplot(2,2,1)
[results] = ball_drop(1/3, 1/3, 1/3, 100, "1");
bar(results)
title('Subplot 1')

subplot(2,2,2)
[results] = ball_drop(2/3, 1/6, 1/6, 100, "1");
bar(results)
title('Subplot 2')

subplot(2,2,3)
[results] = ball_drop(3/5, 3/10, 1/10, 100, "1");
bar(results)
title('Subplot 3:')

subplot(2,2,4)
[results] = ball_drop(3/5, 1/10, 3/10, 100, "1");
bar(results)
title('Subplot 4')

%% Plot 2
subplot(2,2,1)
[results] = ball_drop(1/3, 1/3, 1/3, 200, "1");
bar(results)
title('Subplot 1')

subplot(2,2,2)
[results] = ball_drop(2/3, 1/6, 1/6, 200, "1");
bar(results)
title('Subplot 2')

subplot(2,2,3)
[results] = ball_drop(3/5, 3/10, 1/10, 200, "1");
bar(results)
title('Subplot 3:')

subplot(2,2,4)
[results] = ball_drop(3/5, 1/10, 3/10, 200, "1");
bar(results)
title('Subplot 4')

%% Plot 3
subplot(2,2,1)
[results] = ball_drop(1/3, 1/3, 1/3, 100, "rand");
bar(results)
title('Subplot 1')

subplot(2,2,2)
[results] = ball_drop(2/3, 1/6, 1/6, 100, "rand");
bar(results)
title('Subplot 2')

subplot(2,2,3)
[results] = ball_drop(3/5, 3/10, 1/10, 100, "rand");
bar(results)
title('Subplot 3:')

subplot(2,2,4)
[results] = ball_drop(3/5, 1/10, 3/10, 100, "rand");
bar(results)
title('Subplot 4')

%% Plot 4
subplot(2,2,1)
[results] = ball_drop(1/3, 1/3, 1/3, 200, "rand");
bar(results)
title('Subplot 1')

subplot(2,2,2)
[results] = ball_drop(2/3, 1/6, 1/6, 200, "rand");
bar(results)
title('Subplot 2')

subplot(2,2,3)
[results] = ball_drop(3/5, 3/10, 1/10, 200, "rand");
bar(results)
title('Subplot 3:')

subplot(2,2,4)
[results] = ball_drop(3/5, 1/10, 3/10, 200, "rand");
bar(results)
title('Subplot 4')