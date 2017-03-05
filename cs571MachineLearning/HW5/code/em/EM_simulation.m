clc
clear

m = 5;
n = 100;
theta = [0.8, 0.35];

data = [];
for i = 1:m
    class = find(mnrnd(1, [0.5, 0.5]));
    temp = mnrnd(n, [theta(class), 1 - theta(class)]);
    data(i) = temp(1);  
end

[thetaA, thetaB] = em(data, 0.4, 0.2, n);