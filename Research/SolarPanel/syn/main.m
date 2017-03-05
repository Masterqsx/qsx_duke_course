clc
clear

Ntrain = mnrnd(1000000, [0.97, 0.03]);
Ntrain0 = Ntrain(1);
Ntrain1 = Ntrain(2);
Htrain0 = normrnd(0, 0.1, Ntrain0, 1);
Htrain1 = normrnd(1, 0.4, Ntrain1, 1);
DsTrain = [Htrain0, zeros(Ntrain0, 1);Htrain1, ones(Ntrain1, 1)];

histogram(DsTrain(DsTrain(:, 2) == 0, 1), 100);
hold on;
histogram(DsTrain(DsTrain(:, 2) == 1, 1), 100);
hold off;
xlabel('Decision Statistics', 'FontWeight', 'bold', 'fontsize', 14);
ylabel('Numbers of Values', 'FontWeight', 'bold', 'fontsize', 14);
title('The Distribution of Synthetic Dataset', 'FontWeight', 'bold', 'fontsize', 14);
legend('\fontsize {12}{\bfH_0}', '\fontsize {12}{\bfH_1}')
figure
methodCompare(DsTrain, DsTrain)