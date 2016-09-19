function numda=dlrtClassifier(x,H0_1,H1_1,k)
    s0=size(H0_1);
    s1=size(H1_1);
    for i=1:s0(1)
       d0(i)=0;
       for j=1:s0(2)
           d0(i)=d0(i)+(x(j)-H0_1(i,j))^2;
       end
    end
    re0=sort(d0);
    for i=1:s1(1)
       d1(i)=0;
       for j=1:s1(2)
           d1(i)=d1(i)+(x(j)-H1_1(i,j))^2;
       end
    end
    re1=sort(d1);
    numda=log(s0(1)*re0(k)^(s0(2)/2)/(s1(1)*re1(k)^(s1(2)/2)));
  
end
