clear all

figure
clf
hold on
box on

GBRMPA_OUTLINE = [
    142.5 -10.7;
    145.0 -10.7;
    145.0 -13.0;
    147.0 -17.5;
    153.0 -21.0;
    154.0 -24.5;
    152.0 -24.5
]

load AustOutline_MXB362
pt = patch(Outline(:,1), Outline(:,2), [0.8 0.8 0.8]);
set(pt, 'facecolor', [1 0.9 0.65])

load ReefOutline_MXB362 
plot(ReefRaw(:,1), ReefRaw(:,2), 'b')

load GreenZones_MXB362
NumZone = length(GreenOutline);
for a = 1:NumZone
    pt = patch(GreenOutline{a}(1,:), GreenOutline{a}(2,:), 'g');
    set(pt, 'edgecolor', 'none', 'facealpha', 0.5)
end

plot(GBRMPA_OUTLINE(:,1), GBRMPA_OUTLINE(:,2), 'r', 'LineWidth', 1.5)

set(gca, 'color', [0.94 1, 1])
text(145, -21, 'Queensland', 'FontSize', 17)
T = text(149.8, -18.74, 'GBRMP Boundry', 'FontSize', 12);
set(T, 'fontangle', 'italic', 'color', 'r')
set(T, 'rotation', -18)

xlim([142.3 154.5])
ylim([-26 -9])

axes('Position', [0.15 0.12 0.2 0.1])
axis equal; 
hold on
patch(Outline(:,1), Outline(:,2), [1 1 1]);
pt = patch([142.3, 154.5 154.5 142.3], [-26 -26 -9 -9], [0 0 0]);
set(pt, 'facealpha',0.2)
axis off