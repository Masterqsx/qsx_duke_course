function [P, R, threshold] = prAdjustTrain(data, label)
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
end