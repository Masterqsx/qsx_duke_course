function numda=ldaClassifier(x,mean,variance,H0_1,H1_1)
    Sw=variance(:,:,1)+variance(:,:,2);
    Sb=(mean(:,1)-mean(:,2))*(mean(:,1)-mean(:,2))';
    det(Sw);
    w=Sw\(mean(:,2)-mean(:,1));
    y0=w'*H0_1';
    y1=w'*H1_1';
    m(1)=w'*mean(:,1);
    m(2)=w'*mean(:,2);
    v(1)=var(y0);
    v(2)=var(y1);
    numda=w'*x;
    %%boundary=(sqrt(v(1))*m(2)+sqrt(v(2))*m(1))/(sqrt(v(1))+sqrt(v(2)));
    %%if (m(2)-boundary)>=0
    %%   numda=w'*x-boundary;
    %%else
    %%   numda=-(w'*x-boundary);
    %%end
end