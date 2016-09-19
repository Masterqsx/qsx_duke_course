function [w,X]=RVMTrain(H0_1,H1_1,basisWidth)
    sz0=size(H0_1);
    sz1=size(H1_1);
    T0=zeros(sz0(1),1);
    T1=ones(sz1(1),1);
    X=[H0_1;H1_1];
    Y=[T0;T1];
    BASIS=rbf(X,X,basisWidth);
    [PARAMETER, ~, ~] = SparseBayes('Gaussian', BASIS, Y);
    w=zeros(size(X,1),1);
    w(PARAMETER.Relevant)= PARAMETER.Value;
    
end