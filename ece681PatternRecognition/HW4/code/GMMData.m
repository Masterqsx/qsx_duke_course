clear
clc
mu0_1=[-3,2];
mu0_2=[0,2];
mu1_1=[0,-1];
mu1_2=[3,-1];

sigmap_1=[1,0.7;0.7,1];
sigmam_1=[1,-0.7;-0.7,1];


H0_1=mvnrnd(mu0_1,sigmap_1,100);
H0_2=mvnrnd(mu0_2,sigmam_1,100);

H1_1=mvnrnd(mu1_1,sigmam_1,100);
H1_2=mvnrnd(mu1_2,sigmap_1,100);

H0_1=[H0_1;H0_2];
H1_1=[H1_1;H1_2];

Bayes=CrossValidation_multiclassifier(H0_1,H1_1,1,0);
hold on;
Dlrt3=CrossValidation_multiclassifier(H0_1,H1_1,3,3);
Dlrt5=CrossValidation_multiclassifier(H0_1,H1_1,3,5);
Dlrt9=CrossValidation_multiclassifier(H0_1,H1_1,3,9);
Dlrt15=CrossValidation_multiclassifier(H0_1,H1_1,3,15);
SVM=CrossValidation_multiclassifier(H0_1,H1_1,5,0);
RVM=CrossValidation_multiclassifier(H0_1,H1_1,6,0);

grid on;
legend(['Bayes classifier 10-folder ROC, AUC = ',num2str(Bayes)],['DLRT k=3 classifier 10-folder ROC, AUC = ',num2str(Dlrt3)],['DLRT k=5 classifier 10-folder ROC, AUC = ',num2str(Dlrt5)],['DLRT k=9 classifier 10-folder ROC, AUC = ',num2str(Dlrt9)],['DLRT k=15 classifier 10-folder ROC, AUC = ',num2str(Dlrt15)],['SVM classifier 10-folder ROC, AUC = ',num2str(SVM)],['RVM classifier 10-folder ROC, AUC = ',num2str(RVM)]);
plot(0:0.01:1,0:0.01:1,'--');
xlabel('P_F_A');
ylabel('P_D');
title('mean ROC with different classifiers');

figure;
visual_multiclassifier(H0_1,H1_1,1,0);
figure;
visual_multiclassifier(H0_1,H1_1,3,3);
figure;
visual_multiclassifier(H0_1,H1_1,3,5);
figure;
visual_multiclassifier(H0_1,H1_1,3,9);
figure;
visual_multiclassifier(H0_1,H1_1,3,15);
figure;
visual_multiclassifier(H0_1,H1_1,5,0);
figure;
visual_multiclassifier(H0_1,H1_1,6,0);

load('HW04gaussianMixtureBlindTestFeatures.mat')
basisWidth=sqrt(0.5);%could first choose the 1/nums_para, then do the grid search
[RVM_w,RVM_X]=RVMTrain(H0_1,H1_1,basisWidth);

for i=1:length(gaussianMixtureBlindFeatures)
    decStat(i)=RVMClassifier(gaussianMixtureBlindFeatures(i,:)',RVM_X,RVM_w,basisWidth);
end
figure;
decStat=decStat';
ksdensity(decStat);
save GaussianMixtureDatadecStat.mat decStat;