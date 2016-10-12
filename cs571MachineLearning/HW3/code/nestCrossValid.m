function nestCrossValid(data)
    P = randperm(10);
    for i = 1:(length(data)/10)-1
        P = [P, randperm(10)];
    end
    [m,n] = size(data);
    
    Ntree = [5, 15, 30];
    index = 1:10;
    for i = 1:10
        trainingSet = data((P~=i), :);
        testSet = data((P==i), :);
% ... create the desired matrices
        X = trainingSet(:, 1:n-1);
        Y = trainingSet(:, n);
        Xtest = testSet(:, 1:n-1);
        Ytest = testSet(:, n);
%% Hyper parameter evaluate
        count = 1;
        AUCrf_v = zeros(3,1);
        AUCbt_v = zeros(3,1);
        for k = Ntree
            for j = index(index~=i)
                Xvalid = data(P~=i&P==j,1:n-1);
                Yvalid = data(P~=i&P==j,n);
                Xtrain = data(P~=i&P~=j,1:n-1);
                Ytrain = data(P~=i&P~=j,n);
% Random Forest (RF)
                rfModel = fitensemble(Xtrain, Ytrain, 'Bag', k, 'Tree', 'Type', 'Classification');
                [~, Yscores] = predict(rfModel, Xvalid);
% ... compute the standard ROC curve and the AUROC
                [Xrf, Yrf, Trf, AUCrf] = perfcurve(Yvalid, Yscores(:, 2), 1);
                AUCrf_v(count) = AUCrf_v(count) + AUCrf;
% Boosted Trees
                btModel = fitensemble(Xtrain, Ytrain, 'AdaBoostM1', k, 'Tree');
                [~, Yscores] = predict(btModel, Xvalid);
% ... compute the standard ROC curve and the AUROC
                [Xbt, Ybt, Tbt, AUCbt] = perfcurve(Yvalid, sigmf(Yscores(:, 2), [1 0]), 1);
                AUCbt_v(count) = AUCbt_v(count) + AUCbt;
            end
            count = count+1;
        end
        Ntree_rf = Ntree(AUCrf_v == max(AUCrf_v));
        Ntree_bt = Ntree(AUCbt_v == max(AUCbt_v));
        Ntree_rf = Ntree_rf(1)
        Ntree_bt = Ntree_bt(1)
%% Cross Validation
% Random Forest (RF)
        rfModel = fitensemble(X, Y, 'Bag', Ntree_rf, 'Tree', 'Type', 'Classification');
        [~, Yscores] = predict(rfModel, Xtest);

% ... compute the standard ROC curve and the AUROC
        [Xrf, Yrf, Trf, AUCrf] = perfcurve(Ytest, Yscores(:, 2), 1);

% Boosted Trees

        btModel = fitensemble(X, Y, 'AdaBoostM1', Ntree_bt, 'Tree');
        [~, Yscores] = predict(btModel, Xtest);

% ... compute the standard ROC curve and the AUROC
        [Xbt, Ybt, Tbt, AUCbt] = perfcurve(Ytest, sigmf(Yscores(:, 2), [1 0]), 1);
%% ROC Curves
        if (i <= 5)
            figure(3);
            subplot(2, 3, i);
        else
            figure(4);
            subplot(2, 3, i-5);
        end
        hold on
        plot(Xrf, Yrf)
        plot(Xbt, Ybt)
        legend(['Random Forest, AUC = ', num2str(AUCrf)], ['Boosted Trees, AUC = ', num2str(AUCbt)], 'Location','southeast')
        xlabel('false positive rate');
        ylabel('true positive rate');
        title(['ROC Curves for folder ',num2str(i)]);
        grid on
        hold off
    end

end