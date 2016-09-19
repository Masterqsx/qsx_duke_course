function AUC = CrossValidation_multiclassifier(H0_1,H1_1,n,k)
cl=size(H0_1);
numFolder=3;

Key_H0=rem([1:size(H0_1,1)]-1,numFolder)+1;
Key_H0=Key_H0(randperm(length(Key_H0)))';
Key_H1=rem([1:size(H1_1,1)]-1,numFolder)+1;
Key_H1=Key_H1(randperm(length(Key_H1)))';

for thisFolder=1:numFolder
        thisFolder
        traindata=[H0_1(Key_H0~=thisFolder,:);H1_1(Key_H1~=thisFolder,:)];
        traindata(:,cl(2)+1)=[zeros(cl(1)/numFolder*(numFolder-1),1);ones(cl(1)/numFolder*(numFolder-1),1)];
        train0=H0_1(Key_H0~=thisFolder,:);train1=H1_1(Key_H1~=thisFolder,:);
        me(:,1)=mean(train0)';me(:,2)=mean(train1)';
        variance(:,:,1)=cov(train0);variance(:,:,2)=cov(train1);
        if(n==0)
            num_test=runClassfier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),traindata,9);
        end
        if(n==1)
            num_test=bayesClassifier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),me,variance);
        end
        if(n==2)
            num_test=ldaClassifier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),me,variance,train0,train1);
        end
        if(n==3)
            num_test=dlrtClassifier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),train0,train1,k);
        end
        if(n==4)
            w=logisticRegressionTrain(train0,train1,0.01);
            num_test=logisticRegressionClassifier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),w);
        end
        if(n==5)
            SVMModel=SVMTrain(train0,train1);
            num_test=SVMClassifier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),SVMModel);
        end
        if(n==6)
            basisWidth=sqrt(size(train0,2));%could first choose the 1/nums_para, then do the grid search
            [RVM_w,RVM_X]=RVMTrain(train0,train1,basisWidth);
            num_test=RVMClassifier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),RVM_X,RVM_w,basisWidth);
        end
        
        if(thisFolder==1)
            num_mean=num_test;
        else
            num_mean=[num_mean;num_test];
        end
  
end


AUC=plotROC(num_mean(:,1),num_mean(:,2));
end