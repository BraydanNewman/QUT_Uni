function dydt = ionChannelFn(t,y,k1,k2)
    C = y(1);
    P = y(2);
    
    dCdt = -k1*C+k2*P;
    dPdt = k1*C-k2*P;

    dydt = [dCdt;dPdt];
end