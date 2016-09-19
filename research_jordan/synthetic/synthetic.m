clear
clc

list = [500, 1000, 2000, 4000, 8000, 16000, 20000]; % number of testing samples
mean_list = [0.1, 0.3];
sumERROR = zeros(length(list), 4);
for mean_cur = mean_list
n = 1;
Ntrain0 = 900;
Ntrain1 = 100;
Htrain0 = normrnd(mean_cur, 0.3, Ntrain0, 1);
Htrain1 = normrnd(0.8, 0.3, Ntrain1, 1);

trainData = [Htrain0;Htrain1];
trainLabel = [zeros(Ntrain0, 1);ones(Ntrain1, 1)];
for Ntest = list
    for i = 1 : 10
        mu0guess = mean(Htrain0);
        mu1guess = mean(Htrain1);
        sigma0guess = sqrt(var(Htrain0));
        sigma1guess = sqrt(var(Htrain1));
        [PD,PF,threshold_roc, ave] = rocAdjustTrain(trainData, trainLabel);
        [P,R,threshold_pr] = prAdjustTrain(trainData, trainLabel);
        
        Ntest0 = Ntest * 0.9;
        Ntest1 = Ntest - Ntest0;
        Htest0 = normrnd(mean_cur-0.2, 0.3, Ntest0, 1);
        Htest1 = normrnd(0.8, 0.3, Ntest1, 1);
        testData = [Htest0;Htest1];
        testLabel = [zeros(Ntest0, 1);ones(Ntest1, 1)];

        [NH1_2, ERROR_2, N1_2] = posteriroTest(testData, testLabel, mu0guess, sigma0guess, mu1guess, sigma1guess, Ntrain0/(Ntrain0+Ntrain1), Ntrain1/(Ntrain0+Ntrain1));
        [NH1_3, ERROR_3, N1_3] = rocAdjustTest(testData, testLabel, PD, PF, threshold_roc, ave);
        [NH1_4, ERROR_4, N1_4] = prAdjustTest(testData, testLabel, P, R, threshold_pr, ave);
        sumERROR(n,1) = sumERROR(n,1) + ERROR_2;
        sumERROR(n,2) = sumERROR(n,2) + ERROR_3;
        sumERROR(n,3) = sumERROR(n,3) + ERROR_4;
    end
    
    sumERROR(n,1) = sumERROR(n,1) / 10;
    sumERROR(n,2) = sumERROR(n,2) / 10;
    sumERROR(n,3) = sumERROR(n,3) / 10;
    n=n+1;
end
plot(list,sumERROR(:,1))
hold on;

plot(list,sumERROR(:,2))
plot(list,sumERROR(:,3))
end
xlabel('# of test decision statistics');
ylabel('Error');
title('The Error of Posterior Method');
legend('bestposterior', 'bestrocadjust', 'bestpradjust','mediumposterior', 'mediumrocadjust', 'mediumpradjust','worstposterior', 'worstrocadjust', 'worstpradjust');
%legend('bestposterior','mediumposterior','worstposterior');
grid on;