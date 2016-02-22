

/*
input:
coordinate: the coordinate of edge points on pupil circle.
it format is
[x_1, y_1;
 x_2, y_2;
   .,   .;
   .,   .;   
 x_n, y_n;
   .,   .;
   .,   .;   
 x_N, y_N;
];
*/
#include <math.h>
#include "fit_ellipse.h"
#include "matrix.h"

matrix fit_ellipse(const matrix& coord)
{
    matrix D1=(coord.columnVector(0)*coord.columnVector(0)).appendright(coord.columnVector(0)*coord.columnVector(1)).appendright(coord.columnVector(1)*coord.columnVector(1));
    matrix D2=coord.columnVector(0).appendright(coord.columnVector(1)).appendright(matrix::ones(coord.height(),1));
    matrix S1=matrix::crossProduct(D1.transform(), D1);
    matrix S2=matrix::crossProduct(D1.transform(), D2);
    matrix S3=matrix::crossProduct(D2.transform(), D2);
    matrix T=matrix::crossDivision(S3, S2.transform())*(-1);
    matrix M=S1+matrix::crossProduct(S2, T);
    matrix tmp(M.height(), M.width());
    for(unsigned i=0; i<M.height(); i++)
    {
    	for(unsigned j=0; j<M.width(); j++)
    	{
            if(i==0)
                tmp.setvalue(i,j, 0.5*M.getvalue(2,j));
            else if(i==1)
                tmp.setvalue(i,j, -M.getvalue(1,j));
            else
                tmp.setvalue(i,j, 0.5*M.getvalue(0,j));
    	}
    }

    matrix eigv=tmp.eigenvector();
    double cond=0;
    matrix a1;
    for(unsigned j=0; j<M.width(); j++)
    {         
           cond=4*eigv.getvalue(0, j)*eigv.getvalue(2, j)-eigv.getvalue(1, j)*eigv.getvalue(1, j);
    	   if(cond>0)
    	    a1=eigv.columnVector(j);
    }
    matrix under=matrix::crossDivision(T, a1);
    double a=a1.getvalue(0,0);
    double b=a1.getvalue(0,1)/2;
    double c=a1.getvalue(0,2);
    double d=under.getvalue(0,0)/2;
    double f=under.getvalue(0,1)/2;
    double g=under.getvalue(0,2);

    //ellipse center
    double num=b*b-a*c;
    double XCenter=(c*d-b*f)/num;
    double YCenter=(a*f-b*d)/num;

    //ellipse angle of rotation.
    double theta=0.5*atan(2*b/(a-c));

    //ellipse axis length
    double up=2*(a*f*f+c*d*d+g*b*b-2*b*d*f-a*c*g);
    double down1=(b*b-a*c)*((c-a)*sqrt(1+4*b*b/((a-c)*(a-c)))-(c+a));
    double down2=(b*b-a*c)*((a-c)*sqrt(1+4*b*b/((a-c)*(a-c)))-(c+a));
    double xRadius=sqrt(up/down1);
    double yRadius=sqrt(up/down2);

    matrix parameter(1,5);
    parameter.setvalue(0, 0, XCenter);
    parameter.setvalue(0, 1, YCenter);
    parameter.setvalue(0, 2, theta);
    parameter.setvalue(0, 3, xRadius);
    parameter.setvalue(0, 4, yRadius);
    return parameter;
}