clc
clear

dataRoot = 'data';
%% load training data
trainData = loadMNISTImages(fullfile(dataRoot,'train-images-idx3-ubyte'));
trainData = trainData';
trainLabel = loadMNISTLabels(fullfile(dataRoot, 'train-labels-idx1-ubyte'));


%% load testing data
testData = loadMNISTImages(fullfile(dataRoot, 't10k-images-idx3-ubyte'));
testData = testData';
testLabel = loadMNISTLabels(fullfile(dataRoot, 't10k-labels-idx1-ubyte'));


%% sample the dataset and estimate
train = [trainData trainLabel];
test = [testData testLabel];

err = 0;
repeat = 30;
for i = 1:repeat
    trainSample = datasample(train, 500);
    testSample = datasample(test, 500);
    pre_label = classifyCharacters(trainSample(:, 1:size(trainSample, 2)-1), trainSample(:, size(trainSample, 2)), testSample(:, 1:size(testSample, 2)-1));
    err = err + length(pre_label(pre_label ~= testSample(:, size(testSample, 2)))) / length(pre_label);
end

err = err / repeat