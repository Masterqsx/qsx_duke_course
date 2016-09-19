clc
clear
mu0_1=[0,0,0,0];
mu1_1=[0,2,3,3];
cov=[0.5,0,0,0.3;0,1.0,0,0.7;0,0,1.0,0.2;0.3,0.7,0.2,1.5];
H0_1=mvnrnd(mu0_1,cov,250);
H1_1=mvnrnd(mu1_1,cov,250);

for i=1:20
    re(i)=crossValidation(H0_1,H1_1);
end
avg=(max(re)-min(re))/min(re)

feature_set_exhaustive=exhaustiveSearch(H0_1,H1_1,avg);
figure();
feature_set_scalar=scalarSearch(H0_1,H1_1,avg);
figure();
feature_set_sequential=sequentialSearch(H0_1,H1_1,avg);

 load 'HW02knnFeatureSelectionBlindTestFeatures.mat';
 Ds_1=[H0_1(:,[2,3]);H1_1(:,[2,3])];
 Target_1=zeros(250,1);
 Target_1=[Target_1;ones(250,1)];
 Classfier=Ds_1;
 Classfier(:,3)=Target_1;
for i=1:length(knnFeatureSelectionBlindFeatures)
    decStat(i)=runClassfier(knnFeatureSelectionBlindFeatures(i,[2,3]),Classfier,5);
end
decStat=decStat';
save decStat.mat decStat;