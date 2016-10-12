close all
clc
clear



load tictactoe
data = datapreprocess(tictactoe);
[AUC_g, AUC_s, AUC_c, AUC_r, AUC_b] = crossValid(data);
nestCrossValid(data);
mAUC_b = mean(AUC_b);
mAUC_c = mean(AUC_c);
mAUC_g = mean(AUC_g);
mAUC_r = mean(AUC_r);
mAUC_s = mean(AUC_s);

dAUC_b = std(AUC_b);
dAUC_c = std(AUC_c);
dAUC_g = std(AUC_g);
dAUC_r = std(AUC_r);
dAUC_s = std(AUC_s);