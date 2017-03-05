clc
clear

syn_data1 = normrnd(1, 1, 10, 1);
syn_data2 = normrnd(2.8, 0.2, 20, 1);
[syn_means, syn_res] = km(2, [syn_data1; syn_data2]);

graph = im2double(imread('raccoon.png'));
[m, n] = size(graph);
data = reshape(graph, [m * n, 1]);
figure
histogram(data);
title('Pixel Distribution of Original Picture');
xlabel('pixel value');
ylabel('times');

[means, res, ~] = km(2, data);
colormap(gray);
imagesc(reshape(res, [m, n]));

figure
histogram(res);
title('Pixel Distribution of 2 means Picture');
xlabel('pixel value');
ylabel('times');

figure
[means, res, ~] = km(4, data);
colormap(gray);
imagesc(reshape(res, [m, n]));

figure
histogram(res);
title('Pixel Distribution of 4 means Picture');
xlabel('pixel value');
ylabel('times');

figure
[means, res, ~] = km(8, data);
colormap(gray);
imagesc(reshape(res, [m, n]));

figure
histogram(res);
title('Pixel Distribution of 8 means Picture');
xlabel('pixel value');
ylabel('times');