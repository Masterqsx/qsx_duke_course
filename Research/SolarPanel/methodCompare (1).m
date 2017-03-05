function methodCompare(DsTest, DsTrain)

interval = 0.002;
range = [0.001:interval:0.01]; %generate ratio vector
c_er_1 = zeros(length(range), 1);
c_er_2 = zeros(length(range), 1);
c_er_3 = zeros(length(range), 1);%store the cumulative error
repeat = 100;
n = 1;

trainData = DsTrain(:, 1);
trainLabel = DsTrain(:, 2);
yH0TrainSample = DsTrain(DsTrain(:, 2) == 0, 1);%isolate training H0
yH1TrainSample = DsTrain(DsTrain(:, 2) == 1, 1);
yH0TestSample = DsTest(DsTest(:, 2) == 0, 1);%isolate test H0
yH1TestSample = DsTest(DsTest(:, 2) == 1, 1);

% yH0TrainSample = transform(yH0TrainSample, eps);
% yH1TrainSample = transform(yH1TrainSample, eps);

pri_train = length(yH1TrainSample) / (length(yH1TrainSample) + length(yH0TrainSample));
[h0_hist, h1_hist] = histTrain(trainData, trainLabel, 0.2);
[PD,PF,threshold_roc, ave] = rocAdjustTrain(trainData, trainLabel);

testAll = DsTest;
Ntest_t = length(testAll);

for ratio = range
    for i = 1:repeat      
        Ntest = floor(Ntest_t * ratio);
        testsample = datasample(testAll, Ntest);
        testData = testsample(:, 1);
%         testData = transform(testData, eps);
        testLabel = testsample(:, 2);
        pri_test = length(testLabel(testLabel == 1))/Ntest;
%         [NH1_1, ERROR_1, N1_1] = posteriroTest(testData, testLabel, para0_train, para1_train, 1-pri_train, pri_train, @(x, para) pareto(x, para));  
        [NH1_1, ERROR_1, N1_1] = posteriroTest(testData, testLabel, h0_hist, h1_hist, 1-pri_train, pri_train, @(x, para) histTest(x, para));
        [NH1_2, ERROR_2, N1_2] = rocAdjustTest(testData, testLabel, PD, PF, threshold_roc, ave);
        [NH1_3, ERROR_3, N1_3] = rocTest(testData, testLabel, threshold_roc);
        c_er_1(n) = c_er_1(n) + ERROR_1
        c_er_2(n) = c_er_2(n) + ERROR_2
        c_er_3(n) = c_er_3(n) + ERROR_3
    end
    n = n + 1;
end

figure;
list = floor(Ntest_t * range);
c_er_1 = c_er_1 / repeat;
c_er_2 = c_er_2 / repeat;
c_er_3 = c_er_3 / repeat;
plot(list, c_er_1)
hold on;
plot(list, c_er_2)
plot(list, c_er_3)
hold off;
xlabel('# of test decision statistics');
ylabel('Error');
title('The Error of Methods');
legend('posterior', 'rocadjust', 'roc')

end