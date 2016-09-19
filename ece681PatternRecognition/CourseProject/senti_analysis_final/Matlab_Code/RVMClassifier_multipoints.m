function numda_return=RVMClassifier_multipoints(H0_1,H1_1,RVM_X,w,basisWidth)
    l0=size(H0_1);
    l1=size(H1_1);
    for i=1:l0(1)
        numda0_test(i)=RVMClassifier(H0_1(i,:)',RVM_X,w,basisWidth);
    end
    for i=1:l1(1)
        numda1_test(i)=RVMClassifier(H1_1(i,:)',RVM_X,w,basisWidth);
    end
    
    numda_return(:,1)=numda0_test';
    numda_return(:,2)=numda1_test';
end