function AUC=plotROC(H0_1,H1_1)
    index=1;
    for beta=min(min(H0_1)*0.8,min(H1_1)*0.8):0.1:max(max(H0_1)*1.2,max(H1_1)*1.2)
        Pd_1(index)=sum(H1_1>=beta)/length(H1_1);
        Pf_1(index)=sum(H0_1>=beta)/length(H0_1);
        index=index+1;
    end
    AUC=-trapz(Pf_1,Pd_1);
    p=plot(Pf_1',Pd_1','LineWidth',4);
