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

pri_train = length(yH1TrainSample) / (length(yH1TrainSample) + length(yH0TrainSample));
[h0_hist, h1_hist] = histTrain(trainData, trainLabel, 0.2);
% [h0_norm, h1_norm] = normTrain(trainData, trainLabel);
[PD,PF,threshold_roc, ave] = rocAdjustTrain(trainData, trainLabel);

testAll = DsTest;
Ntest_t = length(testAll);

for ratio = range
    for i = 1:repeat      
        Ntest = floor(Ntest_t * ratio);
        testsample = datasample(testAll, Ntest);
        testData = testsample(:, 1);
        testLabel = testsample(:, 2);
        pri_test = length(testLabel(testLabel == 1))/Ntest;        
        [NH1_1, ERROR_1, N1_1] = posteriorTest(testData, testLabel, h0_hist, h1_hist, 1-pri_train, pri_train, @(x, para) histTest(x, para));
        [NH1_2, ERROR_2, N1_2] = rocAdjustTest(testData, testLabel, PD, PF, threshold_roc, ave);
        [NH1_3, ERROR_3, N1_3] = rocTest(testData, testLabel, threshold_roc);
%         [NH1_4, ERROR_4, N1_4] = posteriorTest(testData, testLabel, h0_norm, h1_norm, 1-pri_train, pri_train, @(x, para) normTest(x, para));
        c_er_1(n) = c_er_1(n) + ERROR_1;
        c_er_2(n) = c_er_2(n) + ERROR_2;
        c_er_3(n) = c_er_3(n) + ERROR_3;
%         c_er_4(n) = ERROR_4;
    end
    n = n + 1;
end
    
list = floor(Ntest_t * range);
c_er_1 = c_er_1 / repeat;
c_er_2 = c_er_2 / repeat;
c_er_3 = c_er_3 / repeat;
plot(list, c_er_2, 'LineWidth', 2)
hold on;
plot(list, c_er_3, 'LineWidth', 2)
plot(list, c_er_1, 'LineWidth', 2)
hold off;
xlabel('# of test decision statistics', 'FontWeight', 'bold', 'fontsize', 14);
ylabel('Error', 'FontWeight', 'bold', 'fontsize', 14);
title('The Error of Aerial Imagery Dataset', 'FontWeight', 'bold', 'fontsize', 14);
legend('\fontsize {12}{\bfROC Adjust}', '\fontsize {12}{\bfROC}', '\fontsize {12}{\bfPosterior}')

end