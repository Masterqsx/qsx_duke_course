function numda=MultinomialNaiveBayesClassifier(x,Mdl)
    [label,score]=predict(Mdl,x');
    numda=score(2);
end