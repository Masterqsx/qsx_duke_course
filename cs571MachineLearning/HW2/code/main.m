clc
clear
M = csvread('dataset.csv',1,0);
label = M(:, 4);
train = M(:, 1:3);
theta = [0.05 ; -3 ; 2.5];
cons = 0.3;

linear_decision = linear_c(theta, train', cons);
[P_linear, R_linear, F1_linear, Confusion_linear, threshold_linear, threshold_linear_range] = find_t(linear_decision, label);

nonlinear_decision = nonlinear_c(theta, train', cons);
[P_nonlinear, R_nonlinear, F1_nonlinear, Confusion_nonlinear, threshold_nonlinear, threshold_nonlinear_range] = find_t(nonlinear_decision, label);
AUC_nonlinear = plotROC(nonlinear_decision(label == 0), nonlinear_decision(label == 1));
title('f(x) ROC curve');
legend(['ROC curve of f(x) :',num2str(AUC_nonlinear)]);
grid on;