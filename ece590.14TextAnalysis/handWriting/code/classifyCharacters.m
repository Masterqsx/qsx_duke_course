function pre = classifyCharacters(train, label, test)
    train = transform(train);
    test = transform(test);
    t = templateSVM('Standardize',1, 'KernelFunction','linear');
    SVMmodel = fitcecoc(train,label, 'learner', t);
    pre = predict(SVMmodel, test);
end

