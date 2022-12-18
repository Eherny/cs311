/******************************************
Template prepared by Kazumi Slott
CS311

Description of this program: ???????????????????

Your name: Eric Hernandez
Your programmer number:18
Number of hours you spent:10 min
Any difficulties?:  realizing the input file is wrong in the function
*******************************************/
//What do you need to include? HINT: What are you using in main()?
//include your matrix.h
#include "matrix.h"
#include <iostream>
#include <fstream>
int main()
{
  
  Matrix<double> m1(4,4);
  Matrix<double> m2(4,3);
  //Your matrices need to be of the same data type.  When you do multiplication, the data types of the 2 matrices need to be the same.

  ifstream fin;
  //  create fin
  fin.open("/cs/slott/cs311/house_info.in");
  fin>>m1;
    //load the data into the first matrix
  fin.close();

  fin.open("/cs/slott/cs311/house_function.in");
  fin>>m2;
  //load the data into the second matrix
  fin.close();

  
    //use try and catch
    //In catch, show the following message.
  try{
    Matrix<double>r=m1*m2;//creates a matrix and  by multiplying m1, and m2
    cout<<r<<endl; //shows the resulting matrix
  }
  catch(Matrix<double>::size_error)//attempts to catch a size error error
      {
      cout << "SIZE ERROR" << endl;
      }
  return 0;
}
