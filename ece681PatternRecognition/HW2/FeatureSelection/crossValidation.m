function AUC = crossValidation(H0_1,H1_1)
cl=size(H0_1);
numFolder=10;

Key_H0=rem([1:length(H0_1)]-1,numFolder)+1;
Key_H0=Key_H0(randperm(length(Key_H0)))';
Key_H1=rem([1:length(H1_1)]-1,numFolder)+1;
Key_H1=Key_H1(randperm(length(Key_H1)))';

for thisFolder=1:numFolder
        traindata=[H0_1(Key_H0~=thisFolder,:);H1_1(Key_H1~=thisFolder,:)];
        traindata(:,cl(2)+1)=[zeros(cl(1)/10*9,1);ones(cl(1)/10*9,1)];
        num_test=runClassfier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),traindata,9);
        if(thisFolder==1)
            num_mean=num_test;
        else
            num_mean=[num_mean;num_test];
        end
  
end
AUC=plotROC(num_mean(:,1),num_mean(:,2));

end

