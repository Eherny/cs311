/**********************************
Template prepared by Kazumi Slott
CS311

matrix class

Replace the ?????s

For examples of matrix multiplication
https://matrix.reshish.com/multCalculation.php 

Your name:Eric Hernandez
Your programmer number:18
Hours spent?:7
Any difficulties?:EVERYTHING i cried a little bit
***********************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

//This forward declaration of Matrix class is necessary because the following operator>> and << are using Matrix as a parameter
template <class T>
class Matrix;

//This forward declaration of operator>> is necessary Since operator<< is a template function.
template<class T>
ifstream& operator>>(ifstream& fin, Matrix<T>& m);

//This forward declaration of operator<< is necessary Since operator<< is a template function.
template <class T>
ostream& operator<<(ostream& o, const Matrix<T> & m);

//Template class so we can have a matrix of any data types, int or double
template <class T>
class Matrix
{
  //friend functions so they can access the private members 
  friend ostream& operator<< <T>(ostream& o, const Matrix<T> & m);
  friend ifstream& operator>> <T>(ifstream& fin, Matrix<T>& m);

private: 
  T** m; //2 dimensional dynamic array
  const int R; //number of rows
  const int C; //number of columns

public: 
  Matrix(int R, int C);
  Matrix();
  ~Matrix();
  Matrix operator*(const Matrix& other);// matrix multiplication
  class size_error{};//exception class 
};

//default constructor
template<class T>
Matrix<T>::Matrix() : R(0), C(0) //setting const R and C to initial value, 0.
{
  m = NULL;
}

//constructor to create a matrix, row x col 
template<class T>
Matrix<T>::Matrix(int row, int col) : R(row), C(col) //setting const R and C 
{
  if(row <= 0 || col <= 0)
    {
      m = NULL;
      return;
    }

  //m = new T[R][C]; //this doesn't compile
  m = new T*[R]; //create a single dimensional array of pointers of the T type
  for (int i=0; i<R; i++) //create a single dimensional array for each slot of m
    m[i] = new T[C];

  //initialize each element to 0
  for(int rw = 0; rw < R; rw++)
    for(int cl = 0; cl < C; cl++)
	m[rw][cl] = 0;
}

//fill a matrix using an input file
template<class T>
ifstream& operator>>(ifstream& fin, Matrix<T>& mrx)
{
  //for the row of file matrix  
  for(int i=0;i<mrx.R;i++)
    //for the columns of the left hand side
    for(int j=0;j<mrx.C;j++)
      fin >> mrx.m[i][j];  //take them in as a matrix array
  return fin; //return the file matrix
  
}

/*output the matrix to screen in the following format. Allocate 10 spaces for each value.
         1          1          1
         2          2          2
         3          3          3
         4          4          4 
*/
template<class T>
ostream& operator<<(ostream& o, const Matrix<T>& mrx)
{
  //for the row of the matrix
  for (int i=0; i < mrx.R; ++i){ 
    for (int j=0; j < mrx.C; ++j){//for the columns of the matrix 
      o <<setw(10)<<mrx.m[i][j] ; //output the matrix given setw10
    }    
    o << '\n'; //line break to start new row
  }
  return o;
  
}

//matrix multiplication
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
  Matrix<T> prod(this->R,other.C); //make a matrix for a product using other and the pointer
  T sum;
  if((this->C!=other.R))//exception class
    throw size_error();  //throw the error if it hits
    
  for(int i=0; i<this->R;++i) //through all the rows of left
    {
      for(int j=0; j<other.C;++j) //through all the columns of the right
	{
	  sum=0; //reset sum every time  
	  for(int k= 0;k<other.R;++k)
	    {
	      
	      sum+= this->m[i][k]* other.m[k][j]; //multiplying the column and rows in order to get one of the matrix sums
	      
	    }
	  prod.m[i][j]=sum; //apply the sum to the product matrix
	  
	}
      
    }
  return prod;//returning the product

}

//destructor                                                                                                                                                                                        
template<class T>
Matrix<T>::~Matrix()
{

    //if m is not null
  if(m!=NULL)
    {
      for(int r=0;r<R;r++) //go through all the loops of the matrix
	{ 
	  delete[] m[r]; //delete the rows inside the matrix
	  
	}
      delete[] m; //delete the pointer to the matrix
      
    }

  //destroy what is created in heap memory                                                                                                                          
  //if m is not NULL do the following                                  
     //HINT: delete each dynamic array pointed to by each slot of m                                                                                                                                   
     //delete m (m contains all rows)                                                                                                                                                                   
}
