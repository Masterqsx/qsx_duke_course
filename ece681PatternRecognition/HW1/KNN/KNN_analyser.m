clear
clc
mu0_1=[0,0];
mu1_1=[2,3];
sigma0_1=[1,0;0,1];
sigma1_1=[2,0;0,2];
H0_1=mvnrnd(mu0_1,sigma0_1,50);
H1_1=mvnrnd(mu1_1,sigma1_1,50);

Ds_1=[H0_1;H1_1];
Target_1=zeros(50,1);
Target_1=[Target_1;ones(50,1)];

Min=min(Ds_1);
Max=max(Ds_1);

x=linspace(Min(1)*0.8,Max(1)*1.2,200);
y=linspace(Min(2)*0.8,Max(2)*1.2,200);
[Surface_x,Surface_y]=meshgrid(x,y);


Classfier=Ds_1;
Classfier(:,3)=Target_1;


K=[1 3 5 7 11 15 19];
for i=1:200
  for j=1:200
    for q=1:7
        numda(i,j,q)=runClassfier([Surface_x(i,j),Surface_y(i,j)],Classfier,K(q));  
    end
  end
end
for q=1:7
    subplot(2,4,q);
    imagesc([Min(1)*0.8,Max(1)*1.2],[Min(2)*0.8,Max(2)*1.2],numda(:,:,q));
    title(['KNN Visualization K=' num2str(K(q))]);
    xlabel('Feature 1');
    ylabel('Feature 2');
    colorbar;
    hold on;
    plot(Ds_1(Target_1==1,1),Ds_1(Target_1==1,2),'ro','MarkerFaceColor','r')
    plot(Ds_1(Target_1==0,1),Ds_1(Target_1==0,2),'ro','MarkerFaceColor','g')
    
end




figure;
for q=1:7
    numda_train(:,:,q)=runClassfier_multipoints(H0_1,H1_1,Classfier,K(q));
    hold on
    AUC_train(q)=plotROC(numda_train(:,1,q),numda_train(:,2,q));
end
title('ROC curves of train data');
xlabel('P_f');
ylabel('P_d');
legend('K=1','K=3','K=5','K=7','K=11','K=15','K=19');
plot(0:0.01:1,0:0.01:1,'--');

figure;
plot(K,AUC_train);
title('AUC vs K curve of training data');
xlabel('K');
ylabel('AUC');

H0_test=mvnrnd(mu0_1,sigma0_1,200);
H1_test=mvnrnd(mu1_1,sigma1_1,200);

figure;
for q=1:7
    numda_test(:,:,q)=runClassfier_multipoints(H0_test,H1_test,Classfier,K(q));
    hold on
    AUC_test(q)=plotROC(numda_test(:,1,q),numda_test(:,2,q));
end
legend('K=1','K=3','K=5','K=7','K=11','K=15','K=19');
title('ROC curves of test data');
xlabel('P_f');
ylabel('P_d');
plot(0:0.01:1,0:0.01:1,'--');

figure;
plot(K,AUC_test);
title('AUC vs K curve of test data');
xlabel('K');
ylabel('AUC');

%{
ksdensity(numda_test(:,1));
hold on
ksdensity(numda_test(:,2));
%}

load('HW01knnBlindTestFeatures.mat');
for i=1:length(knnBlindFeatures)
    decStat(i)=runClassfier(knnBlindFeatures(i,:),Classfier,15);
end
decStat=decStat';
save decStat.mat decStat;
figure;
imagesc([Min(1)*0.8,Max(1)*1.2],[Min(2)*0.8,Max(2)*1.2],numda(:,:,6));
hold on
plot(H1_test(:,1),H1_test(:,2),'ro','MarkerFaceColor','r')
plot(H0_test(:,1),H0_test(:,2),'ro','MarkerFaceColor','g')
plot(knnBlindFeatures(:,1),knnBlindFeatures(:,2),'ko','MarkerFaceColor','k')
title('BlindTest data distribution on KNN Classifier');
xlabel('Feature 1');
ylabel('Feature 2');
legend('Hypothesis 1','Hypothesis 0','knnBlindTest','Location','SouthEastOutside');