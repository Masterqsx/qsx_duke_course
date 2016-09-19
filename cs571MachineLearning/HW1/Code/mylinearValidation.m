function accuracy=mylinearValidation(x,y,w)
    [len,wid] = size(x);
    count = 0;
    for i=1:len
        if(y(i)*w*x(i,:)'>=0)
            count = count + 1;
        end
    end
    accuracy = count/len;
end