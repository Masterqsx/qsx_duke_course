clear
clc
mu0_1=[0,0];
mu1_1=[2,3];
sigma0_1=[1,0;0,1];
sigma1_1=[2,0;0,2];
H0_1=mvnrnd(mu0_1,sigma0_1,500);
H1_1=mvnrnd(mu1_1,sigma1_1,500);
numFolder=10;

Key_H0=rem([1:length(H0_1)]-1,numFolder)+1;
Key_H0=Key_H0(randperm(length(Key_H0)))';
Key_H1=rem([1:length(H1_1)]-1,numFolder)+1;
Key_H1=Key_H1(randperm(length(Key_H1)))';

K=[1 3 5 7 11 15 19];
for q=1:7
  %  figure();
    for thisFolder=1:numFolder
        traindata=[H0_1(Key_H0~=thisFolder,:);H1_1(Key_H1~=thisFolder,:)];
        traindata(:,3)=[zeros(450,1);ones(450,1)];
        num_test=runClassfier_multipoints(H0_1(Key_H0==thisFolder,:),H1_1(Key_H1==thisFolder,:),traindata,K(q));
        if(thisFolder==1)
            num_mean=num_test;
        else
            num_mean=[num_mean;num_test];
        end
       % hold on;
        AUC(q,thisFolder)=plotROC(num_test(:,1),num_test(:,2));
    end
    AUC(q,numFolder+1)=plotROC(num_mean(:,1),num_mean(:,2));
 %   legend('folder=1','folder=2','folder=3','folder=4','folder=5','folder=6','folder=7','folder=8','folder=9','folder=10','mean');
    mean(:,:,q)=num_mean;
 %   plot(0:0.01:1,0:0.01:1,'--');
end
for q=1:7
    plotROC(mean(:,1,q),mean(:,2,q));
    hold on;
end
legend('k=1','k=3','k=5','k=7','k=11','k=15','k=19');
plot(0:0.01:1,0:0.01:1,'--');
xlabel('P_F_A');
ylabel('P_D');
title('mean ROC with different k');
grid on;

figure();
plot(K,AUC(:,11),'-o');
xlabel('Number of k');
ylabel('AUC for mean ROC');
title('mean AUC for mean ROC vs k');
grid on;

for q=1:6
    AUC_incre(q)=(AUC(q+1,11)-AUC(q,11))/AUC(q,11);
end
figure();
plot(K(2:7),AUC_incre,'-o');
xlabel('Number of k');
ylabel('Percentage of AUC for mean ROC change');
title('Percentage of mean AUC for mean ROC vs k');
grid on;