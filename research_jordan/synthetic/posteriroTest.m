function [NH1, error, N1] = posteriroTest(data, label, mu0, sigma0, mu1, sigma1, PH0, PH1)
    NH1 = 0;
    for i =1:length(data)
        NH1 = NH1 + normpdf(data(i), mu1, sigma1) * PH1 / (normpdf(data(i), mu1, sigma1) * PH1 + normpdf(data(i), mu0, sigma0) * PH0);
    end;
    N1 = length(data(label == 1));
    error = abs(NH1 - length(find(label == 1))) / length(find(label == 1));
end