niter = 300;

x0 = 0.370;
x1 = 0.371;
y0 = -0.362;
y1 = -0.363;

res = 2000;
X = linspace(x0,x1,res);
Y = linspace(y0,y1,res);
[x,y] = meshgrid(X,Y);

c = x + 1i * y;

z = zeros(size(c));
k = zeros(size(c));

for ii = 1:niter
    z = z.^ 2 + c;

    k(abs(z) > 2 & k == 0) = niter - ii;
end


figure(4), clf
colormap hot
imagesc(X,Y,k);
axis square
set(gca, 'xtick',[],'ytick',[])