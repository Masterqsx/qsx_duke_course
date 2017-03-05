function res = rbfkernel(data1, data2, sigma)
    [n1, p1] = size(data1);
    norm1 = sum(data1.^2, 2);
    [n2, p2] = size(data2);
    norm2 = sum(data2.^2, 2);
    D = ones(n1, 1) * norm2' + (ones(n2, 1) * norm1')' - 2 .* data1 * data2';
    res = exp(-D/2*sigma^2);
end