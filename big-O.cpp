#include "big-O.h"
#include <iostream>
using namespace std;



int main()
{


  int sum;
  int ar[8]={5,-4,-3,2,4,0,3,-1};
  sum=algoA(ar,8);
  cout<<sum<<endl;;
  sum=algoB(ar,8);
  cout<<sum<<endl;
  cout<<endl;
  sum=algoC(ar,8);
   cout<<sum<<endl;
   
   




}
