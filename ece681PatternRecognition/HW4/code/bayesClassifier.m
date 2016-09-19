function numda=bayesClassifier(x,mean,variance)
    p0=-0.5*(x-mean(:,1))'/variance(:,:,1)*(x-mean(:,1))-0.5*log(det(variance(:,:,1)))+log(0.5);
    p1=-0.5*(x-mean(:,2))'/variance(:,:,2)*(x-mean(:,2))-0.5*log(det(variance(:,:,2)))+log(0.5);
    numda=p1-p0;
end