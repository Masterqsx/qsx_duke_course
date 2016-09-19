function AUC=plotROC(H0_1,H1_1)
    index=1;
    min0=min(H0_1);
    min1=min(H1_1);
    max0=max(H0_1);
    max1=max(H1_1);
    mean0=mean(H0_1);
    mean1=mean(H1_1);
    if(min0>=0)
        min0=min0*0.8;
    else
        min0=min0*1.2;
    end
    
    if(min1>=0)
        min1=min1*0.8;
    else
        min1=min1*1.2;
    end
    
    if(max0>=0)
        max0=max0*1.2;
    else
        max0=max0*0.8;
    end
    
    if(max1>=0)
        max1=max1*1.2;
    else
        max1=max1*0.8;
    end
    for beta=min(min0,min1):0.001:max(max0,max1)
        if(mean1>=mean0)
            Pd_1(index)=sum(H1_1>=beta)/length(H1_1);
            Pf_1(index)=sum(H0_1>=beta)/length(H0_1);
        else
            Pd_1(index)=sum(H1_1<=beta)/length(H1_1);
            Pf_1(index)=sum(H0_1<=beta)/length(H0_1);
        end
        index=index+1;
    end
    if(mean1>=mean0)
        AUC=-trapz(Pf_1,Pd_1);  
    else
        AUC=trapz(Pf_1,Pd_1);  
    end
    
    figure;
    p=plot(Pf_1',Pd_1','LineWidth',4);
    xlabel('P_f');
    ylabel('P_d');
