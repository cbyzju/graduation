#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

using namespace std;

//**********constructor and deconstructor****************//
matrix::matrix()
{
  
}

matrix::matrix(const matrix &ref)
{
	vec=ref.vec;
}


matrix::matrix(unsigned height, unsigned width)
{
	 
	 vector< vector<double> > temp(height, vector<double>(width));
	 vec=temp;
}

matrix::~matrix()
{

}


//*************operator overload***********************//
//1). 输出流operator<<重载
ostream& operator<<(ostream &os, const matrix& input)
{
	os<<"height: "<<input.height()<<" width: "<<input.width()<<"\n"<<"Matrix value: "<<"\n";
	for(unsigned i=0; i<input.height(); i++)
	{
		for(unsigned j=0; j<input.width(); j++)
		{
			os<<setiosflags(ios::fixed);
		    os<<setprecision(5)<<setw(9)<<input.getvalue(i,j);
		}
		os<<"\n";
	}
	return os;

}




//2). 赋值运算符operator=重载
matrix& matrix::operator=(const matrix &input)
{
      (*this).vec=input.vec;
      return *this;
}

//3). 赋值运算符operator+重载
//这里不能返回Temp的引用，因为Temp是函数局部变量，会在函数调用结束之后，被销毁
//若依旧想返回引用，则需要将Temp定义为全局变量。
matrix matrix::operator+(const matrix &input) const
{
	vector< vector<double> > temp(input.height(), vector<double>(input.width()));
    matrix Temp(temp);
    if((*this).height()!=input.height())
	{
		cerr<<"Addtion is not allowed, height of these two matrix is not matched, please check it!"<<endl;
		exit(1);
	}
	else if((*this).width()!=input.width())
	{
		cerr<<"Addtion is not allowed, width of these two matrix is not matched, please check it!"<<endl;
		exit(2);
	}

	for(unsigned i=0; i<input.height();i++)
		for(unsigned j=0; j<input.width();j++)
			Temp.vec[i][j]=(*this).getvalue(i,j)+input.getvalue(i,j);
      return Temp;
}


//4). 赋值运算符operator+=重载
matrix& matrix::operator+=(const matrix &input)
{
      *this=*this+input;
      return *this;
}


//5). 赋值运算符operator-重载
matrix matrix::operator-(const matrix &input) const
{
	vector< vector<double> > temp(input.height(), vector<double>(input.width()));
    matrix Temp(temp);
    if((*this).height()!=input.height())
	{
		cerr<<"Substraction is not allowed, height of these two matrix is not matched, please check it!"<<endl;
		exit(1);
	}
	else if((*this).width()!=input.width())
	{
		cerr<<"Substraction is not allowed, width of these two matrix is not matched, please check it!"<<endl;
		exit(2);
	}

	for(unsigned i=0; i<input.height();i++)
		for(unsigned j=0; j<input.width();j++)
			Temp.setvalue(i,j, (*this).getvalue(i,j)-input.getvalue(i,j));
      return Temp;
}


//6). 赋值运算符operator-=重载
matrix& matrix::operator-=(const matrix &input)
{
      *this=*this-input;
      return *this;
}

//7). 赋值运算符operator*重载

//7.1) scalar multiplication
matrix matrix::operator*(const double input) const
{
	vector< vector<double> > temp(height(), vector<double>(width()));
    matrix Temp(temp);
   
	for(unsigned i=0; i<height();i++)
		for(unsigned j=0; j<width();j++)
			Temp.vec[i][j]=(*this).getvalue(i,j)*input;
      return Temp;
}



// 7.2) matrix inner multiplication
matrix matrix::operator*(const matrix &input) const
{
	vector< vector<double> > temp(input.height(), vector<double>(input.width()));
    matrix Temp(temp);
    if((*this).height()!=input.height())
	{
		cerr<<"Multiplication is not allowed, height of these two matrix is not matched, please check it!"<<endl;
		exit(1);
	}
	else if((*this).width()!=input.width())
	{
		cerr<<"Multiplication is not allowed, width of these two matrix is not matched, please check it!"<<endl;
		exit(2);
	}

	for(unsigned i=0; i<input.height();i++)
		for(unsigned j=0; j<input.width();j++)
			Temp.vec[i][j]=(*this).getvalue(i,j)*input.getvalue(i,j);
      return Temp;
}



//8). 赋值运算符operator*=重载
matrix& matrix::operator*=(const matrix &input)
{
      *this=*this*input;
      return *this;
}


