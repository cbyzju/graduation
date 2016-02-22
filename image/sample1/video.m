
numfiles=300;
black=zeros(1,numfiles);
FigHandle = figure;
%set(FigHandle, 'Position', [20, 20, 1200, 750]);
t=zeros(1,numfiles);
for k=100:150
filename=sprintf('image%d.txt',k);
data=load(filename,'-ascii');
   
tic;
  %% rough center localization.
[C_Row, C_Column, binary]=FixedThreshold(data);
%[C_Row, C_Column, binary]=AdaptiveThreshold(data, 70, 50);
   
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

if(count<3)
    continue;
end
PointMatrix=PointMatrix(1:count, :);

%% eyelid removal. remove the noise points laying on the eyelid.
PointMatrixNew=EyelidRemoval(PointMatrix);

%% ellipse fitting.
[RoughxCenter, RoughyCenter,RoughxRadius, RoughyRadius, Roughtheta]=fit_ellipse(PointMatrixNew(:,2), PointMatrixNew(:,1));
   
t(k)=toc;

%% show
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
end

