x = linspace(0, 1, 100);

figure

hold on

a = plot([0 0 1 1 0], [0 1 1 0 0], "k", "LineWidth", 2);
b = plot(x, 0.5-sqrt(0.5 ^ 2 - (x - 0.5).^2), "LineWidth", 2, "Color", [0, 0.5, 1]);
plot(x, 0.5+sqrt(0.5 ^ 2 - (x - 0.5).^2), "LineWidth", 2, "Color", [0, 0.5, 1]);


axis equal
axis square

xlabel("x")
ylabel("y")

xlim([0 1.2])
ylim([0 1.2])

legend([a, b], ["Unit Circle", "Circle"]);
set(gca, "fontsize", 12)

%%
N = 1E6;
M = 1E6;
[circleArea, areaError] = areaCircle(N, M)