%================================================
%             ECE 581 Hmwk7
%             Shengxin Qian
%================================================
clear
set(figure,'NumberTitle','off','Name','abc');
for Es=[1,2,4,16]                                   %keep variance of noise=1 and set Es=1,2,4,16
    s=signal_image_generator(1024,Es);              %generate signal image according to required Es

    sum_varianceH0=sum_variance_H0(s,1024,1);       %calculate the required variance(H0) for algorithm in Hmwk2 
    sum_varianceH1=sum_variance_H1(s,1024,1);       %calculate the required variance(H1) for algorithm in Hmwk2 
    sum_meanH1=sum_mean_H1(s,1024,1);               %calculate the required mean(H1) for algorithm in Hmwk2 
    
    trial_number=5000;                              %the experiment time
    z_H0=normrnd(0,sqrt(sum_varianceH0),1,trial_number);%generate the output(H0) of algorithm in Hmwk2
    z_H1=normrnd(sum_meanH1,sqrt(sum_varianceH1),1,trial_number);%generate the output(H1) of algorithm in Hmwk2

    lnlambda_H0=z_H0-0.5*sum_meanH1;                %the lnlambda_H0 output according to the problem 5-1
    lnlambda_H1=z_H1-0.5*sum_meanH1;                %the lnlambda_H1 output according to the problem 5-1

    index=1;
    for beta=min(lnlambda_H0):0.01:max(lnlambda_H1) 
        Pf(index)=sum(lnlambda_H0>=beta);           %Pf in experiment
        Pd(index)=sum(lnlambda_H1>=beta);           %Pd in experiment
        Pft(index)=1-normcdf(beta,-0.5*sum_meanH1,sqrt(sum_varianceH0));%Pf theoretically
        Pdt(index)=1-normcdf(beta,0.5*sum_meanH1,sqrt(sum_varianceH1)); %Pd theoretically
        index=index+1;
    end
    
    hold on
    plot(Pf/trial_number,Pd/trial_number);
    plot(Pft,Pdt);
end