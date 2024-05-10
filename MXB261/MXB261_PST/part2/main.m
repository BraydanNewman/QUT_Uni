%% Plot 1
bins = 20;
samples = 1000;
[KLD1, KLD2, X, b, X1,b1] = sampling(bins, samples);

KLD1
KLD2

subplot(1, 2, 1)
bar(X, b)
ylabel('Probability', 'FontSize', 20)
xlabel('Bins', 'FontSize', 20)
title('Given Data Probability Distribution', 'FontSize', 20)

subplot(1, 2, 2)
bar(X1, b1)
ylabel('Probability', 'FontSize', 20)
xlabel('Bins', 'FontSize', 20)
title('Sampled Data Probability Distribution', 'FontSize', 20)

sgtitle(["Sampling from Experimental Data", "Bins = 20, Samples = 1000"], 'FontSize', 25)

%% PLot 2
bins = 10;
samples = 1000;
[KLD1, KLD2, X, b, X1,b1] = sampling(bins, samples);

KLD1
KLD2

subplot(1, 2, 1)
bar(X, b)
ylabel('Probability', 'FontSize', 20)
xlabel('Bins', 'FontSize', 20)
title('Given Data Probability Distribution', 'FontSize', 20)

subplot(1, 2, 2)
bar(X1, b1)
ylabel('Probability', 'FontSize', 20)
xlabel('Bins', 'FontSize', 20)
title('Sampled Data Probability Distribution', 'FontSize', 20)

sgtitle(["Sampling from Experimental Data", "Bins = 10, Samples = 1000"], 'FontSize', 25)

%% Plot 3
bins = 40;
samples = 1000;
[KLD1, KLD2, X, b, X1,b1] = sampling(bins, samples);

KLD1
KLD2

subplot(1, 2, 1)
bar(X, b)
ylabel('Probability', 'FontSize', 20)
xlabel('Bins', 'FontSize', 20)
title('Given Data Probability Distribution', 'FontSize', 20)

subplot(1, 2, 2)
bar(X1, b1)
ylabel('Probability', 'FontSize', 20)
xlabel('Bins', 'FontSize', 20)
title('Sampled Data Probability Distribution', 'FontSize', 20)

sgtitle(["Sampling from Experimental Data", "Bins = 20, Samples = 1000"], 'FontSize', 25)
