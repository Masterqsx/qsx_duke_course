function w=logisticRegressionTrain(H0_1,H1_1,alpha)
    sz0=size(H0_1);
    sz1=size(H1_1);
    w=ones(sz0(2)+1,1);
    sigmoidFcn = @(x)1./(1+exp(-x));
    H0=[ones(sz0(1),1),H0_1];
    H1=[ones(sz1(1),1),H1_1];
    T0=zeros(sz0(1),1);
    T1=ones(sz1(1),1);
    X=[H0;H1];
    Y=[T0;T1];
    while 1
        P=sigmoidFcn((w'*X')');
        W=diag(P.*(1-P)+10^(-15));
        temp=(-1.*X'*W*X)\(X'*(Y-P));
        if norm(temp)<0.001
            break;
        end
        w=w-alpha*temp;
    end

end