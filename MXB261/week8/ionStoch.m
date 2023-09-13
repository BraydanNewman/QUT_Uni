function [countC, countP] = ionStoch(k1,k2, C0, N, T, M)
    countC = zeros(M,1);
    countP = zeros(M,1);
    for j = 1:M
        ti = 0;
        counter = 1;
    
        C(1) = C0;
        P(1) = N - C0;
    
        while ti < T
    
            q1 = k1*C(counter);
            q2 = k2*P(counter);
            r = q1 + q2;
    
            u1 = rand();
    
            deltaT = -log(u1)/r;
            ti = ti + deltaT;
    
            u2 = rand();
            if u2 < q1/r
                C(counter + 1) = C(counter) - 1;
                P(counter + 1) = P(counter) + 1;
            else
                C(counter + 1) = C(counter) + 1;
                P(counter + 1) = P(counter) - 1;
            end
            counter = counter + 1;
        end
        countC(j) = C(end);
        countP(j) = P(end);
        
        plot(C)
        hold on
        plot(P)
    end
end