function [KLD1, KLD2, X, b, X1,b1] = sampling(bin, N)
    % Set Up
    load("sampledata2023.mat");
    
    figure(1)
    h = histogram(Data0, bin);
    b = h.Values / length(Data0);
    c = cumsum(b);
    X = h.BinEdges(1:bin)+h.BinWidth/2;
    
    rng(4)
    DataNew = zeros(1, N);
    for i = 1:N
        u = rand;
        index = find(c>u,1);
        DataNew(1,i) = X(index);
    end
    
    figure(2)
    h1 = histogram(DataNew, bin);
    
    b1 = h1.Values / length(Data0);
    X1 = h1.BinEdges(1:bin)+h1.BinWidth/2;
    
    KLD1 = 0;
    for i = 1:bin
        KLD1 = KLD1 + b(i) * log(b(i)/b1(i));
    end
    
    KLD2 = 0;
    for i = 1:bin
        KLD2 = KLD2 + b1(i) * log(b1(i)/b(i));
    end
end