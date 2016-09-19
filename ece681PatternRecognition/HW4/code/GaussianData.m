clear
clc
mu0_1=[-1,-1];
mu1_1=[2,1];
muo_1=[0,0];
sigma0_1=[1,-0.4;-0.4,1.5];
sigma1_1=[2,0.9;0.9,1];
sigmao_1=[50,-30;-30,50];
H0_1=mvnrnd(mu0_1,sigma0_1,490);
H1_1=mvnrnd(mu1_1,sigma1_1,490);
Ho_1=mvnrnd(muo_1,sigmao_1,10);
H0_1=[H0_1;Ho_1];
H1_1=[H1_1;Ho_1];

Bayes=CrossValidation_multiclassifier(H0_1,H1_1,1,0);
hold on;

Lda=CrossValidation_multiclassifier(H0_1,H1_1,2,0);
LR=CrossValidation_multiclassifier(H0_1,H1_1,4,0);
grid on;
legend(['Bayes classifier 10-folder ROC, AUC = ',num2str(Bayes)],['FLD classifier 10-folder ROC, AUC = ',num2str(Lda)],['LR classifier 10-folder ROC, AUC = ',num2str(LR)]);
plot(0:0.01:1,0:0.01:1,'--');
xlabel('P_F_A');
ylabel('P_D');
title('mean ROC with different classifiers');

figure;
visual_multiclassifier(H0_1,H1_1,1,0);
figure;
visual_multiclassifier(H0_1,H1_1,2,0);
figure;
visual_multiclassifier(H0_1,H1_1,4,0);

load('HW04gaussianBlindTestFeatures.mat')
me(:,1)=mean(H0_1)';me(:,2)=mean(H1_1)';
variance(:,:,1)=cov(H0_1);variance(:,:,2)=cov(H1_1);

for i=1:length(gaussianBlindFeatures)
    decStat1(i)=ldaClassifier(gaussianBlindFeatures(i,:)',me,variance,H0_1,H1_1);
end
figure;
decStat1=decStat1';
ksdensity(decStat1);
xlabel('Decision Statistics, x');
ylabel('f(x)');
title('Probability Density Function for FLD result');

w=logisticRegressionTrain(H0_1,H1_1,0.01);
for i=1:length(gaussianBlindFeatures)
    decStat(i)=logisticRegressionClassifier(gaussianBlindFeatures(i,:)',w);
end
figure;
decStat=decStat';
ksdensity(decStat);
save GaussianDatadecStat.mat decStat;
xlabel('Decision Statistics, x');
ylabel('f(x)')
title('Probability Density Function for Logistic Discriminant result');

for i=1:length(gaussianBlindFeatures)
    decStat2(i)=bayesClassifier(gaussianBlindFeatures(i,:)',me,variance);
end
figure;
decStat2=decStat2';
ksdensity(decStat2);
xlabel('Decision Statistics, x');
ylabel('f(x)');
title('Probability Density Function for Bayes result');

