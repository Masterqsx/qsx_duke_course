function [AUCsvm1, AUCsvm2] = svmCrossValid(data)
    P = randperm(10);
    for i = 1:length(data)/10-1
        P = [P, randperm(10)];
    end
    [m,n] = size(data);
    i = round(rand * 9) + 1;
    trainingSet = data((P~=i), :);
    testSet = data((P==i), :);
    X = trainingSet(:, 1:n-1);
    Y = trainingSet(:, n);
    Xtest = testSet(:, 1:n-1);
    Ytest = testSet(:, n);
%% rbf1
    svmModel = fitcsvm(X, Y, 'Standardize', true, 'KernelFunction', 'rbf', 'KernelScale', sqrt(2));
    svmModel = fitPosterior(svmModel);
    [~, Yscores] = predict(svmModel, Xtest);
    [Xsvm, Ysvm, Tsvm, AUCsvm1] = perfcurve(Ytest, Yscores(:, 2), 1);
    figure;
    plot(Xsvm, Ysvm);
    hold on;
%% rbf 2   
    svmModel = fitcsvm(X, Y, 'Standardize', true, 'KernelFunction', 'rbf', 'KernelScale', sqrt(20));
    svmModel = fitPosterior(svmModel);
    [~, Yscores] = predict(svmModel, Xtest);
    [Xsvm, Ysvm, Tsvm, AUCsvm2] = perfcurve(Ytest, Yscores(:, 2), 1);
    plot(Xsvm, Ysvm);
%% linear    
    svmModel = fitcsvm(X, Y, 'Standardize', true, 'KernelFunction', 'linear');
    svmModel = fitPosterior(svmModel);
    [~, Yscores] = predict(svmModel, Xtest);
    [Xsvm, Ysvm, Tsvm, AUCsvm3] = perfcurve(Ytest, Yscores(:, 2), 1);
    plot(Xsvm, Ysvm);
    
    xlabel('false positive rate');
    ylabel('true positive rate');
    title(['ROC Curves for Classification Algorithms for folder ',num2str(i)]);
    legend(['SVM, AUC = ', num2str(AUCsvm1), ', sigma^2 = ', num2str(2)], ['SVM, AUC = ', num2str(AUCsvm2), ', sigma^2 = ', num2str(20)], ['SVM, AUC = ', num2str(AUCsvm3), ', linear'], 'Location','southeast');
    grid on
end