//9). 赋值运算符operator/重载


//9.1) scalar division
matrix matrix::operator/(const double input) const
{
	vector< vector<double> > temp(height(), vector<double>(width()));
    matrix Temp(temp);

     //scalar division
    if(input==0)
    {
    	cerr<<"Divide by 0 is allowed, please check it!"<<endl;
		exit(1);
    }else
    {
    	for(unsigned i=0; i<height();i++)
		for(unsigned j=0; j<width();j++)
			Temp.vec[i][j]=(*this).getvalue(i,j)/input;
      return Temp;
    }
}


//9.1) matrix division
matrix matrix::operator/(const matrix &input) const
{
	vector< vector<double> > temp(input.height(), vector<double>(input.width()));
    matrix Temp(temp);

    if((*this).height()!=input.height())
	{
		cerr<<"Division is not allowed, height of these two matrix is not matched, please check it!"<<endl;
		exit(1);
	}
	else if((*this).width()!=input.width())
	{
		cerr<<"Division is not allowed, width of these two matrix is not matched, please check it!"<<endl;
		exit(2);
	}

	for(unsigned i=0; i<height();i++)
		for(unsigned j=0; j<width();j++)
			Temp.vec[i][j]=(*this).getvalue(i,j)/input.getvalue(i,j);
      return Temp;
}


//10). 赋值运算符operator/=重载
matrix& matrix::operator/=(const matrix &input)
{
      *this=*this/input;
      return *this;
}


matrix matrix::transform() const
{
	vector< vector<double> > temp(width(), vector<double>(height()));
    matrix Temp(temp);
    for(unsigned i=0; i<width();i++)
		for(unsigned j=0; j<height();j++)
			Temp.vec[i][j]=getvalue(j,i);
      return Temp;

}


 matrix matrix::rowVector(const unsigned i) const
 {
 	if(i>=height())
 	{
 		cerr<<"fetch rowVector, index is beyond the width of matrix!!!"<<endl;
 		exit(3);
 	}
 	vector< vector<double> > temp(1, vector<double>(width()));
    matrix Temp(temp);
    for(unsigned j=0; j<width(); j++)
    	Temp.vec[0][j]=getvalue(i,j);    	
 	return Temp;
 }


matrix matrix::crossProduct(const matrix& A, const matrix& B)
{
	if(A.width()!=B.height())
	{
	   cerr<<"fMatrix Multiplication, size is not matching, please check it!!!"<<endl;
 		exit(5);
	}
	vector< vector<double> > temp(A.height(), vector<double>(B.width()));
    matrix Temp(temp);
    for(unsigned i=0; i<Temp.height(); i++)
    	for(unsigned j=0; j<Temp.width(); j++)
    		Temp.setvalue(i,j,(A.rowVector(i)*(B.columnVector(j).transform())).sum());

    return Temp;
}



 matrix matrix::columnVector(const unsigned j) const
 {
 	if(j>=width())
 	{
 		cerr<<"fetch columnVector, index is beyond the height of matrix!!!"<<endl;
 		exit(5);
 	}
    vector< vector<double> > temp(height(), vector<double>(1));
    matrix Temp(temp);
    for(unsigned i=0; i<height(); i++)
    	Temp.setvalue(i, 0, getvalue(i,j)); 	
    return Temp;
 }


/* assume A is a matrix, it can be denoted as A=LU, where L is lower triangular matrix, and U is upper triangular matrix.
Use a 4 dimensional matrix as an example.
A=[a00, a01, a02, a03;          L=[l00, l01, l02, l03;              U=[u00, u01, u02, u03;
   a10, a11, a12, a13;             l10, l11, l12, l13;                 u10, u11, u12, u13;
   a20, a21, a22, a23;             l20, l21, l22, l23;                 u20, u21, u22, u23;
   a30, a31, a32, a33;]            l30, l31, l32, l33;]                u30, u31, u32, u33;]

we can get N*N equations, and N*N+N unkown coefficients, so here we are invited to specify N of the unkowns aritrarity and then 
try to solve for others. here assume l_ii=1 (i=0, N-1).

when i>j, we can calculate the coeffients of lower triangular matrix:  l_ij=(a_ij-sum_{k=0}^{j-1)(l_ik*u_kj)})/u_jj.

when i<j, we can calculate the coeffients of upper triangular matrix:  u_ij=a_ij-sum_{k=0}^{i-1}(l_ik*u_kj).

the complexity of LU decomposition  is O(n^3), which is better than Gaussian ellination.
  
*/
void matrix::LUD(matrix& lower, matrix& upper) const
{
	if(height()!=width())
	{
		cerr<<"It is not a square matrix, please check it!!!"<<endl;
		exit(3);
	}
	for(unsigned i=0; i<height(); i++)
		for(unsigned j=0; j<width(); j++)
		{
			if(i==j)
				lower.vec[i][j]=1;
			else
			{
				lower.vec[i][j]=0;
				upper.vec[i][j]=0;
			}

			if(i>j)  //calculate the coeffients of lower triangular matrix.
			{
				double sum=0;
				for(unsigned k=0; k<j; k++)
					sum=sum+lower.vec[i][k]*upper.vec[k][j];
				lower.vec[i][j]=((*this).vec[i][j]-sum)/(upper.vec[j][j]);
			}
			else if(i<=j) //calculate the coeffients of upper triangular matrix.
			{
				upper.vec[i][j]=(*this).getvalue(i,j);
				for(unsigned k=0; k<i; k++)
					upper.vec[i][j]=upper.vec[i][j]-lower.vec[i][k]*upper.vec[k][j];
			}
		}
}


