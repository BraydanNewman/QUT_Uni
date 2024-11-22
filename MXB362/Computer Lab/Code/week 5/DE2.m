function dxdt = DE2(t,x)

global g L

dxdt = [x(2); -g/L*sin(x(1))];

end

