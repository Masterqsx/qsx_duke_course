clc
clear

%% q1
range = linspace(-10, 10, 1000);
res1 = log(1 + exp(-range))/log(2);
res2 = max(0, 1 - range);
figure
plot(range, res1);
hold on;
plot(range, res2);
plot(-10:0.1:0, ones(length(-10:0.1:0), 1), zeros(length(0:0.1:1), 1), 0:0.1:1);
grid on;
hold off;
title('Comparison between hinge loss and logistic loss');
xlabel('x');
ylabel('loss');
legend('logistic loss', 'hinge loss', '0-1 loss');
%% synthetic data generation
mu1 = [1, 1];
mu0 = [-1, -1];
sigma1 = [0.1, 0;0, 0.1];
sigma0 = [0.1, 0;0, 0.1];
data0 = mvnrnd(mu0, sigma0, 100);
data1 = mvnrnd(mu1, sigma1, 100);
trainData = [data0 ; data1];
trainLabel = [-ones(100, 1);ones(100, 1)];

%% creditCard data generation
load('creditCard.mat');
creditCard_data = double(creditCard);
creditCard_sample = creditCard_data(:, 1:(size(creditCard_data, 2) - 1));
creditCard_label = creditCard_data(:, size(creditCard_data, 2));
creditCard_label(creditCard_label == 0) = -1;

%% synthetic data SVM test
[alpha, y, data, bias] = my_SVMtrain(trainData, trainLabel, @(data1, data2) linearkernel(data1, data2));
predict = my_SVMpredict(alpha, y, data, bias, trainData, @(data1, data2) linearkernel(data1, data2));

x0_min = min(data(:, 1));
x0_max = max(data(:, 1));
x1_min = min(data(:, 2));
x1_max = max(data(:, 2));
[x0, x1] = meshgrid(x0_min:0.01:x0_max, x1_min:0.01:x1_max);
figure;
for i = 1 : size(x0, 1)
    for j = 1 : size(x0, 2)
       confidence(i, j) = my_SVMpredict(alpha, y, data, bias, [x0(i, j) x1(i, j)] , @(data1, data2) linearkernel(data1, data2));
    end
end

% imagesc([x0_min, x0_max], [x1_min, x1_max], confidence);
hold on
plot(x0(abs(confidence - 0) < 0.001), x1(abs(confidence - 0) < 0.001), 'k.');
plot(data0(:, 1), data0(:, 2), 'r.', data1(:, 1), data1(:, 2), 'bo');
support_index = find(alpha > 0);
plot(data(support_index, 1), data(support_index, 2), 'kx', 'markers',12);
xlabel('x_0');
ylabel('x_1');
title('toy SVM classification');
% colorbar
% set(gca,'YDir','normal')

%% creditCard data SVM linear kernel test
% svmModel_l = fitcsvm(creditCard_sample, creditCard_data(:, size(creditCard_data, 2)), 'Standardize', true, 'KernelFunction', 'linear');
% svmModel_l = fitPosterior(svmModel_l);
% [~, Yscores] = predict(svmModel_l, creditCard_data(:, 1:(size(creditCard_data, 2) - 1)));
svmCrossValid(creditCard_data)
% [alpha_cl, y_cl, data_cl, bias_cl] = my_SVMtrain(creditCard_sample, creditCard_label, @(data1, data2) linearkernel(data1, data2));
% predict_cl = my_SVMpredict(alpha_cl, y_cl, data_cl, bias_cl, creditCard_sample, @(data1, data2) linearkernel(data1, data2));
% 
% %% creditCard data SVM rbf kernel test
% [alpha_cr, y_cr, data_cr, bias_cr] = my_SVMtrain(creditCard_sample, creditCard_label, @(data1, data2) rbfkernel(data1, data2, 100));
% predict_cr = my_SVMpredict(alpha_cr, y_cr, data_cr, bias_cr, creditCard_sample, @(data1, data2) rbfkernel(data1, data2, 100));
