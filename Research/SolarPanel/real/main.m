clc
clear

load('TestingBootstrap.mat')
load('TrainingBootstrap.mat')
warning('off','all')
warning

a = DsTrainBootstrap(DsTrainBootstrap(:, 2) == 0, 1);
b = DsTrainBootstrap(DsTrainBootstrap(:, 2) == 1, 1);
edges = linspace(0,1,101);
c = histcounts(a,edges);
centers = (edges(1:end-1)+edges(2:end))/2;
dx = mean(diff(edges));
d = histcounts(b,edges);
c = c./sum(c*dx);
d = d./sum(d*dx);

bar(centers',c,1,...
    'FaceColor','b',...
    'FaceAlpha',0.5)
hold on
bar(centers',d',1,...
    'FaceColor','r',...
    'FaceAlpha',0.5)
hold off
legend('H0','H1')
xlabel('Decision Statistics', 'FontWeight', 'bold', 'fontsize', 12);
ylabel('Numbers of Values', 'FontWeight', 'bold', 'fontsize', 12);
title('The Distribution of Aerial Imagery Dataset', 'FontWeight', 'bold', 'fontsize', 12);
legend('\fontsize {10}{\bfH_0}', '\fontsize {10}{\bfH_1}')
set(gca, 'fontsize', 12);
% figure
% methodCompare(DsTestBootstrap, DsTrainBootstrap);
