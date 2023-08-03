function [avgArea, areaError] = areaCircle(N,M)
    xc = 0.5;
    yc = 0.5;

    r = 0.5;

    areaExact = pi * r^2;

    countTotal = 0;

    for m = 1:M
        u = rand(N, 1);
        v = rand(N, 1);

        t = (u - xc).^2 + (v - yc).^2 < r^2;
        inCircle = sum(t);
        areaEstimate = inCircle / N;
        countTotal = countTotal + areaEstimate;
    end
    avgArea = countTotal / M;
    areaError = abs(areaExact - avgArea);
end