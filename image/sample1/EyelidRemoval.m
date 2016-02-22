%input: 
%PointMatrix    --the coordinates of edge points laying on the pupil.
%output:
%PointMatrixNew --the coordinates of edge points after removing the noise
%points on the eyelid.


function  PointMatrixNew=EyelidRemoval(PointMatrix)

[sorted,~]=insert_sort(PointMatrix(:,1));

%disp(sorted);
number=1;
count=size(PointMatrix,1);
blacklist=zeros(1,count);
id=1;
for k=1:count-1
   if(sorted(k+1)==sorted(k))
        number=number+1;
    else
        if(number>2)
        blacklist(id)=sorted(k);
        id=id+1;
        end
        number=1;
    end
end

blacklist=blacklist(1,1:id-1);
PointMatrixNew=PointMatrix;
idnew=1;
for k=1:count-1
    flag=0;
    for p=1:id-1
         if(PointMatrix(k,1)==blacklist(p))
              flag=1;
              break;
         end
    end
    if(flag==0)
       PointMatrixNew(idnew,:)=PointMatrix(k,:);
       idnew=idnew+1;    
    end
end
PointMatrixNew=PointMatrixNew(1:idnew-1,:);


end