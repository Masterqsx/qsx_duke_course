clc
clear
data = dlmread('../Dataset/data.txt');
data_pre = dlmread('../Dataset/data_pre.txt');
target = dlmread('../Dataset/target.txt');

H0_data = data(target==0,:);
H0_data = H0_data(1:690,:);
H1_data = data(target==1,:);
H1_data = H1_data(1:690,:);

H0_datapre = data_pre(target==0,:);
H0_datapre = H0_datapre(1:690,:);
H1_datapre = data_pre(target==1,:);
H1_datapre = H1_datapre(1:690,:);

SVM_data_nopca = CrossValidation_multiclassifier(H0_data,H1_data,5,0);
SVM_datapre_nopca = CrossValidation_multiclassifier(H0_datapre,H1_datapre,5,0);
RVM_data_nopca = CrossValidation_multiclassifier(H0_data,H1_data,6,0);
RVM_datapre_nopca = CrossValidation_multiclassifier(H0_datapre,H1_datapre,6,0);








