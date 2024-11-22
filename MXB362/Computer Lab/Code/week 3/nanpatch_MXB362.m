function P = nanpatch_MXB362(XX,YY,CL)

F = [0 find(isnan(XX))];
for f = 1:length(F)-1
    XXX = XX(F(f)+1:F(f+1)-1);
    YYY = YY(F(f)+1:F(f+1)-1);
    
    P = patch(XXX,YYY,CL);
    set(P,'edgecolor',0.8.*ones(1,3));
end
