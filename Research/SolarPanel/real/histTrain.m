function [h0_hist, h1_hist] = histTrain(data, label, interval)
      h1_range = min(data(label == 1)):interval:max(data(label == 1));
      [h1_hist, ~] = hist(data(label == 1), h1_range);
      h1_hist = h1_hist ./ sum(h1_hist);
      h1_hist = h1_hist';
      h1_hist(:, 2) = [h1_range]';
      
      h0_range = min(data(label == 0)):interval:max(data(label == 1));
      [h0_hist, ~] = hist(data(label == 0), h0_range);
      h0_hist = h0_hist ./ sum(h0_hist);
      h0_hist = h0_hist';
      h0_hist(:, 2) = [h0_range]';
end