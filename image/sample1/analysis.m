
filename=sprintf('image%d.txt',79);
 data=load(filename,'-ascii');

    %%imshow(uint8(data));
    %%return;
    
    %% rough center localization.
    binary=uint8(data);
    number=0;
    max=0;
    C_Column=0;
  for j=1:318
      columnSum=0;
       for i=1:198
           if(binary(i,j)<30)
               binary(i,j)=0;
               if(j>30 && j<288)
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
   black(k)=number;         
    
   max=0;
   for i=31:168
       Rowsum=0;
       for j=31:288
           Rowsum=Rowsum+1-binary(i,j);
           if(Rowsum>max)
               max=Rowsum;
               C_Row=i;
           end           
       end
   end
   
   
  %% swimming algorithm.
   %%% Swim Algorithm: get the points on the pupil ellipse %%%
row=198;
column=318;
degree=12;
PointMatrix=zeros(360/degree, 2);
averageDistance=0;
count=0;
for angle=0:degree:359
    R_old=3;
    x_old=C_Row-round(R_old*sind(angle));
    y_old=C_Column+round(R_old*cosd(angle));
    while(x_old>0 && x_old<row && y_old>0 && y_old<column && binary(x_old,y_old)<1)
             R_old=R_old+1;
             x_old=C_Row-round(R_old*sind(angle));
             y_old=C_Column+round(R_old*cosd(angle));
    end
 
           count=count+1;
           PointMatrix(count,1)=x_old;
           PointMatrix(count,2)=y_old;
end

PointMatrix=PointMatrix(1:count, :);


   %% ellipse fitting.
   
[RoughxCenter, RoughyCenter,RoughxRadius, RoughyRadius, Roughtheta]=fit_ellipse(PointMatrix(:,2), PointMatrix(:,1));
subplot(1,2,1);imshow(uint8(data)); title(filename);impixelinfo;
subplot(1,2,2);imshow(uint8(binary));  %%hold on;h=plot(C_Column, C_Row,'*');
hold on; plot(PointMatrix(:,2), PointMatrix(:,1), '.','MarkerSize',10);
   
R=0:0.01:2*pi;
RoughxRadius=RoughxRadius+1;
RoughyRadius=RoughyRadius+1;
xx = RoughxCenter + RoughxRadius*cos(R)*cos(Roughtheta) - RoughyRadius*sin(R)*sin(Roughtheta);
yy = RoughyCenter + RoughxRadius*cos(R)*sin(Roughtheta) + RoughyRadius*sin(R)*cos(Roughtheta);
%%plot(x, y ,'.');axis([1 800 1 600]);hold on;
hold on; plot(xx,yy);
hold on; plot(RoughxCenter, RoughyCenter, 'g+','MarkerSize',8);


sum=zeros(1,198);
for i=1:198
    for j=1:318
        sum(i)=sum(i)+double(binary(i,j));
    end
    sum(i)=sum(i)/318;
end
figure;plot(sum,'linewidth',2);
set(gcf,'color','white');
%title('Horizontal Projection');
xlabel('the i-th row, i=1,.....,M');
ylabel('H(i)');

sum=zeros(1,318);
for j=1:318
   for i=1:198
        sum(j)=sum(j)+double(binary(i,j));
    end
    sum(j)=sum(j)/198;
end
figure;plot(sum,'linewidth',2);
set(gcf,'color','white');
%title('Vertical Projection');
xlabel('the j-th column, i=1,.....,N');
ylabel('V(j)');

   
figure;
plot(PointMatrix(:,1),'.','Markersize',12);xlabel('edge points');ylabel('vertical coordinates');
exportfig(gcf,'removal.eps','bounds','tight');
set(gcf,'color','white');
%set (gcf,'Position',[0,0,318,198]);
hold on;plot(0:60,ones(1,61)*52,'r','linewidth',2);
hold on;plot(0:60,ones(1,61)*101,'-.g','linewidth',2);
hold on;plot(0:60,ones(1,61)*115,'c:','linewidth',2);



   