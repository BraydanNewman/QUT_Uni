clear all

load Underground_station_data_MXB362

h = figure(1); clf

A2 = axes('Position',[0.1 0.7 0.3 0.25], 'Color',0.3.*ones(1,3));
box on
hold on

xlim([0 24]);
ylim([0 2])
set(gca, 'xtick',0:2:24,'color',0.3*ones(1,3))
xlabel('Hour', 'FontSize', 19, 'Color',1.*ones(1,3))
ylabel('Trips (x 1000)', 'FontSize',19, 'Color',1.*ones(1,3))

A1 = axes('Position',[0.0 0.0 1 1]);
hold on

load London_road_water_data_MXB362

plot3(Rx1,Ry1,zeros(size(Rx1)),'Color',0.4.*ones(1,3),'LineWidth',1)
plot3(Rx2,Ry2,zeros(size(Rx2)),'Color',0.4.*ones(1,3),'LineWidth',1)

for i = 1:length(Thames_river)
    ptch = patch(Thames_river{i}(:,1),Thames_river{i}(:,2), 'b');
    set(ptch, 'edgecolor', 'none', 'linewidth', 2, 'facealpha', 0.7, 'BackFaceLighting', 'unlit');
end

set(gcf, 'color', 0.1.*ones(1,3))
set(gca, 'color', 0.1.*ones(1,3))

axis off

view([-13.5 30]);
zlim([0 5000])
xlim([-0.5 0.33])
ylim([51.28 51.70])
[Xc,Yc,Zc] = cylinder(4e-3,4);

vidObj = VideoWriter('LondonUnderGround.avi', 'Motion JPEG AVI');
vidObj.FrameRate = 10;
vidObj.Quality = 95;
open(vidObj);

camlight

TotalPassengers = 0;

for t = 1:96
    axes(A1);
    for i = 1:size(Station_data,1)
        ss(i) = surf(Xc+Station_data{i,2},Yc+Station_data{i,3},Zc.*Station_data{i,t+3});
        set(ss(i), 'edgecolor', 'none', 'facecolor',[1 0.6 0.6], 'facealpha', 1, 'SpecularColorReflectance', 0.5)
    end

    axes(A2);
    TotalPassengers = [TotalPassengers 1e-5.*sum([Station_data{:,t+3}])];

    plot(24.*[t-1 t]./100, [TotalPassengers(t) TotalPassengers(t+1)], 'w', 'LineWidth',2)

    currFrame = getframe(h);
    writeVideo(vidObj, currFrame);
    disp(t);
    delete(ss);
    clear ss
end

close(vidObj);