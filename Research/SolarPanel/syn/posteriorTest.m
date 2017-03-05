function [NH1, error, N1] = posteriorTest(data, label, para0, para1, PH0, PH1, pdf)
    NH1 = 0;
    for i =1:length(data)
        NH1 = NH1 + pdf(data(i), para1) * PH1 / (pdf(data(i), para1) * PH1 + pdf(data(i), para0) * PH0);
    end;
    N1 = length(data(label == 1));
    error = abs(NH1 - length(find(label == 1))) / length(find(label == 1));
end