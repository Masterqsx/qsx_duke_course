function [h0_hist, h1_hist] = histTrain(data, label)
    h0_hist = [mean(data(label == 0)), sqrt(var(data(label == 0)))];
    h1_hist = [mean(data(label == 1)), sqrt(var(data(label == 1)))];
end