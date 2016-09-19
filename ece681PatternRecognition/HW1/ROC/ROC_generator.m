clc
clear
set(figure,'NumberTitle','off','Name','ROC Curve');
H0_1=normrnd(0,1,250,1);
H1_1=normrnd(4,2,250,1);
plotROC(H0_1,H1_1);

H0_2=normrnd(0,1,300,1);
H1_2=normrnd(2,1,300,1);
hold on
plotROC(H0_2,H1_2);

load('HW01rocBlindTestDecisionStatistics.mat');

H1_blind=rocBlindDecStat(rocBlindTarget==1);
H0_blind=rocBlindDecStat(rocBlindTarget==0);
hold on
plotROC(H0_blind,H1_blind);
plot(0:0.01:1,0:0.01:1,'--')
p1=legend('Question1','Question2','ROC BlindTest','location','SouthEast');
set(p1,'Fontsize',10);
title('ROC curve of decision statistics');
xlabel('P_f');
ylabel('P_d');


set(figure,'NumberTitle','off','Name','Question1 pdf');
ksdensity(H0_1);
hold on
ksdensity(H1_1)
xlim([-5 20]);
title('PDF curve of decision statistics in Question1');
xlabel('Decision variable');
legend('H_0','H_1');
set(figure,'NumberTitle','off','Name','Question2 pdf');
ksdensity(H0_2);
hold on
ksdensity(H1_2)
xlim([-5 20]);
title('PDF curve of decision statistics in Question2');
xlabel('Decision variable');
legend('H_0','H_1');
set(figure,'NumberTitle','off','Name','BlindTest pdf');
ksdensity(H0_blind);
hold on 
ksdensity(H1_blind);
xlim([-5 20]);
title('PDF curve of decision statistics in BlindTest');
xlabel('Decision variable');
legend('H_0','H_1');

figure
[b,index]=sort(rocBlindDecStat);
t=rocBlindTarget(index);

plot(find(t==0),b(t==0),'b*','MarkerSize',10)
hold on
plot(find(t==1),b(t==1),'ro','MarkerSize',5)
title('Sorted Decision Statistics');
legend('H0 hypothesis','H1 hypothesis','location','SouthEast');
xlabel('index');
ylabel('Decision statistics value');