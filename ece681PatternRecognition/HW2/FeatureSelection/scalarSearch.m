function feature_set=scalarSearch(H0_1,H1_1,avg)
    for i=1:4
        AUC1(1,i)=crossValidation(H0_1(:,i),H1_1(:,i));
        AUC1(2,i)=i;
    end
    [m,i]=sort(AUC1(1,:),'descend');
    feature_set=AUC1(:,i(1));
    feature=AUC1(1,:);
    feature_in=feature_set(1);
    
    AUC2(1,1)=crossValidation(H0_1(:,i(1:2)),H1_1(:,i(1:2)));
    AUC2=[AUC2;sort(i(1:2)')];
    feature=[feature,AUC2(1)];
    feature_in=[feature_in,AUC2(1)];
    if AUC2(1)>feature_set(1)
        feature_set=AUC2;
    end
    
    AUC3(1,1)=crossValidation(H0_1(:,i(1:3)),H1_1(:,i(1:3)));
    AUC3=[AUC3;sort(i(1:3)')];
    feature=[feature,AUC3(1)];
    feature_in=[feature_in,AUC3(1)];
    if AUC3(1)>feature_set(1)
        feature_set=AUC3;
    end  
    
    AUC4=crossValidation(H0_1,H1_1);
    AUC4=[AUC4;1;2;3;4];
    feature=[feature,AUC4(1)];
    feature_in=[feature_in,AUC4(1)];
    if AUC4(1)>feature_set(1)
        feature_set=AUC4;
    end    

subplot(1,2,1)
plot(1:length(feature),feature,'-o');
xlabel('Index of feature set');
ylabel('AUC');
title('AUC of considered feature sets with scalar search');
count=0.9;
for i=1:4
    text(5,count-i*0.02,['Set',int2str(i),': ',int2str(i)]);
end
count=count-4*0.02;
text(5,count-0.02,['Set',int2str(5),': ',int2str(AUC2(2:3)')]);
count=count-0.02;
text(5,count-0.02,['Set',int2str(6),': ',int2str(AUC3(2:4)')]);
count=count-0.02;
text(5,count-0.02,['Set',int2str(7),': ',int2str([1,2,3,4])]);

grid on;
subplot(1,2,2)
for i=1:(length(feature_in)-1)
    incre(i)=(feature_in(i+1)-feature_in(i))/feature_in(i);
end
plot([2,3,4],incre,'-o');
hold on;
plot([2,3,4],[avg,avg,avg],'--');
xlabel('Number of features in feature set');
ylabel('Percentage of AUC change');
title('Percentage of AUC change with 2/3/4 features in a group');
legend('Percentage of AUC change','error of cross validation');
grid on;
end