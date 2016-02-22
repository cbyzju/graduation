#ifndef __MATRIX_H__
#define __MATRIX_H__

#include<vector>
#include<iostream>
using namespace std;

class matrix
{
private:
	vector< vector<double> > vec;
     
    matrix hessenberg() const;
    matrix givensrotate() const;
    static matrix eigenvector_iteration(matrix& tmp);

public:
	matrix();
	matrix(vector< vector<double> > vecInstance): vec(vecInstance){};
	matrix(const matrix &ref);
	matrix(unsigned height, unsigned width);
	~matrix();


	//static matrix add(const matrix& A, const matrix& B);  //static在声明阶段需要，在实现阶段是不需要加的，不然会报错
	double getvalue(const unsigned row, const unsigned column) const; 
	void setvalue(const unsigned row, const unsigned column, const double value);
	//const属性浅析：尾部的const，表示this指针指向的对象，不能被修改，也就是说double b=a.getvalue()的时候，a是不能被修改的。
	//               头部的const，表示返回值不能被修改，也就是上面的返回值是不能被修改的
	//               形参列表的const，表示调用函数的时候，传入的实参值不能被修改
	//void setvalue(double value, unsigned row, unsigned column);	
	//原则：能加const限定，就最好加上，因为(1).非const量能够传入const限定的函数，但是const量是不能不能传入非const限定的函数的。
	//                                    （2）以防不能被修改的量，在程序执行的过程中，被无意间修改掉。
	//内联函数，小巧但需要经常性调用的函数，设置成内联函数，更好些
    const unsigned height() const;
	const unsigned width() const ;
   

	//operator overload + - * /.
    matrix& operator=(const matrix& input);
    matrix operator+(const matrix& input) const;
    matrix& operator+=(const matrix& input);
    matrix operator-(const matrix& input) const;
    matrix& operator-=(const matrix& input);
    matrix operator*(const matrix& input) const; //inner product A.*B between matrix.
    matrix operator*(const double input) const;  //mutiplied by scalar
    matrix& operator*=(const matrix& input);
    matrix operator/(const matrix& input) const; //inner division A./B between matrix.
    matrix operator/(const double input) const;  //divided by scalar
    matrix& operator/=(const matrix& input);


    friend ostream& operator<<(ostream &os, const matrix& input);  //output stream overload.


    //most useful operations of matrix.
    double sum() const;
    matrix transform() const;
    static matrix crossProduct(const matrix& A, const matrix& B);  // calculate the cross product A*B between two matrix.
    static matrix crossDivision(const matrix& A, const matrix& B); //calculate the cross product A\B between two matrix.
    matrix rowVector(const unsigned i) const;                      // fetch the whole row i.
    matrix columnVector(const unsigned j) const;                   // fetch the whole column j.

    matrix appendright(const matrix& right) const;                 //append a new matrix on the right side.
    matrix appendbelow(const matrix& below) const;                 //append a new matrix on the below side.

    static matrix ones(const unsigned row, const unsigned column);
    static matrix identity(const unsigned size);                  // construct identity matrix.
    void LUD(matrix& lower, matrix& upper) const;                 //LU decompostion for square matrix.
    double det() const;                                           // determination of a given squre matrix.
    matrix inverse() const;                                       // inverse of a given full squre matrix.
    matrix QRD() const;                                           //now, it's only avaliable for 3*3 matrix.
    matrix eigenvalue() const;                                    //now, it's only avaliable for 3*3 matrix.
    matrix eigenvector() const;                                   //now, it's only avaliable for 3*3 matrix.

};
#endif