//In linear algebra, the determinant is a useful value that can be computed from the elements of a square matrix. The determinant of a matrix A is denoted det(A)
double matrix::det() const
{
	matrix lower((*this));
	matrix upper((*this));
	(*this).LUD(lower, upper);    
    double product=1;
    for(unsigned k=0; k<height(); k++)
    	product=product*upper.getvalue(k,k);
    return product;
}



//back substitution.
matrix matrix::crossDivision(const matrix& A, const matrix& B)
{
      
      matrix y(A.width(), B.width());
      matrix lower(A);
      matrix upper(A);
      A.LUD(lower, upper);
      for(unsigned j=0; j< y.width(); j++)
      {
      	double sumvalue;
      	for(unsigned i=0; i<y.height(); i++)
      	{
      		if(i==0)
      			y.vec[0][j]=B.vec[0][j]/lower.vec[0][0];
      		else
      		{
      		    sumvalue=0;
      		    for(unsigned k=0; k<i; k++)
      			      sumvalue+=lower.vec[i][k]*y.vec[k][j];
      		    y.vec[i][j]=(B.vec[i][j]-sumvalue)/lower.vec[i][i];
      	    }
      	}
      }

      matrix x(A.width(), B.width());
      for(unsigned j=0; j< x.width(); j++)
      {
      	double sumvalue;
      	for(unsigned i=x.height(); i>0; i--)
      	{
      		if(i==x.height())
      		{
      			x.vec[i-1][j]=y.vec[i-1][j]/upper.vec[i-1][i-1];
      		}

      		else
      		{
      		   sumvalue=0;
      		   for(unsigned k=i; k<upper.width(); k++)
      			   sumvalue+=upper.vec[i-1][k]*x.vec[k][j];
      		    x.vec[i-1][j]=(y.vec[i-1][j]-sumvalue)/upper.vec[i-1][i-1];
      	    }
      	}
      }

      return x;
  }



matrix matrix::inverse() const
{
    if((*this).det()==0)
    {
    	cerr<<"this is a not full matrix, inverse is impossible!!!"<<endl;
    	exit(1);
    }

    matrix identity(height(),width());
    for(unsigned i=0; i<height(); i++)
    {
 		for(unsigned j=0; j<width(); j++)
 		{
 			if(i==j)
    	     identity.setvalue(i,j,1);
    	    else
    	 	 identity.setvalue(i,j,0);
 		}
 	}

   return  matrix::crossDivision((*this), identity);
 

}



matrix matrix::hessenberg() const
{
      matrix u(2,1);
      matrix sub(2,2);
      u.vec[0][0]=(*this).vec[1][0]+sqrt((*this).vec[1][0]*(*this).vec[1][0]+(*this).vec[2][0]*(*this).vec[2][0]);
      u.vec[1][0]=(*this).vec[2][0];
      matrix tmp(crossProduct(u, u.transform())/(crossProduct(u.transform(),u).vec[0][0]));
      sub.setvalue(0,0,1-2*tmp.vec[0][0]);
      sub.setvalue(0,1, -2*tmp.vec[0][1]);
      sub.setvalue(1,0, -2*tmp.vec[1][0]);
      sub.setvalue(1,1,1-2*tmp.vec[1][1]);

      matrix h(3,3);
      for(unsigned i=0; i<3; i++)
      {
      	for(unsigned j=0; j<3; j++)
      	{
      		if(i==0 || j==0)
      			h.vec[i][j]=0;
      		else
      			h.vec[i][j]=sub.vec[i-1][j-1];      		
      	}
      }
      h.vec[0][0]=1;

      //return h;
      return crossProduct(crossProduct(h,(*this)),h);
}
    


