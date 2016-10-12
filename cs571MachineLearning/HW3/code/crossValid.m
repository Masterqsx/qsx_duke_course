function [AUC_g, AUC_s, AUC_c, AUC_r, AUC_b] = crossValid(data)
    P = randperm(10);
    for i = 1:length(data)/10-1
        P = [P, randperm(10)];
    end
    [m,n] = size(data);
    for i = 1:10
        trainingSet = data((P~=i), :);
        testSet = data((P==i), :);
        X = trainingSet(:, 1:n-1);
        Y = trainingSet(:, n);
        Xtest = testSet(:, 1:n-1);
        Ytest = testSet(:, n);
        %% Generalized Linear Model (Logistic Regression)

        glmModel = fitglm(X, Y, 'Distribution', 'binomial', 'Link', 'logit');
        Yscores = predict(glmModel, Xtest); % these are the posterior probabilities
                                    % of class 1 for the test data

% ... compute the standard ROC curve and the AUROC
        [Xglm, Yglm, Tglm, AUCglm] = perfcurve(Ytest, Yscores, 1);
        AUC_g(i) = AUCglm;
%% Support Vector Machine (SVM)

        svmModel = fitcsvm(X, Y, 'Standardize', true, 'KernelFunction', 'rbf');
        svmModel = fitPosterior(svmModel);
        [~, Yscores] = predict(svmModel, Xtest);

% ... compute the standard ROC curve and the AUROC
        [Xsvm, Ysvm, Tsvm, AUCsvm] = perfcurve(Ytest, Yscores(:, 2), 1);
        AUC_s(i) = AUCsvm;
%% Classification Tree (CART)

        ctreeModel = fitctree(X, Y);
        [~, Yscores, ~, ~] = predict(ctreeModel, Xtest);

% ... compute the standard ROC curve and the AUROC
        [Xcart, Ycart, Tcart, AUCcart] = perfcurve(Ytest, Yscores(:, 2), 1);
        AUC_c(i) = AUCcart;
%% Random Forest (RF)

        rfModel = fitensemble(X, Y, 'Bag', 30, 'Tree', 'Type', 'Classification');
        [~, Yscores] = predict(rfModel, Xtest);

% ... compute the standard ROC curve and the AUROC
        [Xrf, Yrf, Trf, AUCrf] = perfcurve(Ytest, Yscores(:, 2), 1);
        AUC_r(i) = AUCrf;
%% Boosted Trees

        btModel = fitensemble(X, Y, 'AdaBoostM1', 30, 'Tree');
        [~, Yscores] = predict(btModel, Xtest);

% ... compute the standard ROC curve and the AUROC
        [Xbt, Ybt, Tbt, AUCbt] = perfcurve(Ytest, sigmf(Yscores(:, 2), [1 0]), 1);
        AUC_b(i) = AUCbt;
%% ROC Curves
        if (i <= 5)
            figure(1);
            subplot(2, 3, i);
        else
            figure(2);
            subplot(2, 3, i-5);
        end
        plot(Xglm, Yglm)
        hold on
        plot(Xsvm, Ysvm)
        plot(Xcart, Ycart)
        plot(Xrf, Yrf)
        plot(Xbt, Ybt)
        legend(['Logistic Regression, AUC = ',num2str(AUCglm)], ['Support Vector Machine, AUC = ', num2str(AUCsvm)], ['CART, AUC = ', num2str(AUCcart)], ...
        ['Random Forest, AUC = ', num2str(AUCrf)], ['Boosted Trees, AUC = ', num2str(AUCbt)], 'Location','southeast')
        xlabel('false positive rate');
        ylabel('true positive rate');
        title(['ROC Curves for Classification Algorithms for folder ',num2str(i)]);
        grid on
        hold off
%%  individual feature ROC curve generate
        if (i <= 5)
            figure(5);
            subplot(2, 3, i);
            hold on;
        else
            figure(6);
            subplot(2, 3, i-5);
            hold on;
        end
        for feature = 1:n-1
            plotROC(Xtest(Ytest==0,feature), Xtest(Ytest==1,feature));
        end
        xlabel('false positive rate');
        ylabel('true positive rate');
        title(['ROC Curves for each feature for folder ',num2str(i)]);
        grid on
        hold off
        legend('feature1', 'feature2','feature3','feature4','feature5','feature6','feature7','feature8','feature9','Location','southeast' );
    end
end