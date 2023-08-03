%% Pi Shit 
diff = 1;

i = 1;
x = 1;

ap_pi_1 = (4 * (((-1)^0) * (x ^ (2 * 0 + 1) / (2 * 0 + 1))));
ap_pi_2 = ((1/(16^0))*((4/(8*0 + 1))-(2/(8*0 + 4))-(1/(8*0 + 5))-(1/(8*0 + 6))))


while diff > 10E-6
    ap_pi_1 = ap_pi_1 + (4 * (((-1)^i) * (x ^ (2 * i + 1) / (2 * i + 1))));

    ap_pi_2 = ap_pi_2 + ((1/(16^i))*((4/(8*i + 1))-(2/(8*i + 4))-(1/(8*i + 5))-(1/(8*i + 6))));

    diff = abs(ap_pi_1 - ap_pi_2);
    
    i = i + 1;
end

format long
pi
ap_pi_2
ap_pi_1

%% Plotting Shapes

x = -1:0.0001:1;
y = sqrt(1-x.^2);
hold on

plot([0 x 0], [0 y 0], 'LineWidth', 5);

x = -1:0.02:1;
y = 0:0.01:1;

for x1 = x
    for y1 = y
        if x1^2 + y1^2 < 1^2
            plot(x1, y1, ".g", 'MarkerSize',20);
        else
            plot(x1, y1, ".r", 'MarkerSize',20);
        end
    end
end

