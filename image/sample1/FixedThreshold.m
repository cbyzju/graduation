%input:
%data      --the pixel values martrix of eye image
%output:
%C_Row     --the vertical coordinate of approximate center.
%C_Column  --the horizontal coordinate of approximate center¡£
%binary    --binary scale of eye image.

function [C_Row, C_Column, binary]=FixedThreshold(data)

[row,column]=size(data);
binary=uint8(data);
number=0;
max=0;
C_Column=0;
for j=1:column
    columnSum=0;
    for i=1:row
        if(binary(i,j)<25)
            binary(i,j)=0;
            if(i>31 && i<row-30 && j>31 && j<column-30)
                number=number+1;
                columnSum=columnSum+1;
            end
        else
            binary(i,j)=1;
        end
    end
    if(columnSum>max)
        max=columnSum;
        C_Column=j;
    end           
end
   
    
max=0;
for i=31:2:row-30
    Rowsum=0;
    for j=31:2:column-30
        Rowsum=Rowsum+1-binary(i,j);
        if(Rowsum>max)
            max=Rowsum;
            C_Row=i;
        end           
    end
end
end
   