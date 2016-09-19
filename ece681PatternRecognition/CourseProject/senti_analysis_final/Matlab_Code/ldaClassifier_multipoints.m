function numda_return=ldaClassifier_multipoints(H0_1,H1_1,mean,variance,train0,train1)
    l0=size(H0_1);
    l1=size(H1_1);
    for i=1:l0(1)
        numda0_test(i)=ldaClassifier(H0_1(i,:)',mean,variance,train0,train1);
    end
    for i=1:l1(1)
        numda1_test(i)=ldaClassifier(H1_1(i,:)',mean,variance,train0,train1);
    end
    
    numda_return(:,1)=numda0_test';
    numda_return(:,2)=numda1_test';
end