clear
clc
load('mnist_all.mat');%load test and train sets, only use test0,1, train0,1. 

[len0, wid0] = size(train0);
[len1, wid1] = size(train1);
[lent0, widt0] = size(test0);
[lent1, widt1] = size(test1);
train0 = im2double(train0);
train1 = im2double(train1);
y = [-ones(len0,1);ones(len1,1)];
yt = [-ones(lent0,1);ones(lent1,1)];
%% Digit Recognization with Perceptron without feature reduction
x = [train0;train1];
[w1,n1] = myPerceptron(x, y, 2, 0, 0);

xt = [test0;test1];
xt = im2double(xt);
accuray_noReduction = mylinearValidation(xt, yt, w1);
%% Digit Recognization with Perceptron and feature reduction (Norm selection)

for k=0:40
count = 0;
for i=1:wid0
    if (norm(train0(:,i))>k)
        count = [count, i];
    end
end
count = count(2:length(count));
n_count(k+1) = length(count);
x2 = [train0(:,count);train1(:,count)];
[w2,n2] = myPerceptron(x2, y, 2, 0, 0);

accuray_Reduction1(k+1) = mylinearValidation(xt(:,count), yt, w2);
end
%% Digit Recognization with Perceptron and feature reduction (PCA selection)
[U,S,V] = svd(cov(x));
i = 0;
for k=0.005:0.002:0.14
i = i+1;
n_wid = length(find(S>k));
n_n_wid(i) = n_wid;
x3 = x * U(:,1:n_wid);
[w3,n3] = myPerceptron(x3, y, 2, 0, 0);

accuray_Reduction2(i) = mylinearValidation(xt * U(:,1:n_wid), yt, w3);
end
%% Draw graph
figure;
plot(n1(2:length(n1)));
xlabel('Number of Epoch');
ylabel('Number of Mistake');
title('Perceptron algorithm convergence without feature reduction');
grid on;

figure;
plot(n_n_wid,accuray_Reduction2);
xlabel('Number of features');
ylabel('Recognization accuracy');
title('The relation with number of features and accuracy with PCA feature reduction');
grid on;

figure;
plot(n_count,accuray_Reduction1);
xlabel('Number of features');
ylabel('Recognization accuracy');
title('The relation with number of features and accuracy with naive feature reduction');
grid on;
