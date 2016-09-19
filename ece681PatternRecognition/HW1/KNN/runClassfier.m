function numda=runClassfier(testFeature,Classfier,K)
    cl=size(Classfier);
    temp=zeros(cl(1));
    for q=1:cl(1)
     temp(q)=sqrt( (testFeature(1)-Classfier(q,1))^2+(testFeature(2)-Classfier(q,2))^2 );
    end
    [~,index]=sort(temp);
    K_n=index(1:K);
    numda=sum(Classfier(K_n,3)==1)/K;
    