function [C_Row, C_Column, Output]=AdaptiveThreshold(in, s, t)


[height, width]=size(in);
Output=ones(height, width);
rad=round(s/2);

PaddingIn=[repmat(in(:,1),1,rad),in, repmat(in(:,width),1,rad)];
PaddingIn=[repmat(PaddingIn(1,:),rad,1);PaddingIn; repmat(PaddingIn(height,:),rad,1)];

SumMax=0;
C_Column=0;
for i=rad+1:width+rad
    ColSum=0;
    for j=rad+1: height+rad
        x1=i-rad+1;
        x2=i+rad;
        y1=j-rad+1;
        y2=j+rad;
        SumValue=sum(sum(PaddingIn(y1:y2, x1:x2)));
        a=double(PaddingIn(j, i))*s*s;
        if(a<SumValue*(1-t/100))
            Output(j-rad, i-rad)=0;          
        else
            Output(j-rad, i-rad)=1;
        end
        
        ColSum=ColSum+1-Output(j-rad, i-rad); 
    end
       if(ColSum>SumMax)
        SumMax=ColSum;
        C_Column=i-rad;
      end
end 

max=0;
for i=31:2:height-30
    Rowsum=0;
    for j=31:2:width-30
        Rowsum=Rowsum+1-Output(i,j);
        if(Rowsum>max)
            max=Rowsum;
            C_Row=i;
        end           
    end
end
end