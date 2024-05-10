function ode = parasiteModel(t, X, k1, k2, k3, k4, k5)
    X1 = X(1);
    X2 = X(2);
    ode = zeros(2,1);
    ode(1) = k1*X1*X2 - k2*X1;  % dX/dt
    ode(2) = k3 - k4*X2 - k5*X1; % dX2/dt
end

