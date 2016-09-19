function [P, R, F1, Confusion, threshold, threshold_range] = find_t(data, label)
    minError = length(data);
    for i = linspace(min(data), max(data), 2000)
        pe = (length(data(label == 0 & data >= i)) + length(data(label == 1 & data < i)));
        if minError > pe
            threshold = i;
            minError = pe;
        end
    end
    P = length(data(label == 1 & data >= threshold))/(length(data(label == 1 & data >= threshold))+length(data(label == 0 & data >= threshold)));
    R = length(data(label == 1 & data >= threshold))/length(data(label == 1));
    F1 = 2 * P * R / (P + R);
    Confusion(1,1) = length(data(label == 1 & data >= threshold));
    Confusion(1,2) = length(data(label == 1 & data < threshold));
    Confusion(2,1) = length(data(label == 0 & data >= threshold));
    Confusion(2,2) = length(data(label == 0 & data < threshold));
    t = data(data <= threshold);
    threshold_range(1) = max(t);
    t = data(data >= threshold);
    threshold_range(2) = min(t);
end