clear all

figure(1)
clf
hold on
box on
grid on
view(3)

for a = 1:30
    pt = patch([0 1 1 0]/a,[0 0 1 1]/a,a*[1 1 1 1], 'b');
    set(pt, 'facealpha',a/30)
end

axis vis3d
set(gca, 'xtick',[],'ytick',[],'ztick',[])
for t = 1:360
    view([t,30])
    pause(0.01)
end