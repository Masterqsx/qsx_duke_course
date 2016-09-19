function feature_set=sequentialSearch(H0_1,H1_1,avg)
     for i=1:4
        AUC1(1,i)=crossValidation(H0_1(:,i),H1_1(:,i));
        AUC1(2,i)=i;
    end
    [m,i]=max(AUC1(1,:));
    feature_set=AUC1(:,i(1));
    feature_in=feature_set(1);
    feature=AUC1(1,:);
    remain=[1,2,3,4];
    remain=remain(remain~=feature_set(2));
    
    for i=1:3
        auc2=crossValidation(H0_1(:,[feature_set(2),remain(i)]),H1_1(:,[feature_set(2),remain(i)]));
        AUC2(:,i)=[auc2;sort([feature_set(2),remain(i)]')];
    end
    [m,i]=max(AUC2(1,:));
    feature=[feature,AUC2(1,:)];
    feature_in=[feature_in,m];
    if m>feature_set(1)
        feature_set=AUC2(:,i);
    end
    remain=[1,2,3,4];
    remain=remain(remain~=feature_set(2));
    remain=remain(remain~=feature_set(3));
    
    for i=1:2
        auc3=crossValidation(H0_1(:,[feature_set(2:3)',remain(i)]),H1_1(:,[feature_set(2:3)',remain(i)]));
        AUC3(:,i)=[auc3;sort([feature_set(2:3)',remain(i)]')];
    end
    [m,i]=max(AUC3(1,:));
    feature=[feature,AUC3(1,:)];
    feature_in=[feature_in,m];
    if m>feature_set(1)
        feature_set=AUC3(:,i);
    end
    
    AUC4=crossValidation(H0_1,H1_1);
    feature=[feature,AUC4];
    feature_in=[feature_in,AUC4];
    if AUC4>feature_set(1)
        feature_set=[AUC4;1;2;3;4];
    end
subplot(1,3,1)
plot(1:length(feature),feature,'-o');
xlabel('Index of feature set');
ylabel('AUC');
title('AUC of considered feature sets with sequential search');
count=0.9;
for i=1:4
    text(6,count-i*0.02,['Set',int2str(i),': ',int2str(AUC1(2,i))]);
end
count=count-4*0.02;
for i=1:3
    text(6,count-i*0.02,['Set',int2str(i+4),': ',int2str(AUC2(2:3,i)')]);
end
count=count-3*0.02;
for i=1:2
    text(6,count-i*0.02,['Set',int2str(i+7),': ',int2str(AUC3(2:4,i)')]);
end
count=count-2*0.02;
text(6,count-0.02,['Set',int2str(10),': ',int2str([1,2,3,4])]);

grid on;
subplot(1,3,2)
plot([1,2,3,4],feature_in,'-o');
xlabel('Number of features in feature set');
ylabel('AUC');
title('Best AUC with 1/2/3/4 features in a group');
grid on;
subplot(1,3,3)
for i=1:3
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