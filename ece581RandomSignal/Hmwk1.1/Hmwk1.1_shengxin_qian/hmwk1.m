%==========================
%   ECE 581 Homework1
%      Shengxin Qian
%==========================
%   Workspace clear
%==========================
clear 
clear all
nu=1;
set(figure,'NumberTitle','off','Name','Part(a),(b)'); %set figure name

%***********************************************************

%==========================
%   Original noise-free image generation
%==========================
Image_energy=4; %input signal energy of image
Noise_free=eye(1024)*sqrt(Image_energy/1024);%generate noise free image
subplot(1,3,nu);  %put the original noise free image on the first position
imshow(Noise_free)  %show the original noise free image
title('Noise free/Energy:4'); %set subplot name
nu=nu+1;
%==========================
%   (0,1) Gaussian white Noise generate 
%==========================
Noise0=normrnd(0,1,1024);   %Generate (0,1) Gaussian white Noise0
Noise_add=Noise0+Noise_free;%Mix Noise0 and original noise-free image
subplot(1,3,nu);
imshow(Noise0) %show the noise alone image
title('Noise alone/Energy:1'); 
nu=nu+1;
%==========================
%   (0,1) Gaussian white Noise mix
%==========================
subplot(1,3,nu);
imshow(Noise_add)   %show the noise mix image
title(['Noise add/SNR: ',num2str(10*log10(4)),' dB']);
nu=nu+1;

%****************************************************************

%==========================
%   Image energy change and output image comparision
%==========================
for i=1:4
    set(figure,'NumberTitle','off','Name',['Image energy change',num2str(i)]) ; 
    nu=1;
%==========================
%   Energy changed noise-free image generation
%==========================
    Energy_change_free(:,:,i)=eye(1024)*sqrt(i*2500/1024); %set the image energy with i*2500
    subplot(1,3,nu);
    imshow(Energy_change_free(:,:,i)); %show noise free image
    title(['Noise free/Energy:',num2str(i*2500)]); %show the energy in the subplot title
    nu=nu+1;
%==========================
%   (0,1) Gaussian white Noise generate
%==========================
    Noise_nochange(:,:,i)=normrnd(0,1,1024); %set the noise energy with constant 1
    subplot(1,3,nu);
    imshow(Noise_nochange(:,:,i)) %show noise alone image
    title(['Noise alone/Energy:',num2str(1)]); %show the energy in the subplot title
    nu=nu+1;
%==========================
%   (0,1) Gaussian white Noise mix
%==========================    
    Energy_change_add(:,:,i)=Noise_nochange(:,:,i)+Energy_change_free(:,:,i); %mix the noise and noise-free image
    subplot(1,3,nu);
    imshow(Energy_change_add(:,:,i)); %show noise mix image
    title(['Noise add/SNR: ',num2str(10*log10(i*2500)),' dB']); %show the SNR in the subplot title
    nu=nu+1;
end
%**************************************************************

%==========================
%   Noise energy change and output image comparision
%==========================
for i=1:4
    set(figure,'NumberTitle','off','Name',['Noise energy change',num2str(i)]) ; 
    nu=1;
%==========================
%   Energy changed noise-free image generation
%==========================
    Noise_change_free(:,:,i)=eye(1024)*sqrt(1024/1024); %set the image energy with constant 2500
    subplot(1,3,nu);
    imshow(Noise_change_free(:,:,i));
    title(['Noise free/Energy:',num2str(1024)]); %show the energy in the subplot title
    nu=nu+1;
%==========================
%   Energy changed Gaussian white Noise generate
%==========================
    Noise(:,:,i)=normrnd(0,1/1.5^(i-1),1024); %set the noise energy with (1/1.5^(i-1))^2
    subplot(1,3,nu);
    imshow(Noise(:,:,i))
    title(['Noise alone/Energy:',num2str((1/1.5^(i-1))^2)]);%show the energy in the subplot title
    nu=nu+1;
%==========================
%   Energy changed Gaussian white Noise mix
%==========================    
    Noise_change_add(:,:,i)=Noise(:,:,i)+Noise_change_free(:,:,i); 
    subplot(1,3,nu);
    imshow(Noise_change_add(:,:,i));
    title(['Noise add/SNR: ',num2str(10*log10(1024*(1.5^(i-1))^2)),' dB']);%show the SNR in the subplot title
    nu=nu+1;
end
Best_energy_change_add=(Energy_change_add(:,:,1).*(ones(1024)-eye(1024)))+eye(1024);
set(figure,'NumberTitle','off','Name','Best possible image energy change solution');
imshow(Best_energy_change_add);

