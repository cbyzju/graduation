function [unsorted, index]=insert_sort(unsorted)
index=zeros(1,length(unsorted));
   for i=1:length(unsorted)
       index(i)=i;
   end
   
   for i=2:length(unsorted)
       if(unsorted(i)<unsorted(i-1))
           tmp=unsorted(i);
           j=i-1;
           while(j>0 && unsorted(j)>tmp) 
               unsorted(j+1)=unsorted(j);
               k=index(j+1);
               index(j+1)=index(j);
               index(j)=k;
               j=j-1;
           end
               unsorted(j+1)=tmp; 
      end              
   end
end