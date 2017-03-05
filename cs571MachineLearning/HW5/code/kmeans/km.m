function [means, res, label] = km(k, data)
   means = randsample(data, k);
   label = zeros(length(data), 1);
   for i = 1:10
       %% E step
       for index = 1:length(data)
           dis = (data(index) - means).^2;
           temp = find(dis == min(dis));
           label(index) = temp(1);
       end
       %% M step 
       for index = 1:length(means)
           if length(label(label == index)) ~= 0
            means(index) = sum(data(label == index) / length(label(label == index)));
           end
       end
   end
   for i = 1:length(label)
       res(i) = means(label(i));
   end
end