function numda=logisticRegressionClassifier(x,w)
    sigmoidFcn = @(x)1./(1+exp(-x));
    numda=sigmoidFcn(w'*[1;x]);
end