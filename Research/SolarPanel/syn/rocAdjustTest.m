function [NH1, error, N1] = rocAdjustTest(data, label, PD, PF, threshold, ave)
    n0 = length(data(data < threshold));
    n1 = length(data(data >= threshold));
    NH1 = ((n0+n1)*PF-n1)/(PF-PD);
    N1 = length(data(label == 1));
    error = abs(NH1 - length(find(label == 1))) / length(find(label == 1));
end