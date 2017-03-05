function [thetaA_es, thetaB_es] = em(data, thetaA_ori, thetaB_ori, n)
    thetaA_es = thetaA_ori;
    thetaB_es = thetaB_ori;
    for i = 1:1000
%% E Step
        for j = 1:length(data)
            QA(j) = thetaA_es^data(j) * (1 - thetaA_es)^(n - data(j));
            QB(j) = thetaB_es^data(j) * (1 - thetaB_es)^(n - data(j));
            QA(j) = QA(j) * 1/2 / (QA(j) * 1/2 + QB(j) * 1/2);
            QB(j) = 1 - QA(j);
        end 
%% M Step
        thetaA_es = sum(QA .* data) / sum(n * QA);
        thetaB_es = sum(QB .* data) / sum(n * QB);
    end
end