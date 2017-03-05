function res = transform(data)
    for i = 1:size(data, 1)
         img = reshape(data(i, :), [28, 28]);
         res(i, :) = extractHOGFeatures(img);
    end
end