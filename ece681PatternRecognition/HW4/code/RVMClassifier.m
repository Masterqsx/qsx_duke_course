function numda=RVMClassifier(x,X,w,basisWidth)
    numda=rbf(x',X,basisWidth)*w;
end