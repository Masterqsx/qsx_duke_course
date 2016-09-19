function [NH1, error, N1] = prAdjustTest(data, label, P, R, threshold, ave)
    ave_t = mean(data);
    threshold = ave_t/ave * threshold;
    n1 = length(data(data >= threshold));
    NH1 = P*n1/R;
    N1 = length(data(label == 1));
    error = abs(NH1 - length(find(label == 1))) / length(find(label == 1));
end