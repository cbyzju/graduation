%%����һ���۲�ͼƬ�����ڲ���֮��

filename=sprintf('image%d.txt',10);
data=load(filename,'-ascii');
   
tic;
  %% rough center localization.
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
   
  %% swimming algorithm.
   %%% Swim Algorithm: get the points on the pupil ellipse %%%
[row,column]=size(data);
degree=6;
PointMatrix=zeros(360/degree, 2);
count=0;
for angle=0:degree:359
    R_old=15;  %% initial radius for the searching.
    x_old=C_Row-round(R_old*sind(angle));
    y_old=C_Column+round(R_old*cosd(angle));
    if(x_old>0 && x_old<row && y_old>0 && y_old<column && binary(x_old,y_old)<1)
         while(x_old>0 && x_old<row && y_old>0 && y_old<column && binary(x_old,y_old)<1) %%û�����߽磬û�����׵㣬�ͼ�������
             R_old=R_old+1;
             x_old=C_Row-round(R_old*sind(angle));
             y_old=C_Column+round(R_old*cosd(angle));        
           
         end    
             count=count+1;
             PointMatrix(count,1)=x_old;
             PointMatrix(count,2)=y_old;
             
         if(x_old==0 || x_old==row || y_old==0 || y_old==column) %% ��������������У������˱߽磬�ͼ�����һ��angle��ѭ��
                 count=count-1;
                 continue;
         end    
           
         for r=R_old+1:R_old+12 %%�������׵�֮���ټ�������һ�ξ��룬��������˱߽磬��ֱ������������
             %%�߽��ϵĵ㻹�Ǳ���������������ڵ㣬��֮ǰ��¼����������������ϵı߽���Ƴ���
             x_futher=C_Row-round(r*sind(angle));
             y_futher=C_Column+round(r*cosd(angle));
             if(x_futher<=0 || x_futher>=row || y_futher<=0 || y_futher>=column)
                 break;
             end
             if(binary(x_futher,y_futher)<1)
                 count=count-1;                  
                 break;
             end
         end               
    end
end

PointMatrix=PointMatrix(1:count, :);

%% eyelid removal. remove the noise points laying on the eyelid.
[sorted,~]=insert_sort(PointMatrix(:,1));
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

%% ellipse fitting.
[RoughxCenter, RoughyCenter,RoughxRadius, RoughyRadius, Roughtheta]=fit_ellipse(PointMatrixNew(:,2), PointMatrixNew(:,1));
   
t(k)=toc;

%% show

FigHandle = figure;
subplot(1,2,1);imshow(uint8(data)); title(filename);impixelinfo;
subplot(1,2,2); 
%imshow(uint8(binary),'border','tight','initialmagnification','fit');
%set (gcf,'Position',[0,0,318,198]);
imshow(255*uint8(binary)); impixelinfo; hold on;
plot(PointMatrixNew(:,2), PointMatrixNew(:,1), '.','MarkerSize',10);hold on;

R=0:0.01:2*pi;
xx = RoughxCenter + RoughxRadius*cos(R)*cos(Roughtheta) - RoughyRadius*sin(R)*sin(Roughtheta);
yy = RoughyCenter + RoughxRadius*cos(R)*sin(Roughtheta) + RoughyRadius*sin(R)*cos(Roughtheta);
plot(xx,yy,'linewidth',2); hold on;
plot(RoughxCenter, RoughyCenter, 'g+','MarkerSize',12);

drawnow('limitrate');%%ˢ���Կ�����


