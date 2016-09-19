function AUC=visual_multiclassifier(H0_1,H1_1,n,k)
    Ds_1=[H0_1;H1_1];
    Target_1=zeros(length(H0_1),1);
    Target_1=[Target_1;ones(length(H1_1),1)];
    Classfier=Ds_1;
    Classfier(:,3)=Target_1;
    me(:,1)=mean(H0_1)';me(:,2)=mean(H1_1)';
    variance(:,:,1)=cov(H0_1);variance(:,:,2)=cov(H1_1);
    
    Min=min([H0_1;H1_1]);
    Max=max([H0_1;H1_1]);
    
    if(Min(1)>=0)
        minx=Min(1)*0.8;
    else
        minx=Min(1)*1.2;
    end
    
    if(Min(2)>=0)
        miny=Min(2)*0.8;
    else
        miny=Min(2)*1.2;
    end
    
    if(Max(1)>=0)
        maxx=Max(1)*1.2;
    else
        maxx=Max(1)*0.8;
    end
    
    if(Max(2)>=0)
        maxy=Max(2)*1.2;
    else
        maxy=Max(2)*0.8;
    end
    
    x=linspace(minx,maxx,200);
    
    y=linspace(miny,maxy,200);
    [Surface_x,Surface_y]=meshgrid(x,y);
    
    

    for i=1:200
        for j=1:200
            if(n==0)
                numda(i,j)=runClassfier([Surface_x(i,j),Surface_y(i,j)],Classfier,9);  
            end
            if(n==1)
                numda(i,j)=bayesClassifier([Surface_x(i,j),Surface_y(i,j)]',me,variance);
            end
            if(n==2)
                numda(i,j)=ldaClassifier([Surface_x(i,j),Surface_y(i,j)]',me,variance,H0_1,H1_1);
            end
            if(n==3)
                numda(i,j)=dlrtClassifier([Surface_x(i,j),Surface_y(i,j)]',H0_1,H1_1,k);
            end
        end
    end
    
    imagesc([minx,maxx],[miny,maxy],numda(:,:));
     if(n~=0)
         colormap(hsv);
     end
    if(n==0)
        title('KNN Visualization K=9');
    end
    if(n==1)
        title('Bayes Visualization');
    end
    if(n==2)
        title('FLD Visualization');
    end
    if(n==3)
        title(['DLRT Visualization K=',num2str(k)]);
    end
    xlabel('Feature 1');
    ylabel('Feature 2');
    colorbar;
    hold on;
    plot(Ds_1(Target_1==1,1),Ds_1(Target_1==1,2),'ro','MarkerFaceColor','r')
    plot(Ds_1(Target_1==0,1),Ds_1(Target_1==0,2),'ro','MarkerFaceColor','g')
    
    legend('H1 class','H0 class');
    
    
  
end