matrix matrix::givensrotate() const
{
	matrix R1(3,3);
	R1.vec[0][0]=(*this).vec[0][0]/sqrt((*this).vec[0][0]*(*this).vec[0][0]+(*this).vec[1][0]*(*this).vec[1][0]);
	R1.vec[0][1]=(*this).vec[1][0]/sqrt((*this).vec[0][0]*(*this).vec[0][0]+(*this).vec[1][0]*(*this).vec[1][0]);
	R1.vec[1][0]=-R1.vec[0][1];
	R1.vec[1][1]= R1.vec[0][0];
	R1.vec[2][2]=1;

	matrix Rtmp(crossProduct(R1,(*this)));

	matrix R2(3,3);
	R2.vec[0][0]=1;
	R2.vec[1][1]=Rtmp.vec[1][1]/sqrt(Rtmp.vec[1][1]*Rtmp.vec[1][1]+Rtmp.vec[2][1]*Rtmp.vec[2][1]);
	R2.vec[1][2]=Rtmp.vec[2][1]/sqrt(Rtmp.vec[1][1]*Rtmp.vec[1][1]+Rtmp.vec[2][1]*Rtmp.vec[2][1]);
	R2.vec[2][1]=-R2.vec[1][2];
	R2.vec[2][2]= R2.vec[1][1];

	return crossProduct(crossProduct(crossProduct(crossProduct(R2,R1),(*this)),R1.transform()), R2.transform());
}


matrix matrix::eigenvector_iteration(matrix& tmp)
{
	matrix R1(3,3);
	R1.vec[0][0]=tmp.vec[0][0]/sqrt(tmp.vec[0][0]*tmp.vec[0][0]+tmp.vec[1][0]*tmp.vec[1][0]);
	R1.vec[0][1]=tmp.vec[1][0]/sqrt(tmp.vec[0][0]*tmp.vec[0][0]+tmp.vec[1][0]*tmp.vec[1][0]);
	R1.vec[1][0]=-R1.vec[0][1];
	R1.vec[1][1]= R1.vec[0][0];
	R1.vec[2][2]=1;

	matrix Rtmp(crossProduct(R1,tmp));

	matrix R2(3,3);
	R2.vec[0][0]=1;
	R2.vec[1][1]=Rtmp.vec[1][1]/sqrt(Rtmp.vec[1][1]*Rtmp.vec[1][1]+Rtmp.vec[2][1]*Rtmp.vec[2][1]);
	R2.vec[1][2]=Rtmp.vec[2][1]/sqrt(Rtmp.vec[1][1]*Rtmp.vec[1][1]+Rtmp.vec[2][1]*Rtmp.vec[2][1]);
	R2.vec[2][1]=-R2.vec[1][2];
	R2.vec[2][2]= R2.vec[1][1];

  tmp=crossProduct(crossProduct(crossProduct(crossProduct(R2,R1),tmp),R1.transform()), R2.transform());
	return crossProduct(R1.transform(), R2.transform());
}

 matrix matrix::QRD() const
 {
       matrix tmp((*this).hessenberg());

       for(unsigned i=0; i<50; i++)
       {
       	    //cout<<fabs(tmp.vec[2][1])<<endl;
            tmp=tmp.givensrotate();
            if(fabs(tmp.vec[2][1])<0.00001)
                return tmp;
       }
       return tmp;
 }


matrix matrix::eigenvalue() const  //now, it's only avaliable for 3*3 matrix.
{
    matrix output(3,3);
    matrix tmp=(*this).QRD();
    //cout<<"eigenvalue:"<<tmp<<endl;
    output.vec[0][0]=tmp.vec[0][0];
    output.vec[1][1]=tmp.vec[1][1];
    output.vec[2][2]=tmp.vec[2][2];
    return output;

}

