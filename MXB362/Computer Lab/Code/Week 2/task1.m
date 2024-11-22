% 

clear all

load ML_CO2_data

figure(1)
clf

subplot('position', [0.1, 0.07, 0.85, 0.15])

hold on
box on

pp = plot(Data(:,3), Data(:,4));

xlabel('Year', 'FontSize', 15);
ylabel('ppm CO_2', 'FontSize', 15);

xlim([1958, 2020])
ylim([310, 415])

subplot('position', [0.1, 0.3, 0.85, 0.65])

hold on 
box on
pp = plot(Data(:,3), Data(:,4));

xlabel('Year', 'FontSize', 15);
ylabel('Atmosperic CO_2 Concetration (ppm)', 'FontSize', 15)

title('Atmosperic CO_2 Concetration at Mauna Loa','FontSize',16)
L = legend('Mauna Loa monthly avrages');
set(L, 'fontsize', 14, 'location', 'northwest')

xlim([1958, 2020])
ylim([310, 415])