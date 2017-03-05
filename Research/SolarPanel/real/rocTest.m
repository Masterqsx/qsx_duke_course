function [NH1, error, N1] = rocTest(data, label, threshold)
    NH1 = length(data(data >= threshold));
    N1 = length(data(label == 1));
    error = abs(NH1 - length(find(label == 1))) / length(find(label == 1));
end