matrix matrix::eigenvector() const
{
	 matrix eigv=(*this).eigenvalue();
   matrix output(3,3);
   matrix tmp(3,3);
   matrix id=identity(3);
   double y,z;
   for(unsigned i=0; i<3; i++)
   {
      tmp=(*this)-id*eigv.vec[i][i];
      if(tmp.vec[0][1]==0 && tmp.vec[1][1]!=0)  
      {
        if(tmp.vec[0][2]==0)
        {
          z=-(tmp.vec[1][0]/tmp.vec[1][1]-tmp.vec[2][0]/tmp.vec[2][1])/(tmp.vec[1][2]/tmp.vec[1][1]-tmp.vec[2][2]/tmp.vec[2][1]);
          y=-tmp.vec[2][0]/tmp.vec[2][1]-tmp.vec[2][2]/tmp.vec[2][1]*z;
        }
          else
          {
            z=-tmp.vec[0][0]/tmp.vec[0][2];
            y=(tmp.vec[1][2]/tmp.vec[0][2]*tmp.vec[0][0]-tmp.vec[1][0])/tmp.vec[1][1];
          }
      }
      else if(tmp.vec[0][1]!=0 && tmp.vec[1][1]==0)
      {
        if(tmp.vec[1][2]==0)
        {
          
          z=-(tmp.vec[0][0]/tmp.vec[0][1]-tmp.vec[2][0]/tmp.vec[2][1])/(tmp.vec[0][2]/tmp.vec[0][1]-tmp.vec[2][2]/tmp.vec[2][1]);
          y=-tmp.vec[1][0]/tmp.vec[1][1]-tmp.vec[1][2]/tmp.vec[1][1]*z;

        }
          else
          {
            z=-tmp.vec[1][0]/tmp.vec[1][2];
            y=(tmp.vec[0][2]/tmp.vec[1][2]*tmp.vec[1][0]-tmp.vec[0][0])/tmp.vec[0][1];
          }
      }
      else
      {
        z=-(tmp.vec[0][0]/tmp.vec[0][1]-tmp.vec[1][0]/tmp.vec[1][1])/(tmp.vec[0][2]/tmp.vec[0][1]-tmp.vec[1][2]/tmp.vec[1][1]);
        y=-tmp.vec[1][0]/tmp.vec[1][1]-tmp.vec[1][2]/tmp.vec[1][1]*z;

      }

      output.vec[0][i]=1/sqrt(1+y*y+z*z);
      output.vec[1][i]=y/sqrt(1+y*y+z*z);
      output.vec[2][i]=z/sqrt(1+y*y+z*z);
   }

   return output;
}


matrix matrix::ones(const unsigned row, const unsigned column)
{
	matrix unit(row, column);
	for(unsigned i=0; i<row; i++)
	{
		for(unsigned j=0; j<column; j++)
		{
				unit.vec[i][j]=1;
		}
    }
    return unit;
}


matrix matrix::identity(const unsigned size)
{
	matrix unit(size, size);
	for(unsigned i=0; i<size; i++)
	{
		for(unsigned j=0; j<size; j++)
		{
			if(i==j)
				unit.vec[i][j]=1;
		}
    }
    return unit;
}


matrix matrix::appendright(const matrix& right) const                 //append a new matrix on the right side.
{


 	if((*this).height()!=right.height())
 	{
 		cerr<<"append right, the height of matrix is not matching, please check it!!!"<<endl;
 		exit(1);
 	}
    matrix output(right.height(), (*this).width()+right.width());

    for(unsigned i=0; i< output.height(); i++)
    {
        for(unsigned j=0; j< output.width(); j++)
        {
         	if(j<(*this).width())
         		output.vec[i][j]=(*this).vec[i][j];
         	else
         	{
         	    output.vec[i][j]=right.vec[i][j-(*this).width()];
         	}
        }
    }        		
    return output;
}

// matrix appendbelow(const matrix below) const;                 //append a new matrix on the below side.
 //{

 //}



//sum of the whole matrix.
 double matrix::sum() const
 {
 	double tmp=0;
 	for(unsigned i=0; i<height(); i++)
 		for(unsigned j=0; j<width(); j++)
 			tmp+=getvalue(i,j);

 	return tmp;	
 }


double matrix::getvalue(const unsigned row, const unsigned column) const
{
	return (*this).vec[row][column];
}

//void matrix::setvalue(double value, unsigned row, unsigned column)
//{
//	vec[row][column]=value;
//}

void matrix::setvalue(const unsigned row, const unsigned column, const double value)
{
	(*this).vec[row][column]=value;   //this指针加或者不加，没什么关系，编译器在编译时，会自动将其加入到函数中，指向调用该成员函数的类对象
}

const unsigned matrix::height() const
{
	return vec.size();
}

const unsigned matrix::width() const
{
	return vec[0].size();
}