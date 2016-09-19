function numda=runClassfier(testFeature,Classfier,K)
    cl=size(Classfier);
    temp=zeros(cl(1),1);
    for q=1:cl(1)
      for i=1:(cl(2)-1)
        %temp(q)=temp(q)+(testFeature(i)-Classfier(q,i))^(cl(2)-1);
        temp(q)=temp(q)+(testFeature(i)-Classfier(q,i))^2;
      end
%       temp(q)=temp(q)^(1/(cl(2)-1));
      temp(q)=temp(q)^(1/2);
    end
    [~,index]=sort(temp);
    K_n=index(1:K);
    numda=sum(Classfier(K_n,cl(2))==1)/K;
    