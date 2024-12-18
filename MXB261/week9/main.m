%% E - 9.1.2
x = -2:0.2:2;
y = x.^3;
y2 = x.^3 -2*x.^2 + x + 1;
plot(x,y,'b',x,y2,'-.g','LineWidth',3)
xval1 = fzero('2*x^2-x-1',0);
yval1 = xval1^3;
xval2 = fzero('2*x^2-x-1',2);
yval2 = xval2^3;
text(xval1,yval1,tintersection \rightarrow','HorizontalAlignment','right')
text(xval2,yval2,'\downarrow intersection','VerticalAlignment','bottom')
legend('y=x^3','y=x^3-2x^2+x+1')

%% E - 9.1.3
z = peaks;
mesh(z)
colormap("spring")
colorbar

%% E - 9.1.4
z = peaks;
subplot(2,2,1)
surf(z)
shading faceted
title('shading faceted')
subplot(2,2,2)
surf(z)
shading flat
title('shading flat')
subplot(2,2,3)
surf(z)
shading interp
title('shading interp')

%% 
