function numda=SVMClassifier(x,SVMModel)
    [label,score]=predict(SVMModel,x');
    numda=score(2);
end