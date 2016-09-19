function numda_return=dlrtClassifier_multipoints(H0_1,H1_1,train0,train1,k)
    l0=size(H0_1);
    l1=size(H1_1);
    for i=1:l0(1)
        numda0_test(i)=dlrtClassifier(H0_1(i,:)',train0,train1,k);
    end
    for i=1:l1(1)
        numda1_test(i)=dlrtClassifier(H1_1(i,:)',train0,train1,k);
    end
    
    numda_return(:,1)=numda0_test';
    numda_return(:,2)=numda1_test';
end