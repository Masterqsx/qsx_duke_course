clear
clc
mu0_1=[-1,-1];
mu1_1=[2,1];
sigma0_1=[1,-0.4;-0.4,1.5];
sigma1_1=[2,0.9;0.9,1];
H0_1=mvnrnd(mu0_1,sigma0_1,500);
H1_1=mvnrnd(mu1_1,sigma1_1,500);


KNN=CrossValidation_multiclassifier(H0_1,H1_1,0,0);
hold on;
Bayes=CrossValidation_multiclassifier(H0_1,H1_1,1,0);
grid on;
Lda=CrossValidation_multiclassifier(H0_1,H1_1,2,0);
Dlrt3=CrossValidation_multiclassifier(H0_1,H1_1,3,3);
Dlrt5=CrossValidation_multiclassifier(H0_1,H1_1,3,5);
Dlrt9=CrossValidation_multiclassifier(H0_1,H1_1,3,9);
Dlrt15=CrossValidation_multiclassifier(H0_1,H1_1,3,15);
legend(['KNN classifier 10-folder ROC, AUC = ',num2str(KNN)],['Bayes classifier 10-folder ROC, AUC = ',num2str(Bayes)],['LDA classifier 10-folder ROC, AUC = ',num2str(Lda)],['DLRT k=3 classifier 10-folder ROC, AUC = ',num2str(Dlrt3)],['DLRT k=5 classifier 10-folder ROC, AUC = ',num2str(Dlrt5)],['DLRT k=9 classifier 10-folder ROC, AUC = ',num2str(Dlrt9)],['DLRT k=15 classifier 10-folder ROC, AUC = ',num2str(Dlrt15)],'Location','southeast');
plot(0:0.01:1,0:0.01:1,'--');
xlabel('P_F_A');
ylabel('P_D');
title('mean ROC with different classifiers');

figure;
visual_multiclassifier(H0_1,H1_1,0,0);
figure;
visual_multiclassifier(H0_1,H1_1,1,0);
figure;
visual_multiclassifier(H0_1,H1_1,2,0);
figure;
visual_multiclassifier(H0_1,H1_1,3,3);
figure;
visual_multiclassifier(H0_1,H1_1,3,5);
figure;
visual_multiclassifier(H0_1,H1_1,3,9);
figure;
visual_multiclassifier(H0_1,H1_1,3,15);

load('HW03gaussianBlindTestFeatures.mat')
me(:,1)=mean(H0_1)';me(:,2)=mean(H1_1)';
variance(:,:,1)=cov(H0_1);variance(:,:,2)=cov(H1_1);

for i=1:length(gaussianBlindFeatures)
    decStat(i)=bayesClassifier(gaussianBlindFeatures(i,:)',me,variance);
end
figure;
decStat=decStat';
ksdensity(decStat);
save GaussianDatadecStat.mat decStat;

