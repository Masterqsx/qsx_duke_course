function SVMModel=SVMTrain(H0_1,H1_1)
    sz0=size(H0_1);
    sz1=size(H1_1);
    T0=zeros(sz0(1),1);
    T1=ones(sz1(1),1);
    X=[H0_1;H1_1];
    Y=[T0;T1];
    SVMModel=fitcsvm(X,Y,'KernelFunction','rbf','Standardize',true,'ClassNames',[0,1]);

end