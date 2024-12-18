clear all

load USA_County_struct
load USA_State_struct

[D, T] = xlsread("Geocoded_MethLabs.xlsx");
Loc = [D(:,11) D(:,10)];

% TASK 1 A

figure(1); clf, hold on; box on;

for s = 1:length(S)
    XX = S(s).X;
    YY = S(s).Y;

    plot(XX, YY, 'Color',0.8.*ones(1,3))
end

ml = plot(Loc(:,1),Loc(:,2),'r.','MarkerSize',4);

FS = 16;
title('Locations of Methamphetamine Laboratories', 'FontSize', FS);
text(-124,24.3,'Source: DEA National Clandestine Laboratories Register', 'FontSize',FS);

set(gca, 'xtick',[],'ytick',[]);
xlim([-126 -66])
ylim([23.3 50])



% Task 1 B

figure(2), clf, hold on; box on

CL = hot(3200);

CL = CL(end:-1:1,:);

for s = 1:length(S_states)

    XX = S_states(s).X;
    YY = S_states(s).Y;

    LabsInThisState(s) = sum(inpolygon(Loc(:,1),Loc(:,2),XX,YY));

    ThisColor = ceil(LabsInThisState(s))+1;
    
    nanpatch_MXB362(XX,YY,CL(ThisColor,:));
end

set(gca, 'xtick',[],'ytick',[]);
xlim([-126 -66])
ylim([23.3 50])

FS = 16;

colormap(CL)
c = colorbar;
title('Number of Methamphetamine Laboratories in each state', 'FontSize',FS);
set(c, 'Ticks', linspace(0,1,9),'ticklabels',linspace(0,3200,9),'FontSize', FS-2);

