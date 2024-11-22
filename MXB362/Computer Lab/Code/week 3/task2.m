clear all

N = 0.3;

figure(1), clf

r = 2.2;
subplot(3, 1, 1), box on
for t = 1:99
    N(t+1) = r*N(t)*(1 - N(t));
end
plot([1:100], N, 'LineWidth',2);
xlim([1 100]); ylim([0 1.1])
title(["Growth Rate = " num2str(r,3)])

r = 3.2;
subplot(3, 1, 2), box on
for t = 1:99
    N(t+1) = r*N(t)*(1 - N(t));
end
plot([1:100], N, 'LineWidth',2);
xlim([1 100]); ylim([0 1.1])
title(["Growth Rate = " num2str(r,3)])

r = 4.0;
subplot(3, 1, 3), box on
for t = 1:99
    N(t+1) = r*N(t)*(1 - N(t));
end
plot([1:100], N, 'LineWidth',2);
xlim([1 100]); ylim([0 1.1])
title(["Growth Rate = " num2str(r,3)])



figure(2), clf, hold on, box on;

r_list = linspace(2.5,3.8,1500);
XX = [];
YY = [];

for i = 1:length(r_list)
    N=0.3
    r = r_list(i)

    for t = 1:1000
        N(t+1) = r*N(t)*(1-N(t));
    end

    Y = N(800:end);
    X = ones(size(Y))*r;

    XX = [XX X];
    YY = [YY Y];
end

plot(XX, YY, '.', 'MarkerSize',1)
xlabel('Growth rate (r)')
ylabel('Population (N)')
title("Bifurcation Diagram")
xlim([2.8 3.8]);
ylim([0 1.1])