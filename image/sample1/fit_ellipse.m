function [xCenter, yCenter, xRadius, yRadius, theta]=fit_ellipse(x, y)

%     Direct ellipse fitting, proposed in article
%     Hal?r R, Flusser J. "Numerically stable direct least squares fitting of ellipses"[C]
%     Proc. 6th International Conference in Central Europe on Computer Graphics and Visualization. 
%     WSCG. 1998, 98: 125-132.
%
%     Our code is based on a numerically stable version
%     of this fit published by R. Halir and J. Flusser
%
%     Input: These two values come from the output of LineRemove function.
%     x: coordinate value along x-axis
%     y: coordinate value along y-axis
%
%     Output:
%     xCenter: the center coordinate value along x-axis
%     yCenter: the center coordinate value along y-axis
%     xRadius: the radius value along x-axis
%     xRadius: the radius value along y-axis

%     This is a fast non-iterative ellipse fit.  It returns ellipses only, even if points are
%     better approximated by a hyperbola. It is somewhat biased toward smaller ellipses.




D1=[x.^2, x.*y, y.^2];
D2=[x, y, ones(size(x))];
S1=D1'*D1;
S2=D1'*D2;
S3=D2'*D2;
T=-inv(S3)*S2';
M=S1+S2*T;
M=[M(3,:)./2; -M(2, :); M(1, :)./2];
[evec, ~]=eig(M);
cond=4*evec(1, :).*evec(3, :)-evec(2, :).^2;
a1=evec(:, find(cond>0));
A=[a1;T*a1];

a=A(1);
b=A(2)/2;
c=A(3);
d=A(4)/2;
f=A(5)/2;
g=A(6);
%% ellipse Center
num=b^2-a*c;
xCenter=(c*d-b*f)/num;
yCenter=(a*f-b*d)/num;

%% ellipse angle of rotation
theta=0.5*atan(2*b/(a-c));


%% ellipse axis length
up = 2*(a*f*f+c*d*d+g*b*b-2*b*d*f-a*c*g);
down1=(b*b-a*c)*((c-a)*sqrt(1+4*b*b/((a-c)*(a-c)))-(c+a));
down2=(b*b-a*c)*((a-c)*sqrt(1+4*b*b/((a-c)*(a-c)))-(c+a));
xRadius=sqrt(up/down1);
yRadius=sqrt(up/down2);

end

