function w=testGrandientAscending(x,alpha)
    sz0=size(x);
    w=ones(sz0(2)+1,1);
    temp=w;
    Fcn = @(x)-4*x;
    while (norm(temp,1)/length(temp))<0.01
        temp=zeros(sz0(2)+1,1);
        for i=1:sz0(1)
            temp(1)=temp(1)+1*(0-(1-sigmoidFcn(w'*[1,H0_1(i,:)])));
        end
    
        for j=1:(length(w)-1)     
            for i=1:sz0(1)
                temp(j+1)=temp(j+1)+H0_1(i,j)*(0-(1-sigmoidFcn(w'*[1,H0_1(i,:)])));
            end
        end
        w=w+alpha.*temp;
    end  
end