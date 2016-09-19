
function numda_return=bayesClassifier_multipoints(H0_1,H1_1,mean,variance)
    l0=size(H0_1);
    l1=size(H1_1);
    for i=1:l0(1)
        numda0_test(i)=bayesClassifier(H0_1(i,:)',mean,variance);
    end
    for i=1:l1(1)
        numda1_test(i)=bayesClassifier(H1_1(i,:)',mean,variance);
    end
    
    numda_return(:,1)=numda0_test';
    numda_return(:,2)=numda1_test';
end