function feature_set=exhaustiveSearch(H0_1,H1_1,avg)
for i=1:4
    AUC1(1,i)=crossValidation(H0_1(:,i),H1_1(:,i));
    AUC1(2,i)=i;
end
[m,i]=max(AUC1(1,:));
feature_set=AUC1(:,i);
feature_in=feature_set(1);
feature=AUC1(1,:);

count=1;
for i=1:4
    for j=i+1:4
        AUC2(1,count)=crossValidation(H0_1(:,[i,j]),H1_1(:,[i,j]));
        AUC2(2,count)=i;
        AUC2(3,count)=j;
        count=count+1;
    end
end
[m,i]=max(AUC2(1,:));
feature=[feature,AUC2(1,:)];
feature_in=[feature_in,m];
if m>feature_set(1)
    feature_set=AUC2(:,i);
end

count=1;
for i=1:4
    for j=i+1:4
        for k=j+1:4
            AUC3(1,count)=crossValidation(H0_1(:,[i,j,k]),H1_1(:,[i,j,k]));
            AUC3(2,count)=i;
            AUC3(3,count)=j;
            AUC3(4,count)=k;
            count=count+1;
        end
    end
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
    feature_set=AUC4;
    feature_set=[feature_set;1;2;3;4];
end
subplot(1,3,1)
plot(1:length(feature),feature,'-o');
xlabel('Index of feature set');
ylabel('AUC');
title('AUC of considered feature sets with exhaustive search');
count=0.9;
for i=1:4
    text(9,count-i*0.02,['Set',int2str(i),': ',int2str(AUC1(2,i))]);
end
count=count-4*0.02;
for i=1:6
    text(9,count-i*0.02,['Set',int2str(i+4),': ',int2str(AUC2(2:3,i)')]);
end
count=count-6*0.02;
for i=1:4
    text(9,count-i*0.02,['Set',int2str(i+10),': ',int2str(AUC3(2:4,i)')]);
end
count=count-4*0.02;
text(9,count-0.02,['Set',int2str(15),': ',int2str([1,2,3,4])]);
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
