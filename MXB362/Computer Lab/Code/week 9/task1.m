clear all

RecordAnimation = 1;
filename = 'reefAnimation.gif';

f = figure(1);
clf, hold on, box on

load AustOutline_MXB362
pt = patch(Outline(:,1),Outline(:,2),[0.8 0.8 0.8]);
set(pt, 'facecolor', [1 0.9 0.65])

load ReefOutline_MXB362
plot(ReefRaw(:,1),ReefRaw(:,2),'b')

xlim([148.5 155])
XL = xlim;
ylim([-25.5 -19.5]);
YL = ylim;
set(gca,'color',[0.94 1 1])

load LarvalReleases_MXB362

for k = 1:914
    h = convhull(ER_traj_x(:,k), ER_traj_y(:,k));
    P(1) = plot(ER_traj_x(:,k),ER_traj_y(:,k),'.','MarkerSize',2,'Color',[0 0.5 0]);
    P(2) = plot(ER_traj_x(h,k),ER_traj_y(h,k), 'Color','red', 'LineWidth',2);
    
    if RecordAnimation == 1
        frame = getframe(f);
        im = frame2im(frame);
        [imind,cm] = rgb2ind(im,256);

        if k == 1
            imwrite(imind,cm,filename,'gif','LoopCount',inf);
        else
            imwrite(imind,cm,filename,'gif','WriteMode','append',"DelayTime",0.02);
        end
    end

    drawnow

    if k < 914
        delete(P)
    end
end