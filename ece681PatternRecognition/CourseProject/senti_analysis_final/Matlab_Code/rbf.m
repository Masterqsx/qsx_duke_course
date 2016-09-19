function K = rbf(X,Y,basisWidth)
%     nx	= size(X,1);
%     ny	= size(Y,1);
%     D2 = (sum((X.^2), 2) * ones(1,ny)) + (ones(nx, 1) * sum((Y.^2),2)') - 2*X*Y';
%      K=exp(-D2/(basisWidth^2)/2);%nx*ny matrix
      K=X*Y';

end
 
