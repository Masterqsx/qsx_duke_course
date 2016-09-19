function y=sum_mean_H1(s,n,single_variance)
    y=0;
    for i=1:n
        for j=1:n
               y=y+s(i,j)^2;
        end
    end
    y=y/single_variance;
