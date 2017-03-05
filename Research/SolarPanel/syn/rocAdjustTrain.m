function [PD, PF, threshold, ave] = rocAdjustTrain(data, label)
    minError = length(data);
    for i = linspace(min(data), max(data), 2000)
        pe = (length(data(label == 0 & data >= i)) + length(data(label == 1 & data < i)));
        if minError > pe
            threshold = i;
            minError = pe;
        end
    end
    PD = length(data(label == 1 & data >= threshold))/length(data(label == 1));
    PF = length(data(label == 0 & data >= threshold))/length(data(label == 0));
    ave = mean(data);
end