/*************************
Template created by Kazumi Slott
CS311

Expected outputs
[kslott@empress cs311]$ ./a.out
TEST1
L, R, m = 0, 8, 4
L, R, m = 0, 3, 1
L, R, m = 2, 3, 2
2
TEST2
L, R, m = 0, 5, 2
L, R, m = 0, 1, 0
L, R, m = 1, 1, 1
1
TEST3
L, R, m = 0, 8, 4
L, R, m = 0, 3, 1
L, R, m = 2, 3, 2
L, R, m = 2, 1, 1
-1
[kslott@empress cs311]$
**************************/
#include <iostream>
using namespace std;

//a is sorted in ascending order
//key is what you are looking for
//L and R: you are searching for key in a[L..R]
//This function returns index where key was found or -1 if not found.
int binarySearch(const int a[], int key, int L, int R)
{
  int m = (L+R)/2; //middle of [L..R]
  //keep this cout. You need to verify your code by comparing your outputs to the expected outputs listed above.
  cout << "L, R, m = " << L << ", " << R << ", " << m << endl;
  if(L>R)

    return -1;
  else
    if(key==a[m])
      return m;
  else if(key>a[m]) 
    return binarySearch(a,key,m+1,R);
  else if(key<a[m])
    return binarySearch(a,key,L,m-1);


  

  //complete this function by using recursion.
}

//Don't change this main.
//These test cases are from my CS111 lecture notes and lecture recording.  If your outputs are different, check the following lec notes and video.
//CS111 Lecture Notes 6-1: arrays - single dimensional Pages 14-16
//CS111 Recording of lecture on November 13(Fri) - binary search and selection sort
int main()
{
  cout << "TEST1" << endl;
  int ar1[] = {5, 10, 11, 28, 55, 59, 62, 80, 98};
  cout << binarySearch(ar1, 11, 0, 8) << endl;

  cout << "TEST2" << endl;
  int ar2[] = {1, 10, 20, 30, 40, 50};
  cout << binarySearch(ar2, 10, 0, 5) << endl;

  cout << "TEST3" << endl;
  int ar3[] = {5, 9, 11, 28, 55, 59, 62, 80, 98};
  cout << binarySearch(ar3, 10, 0, 8) << endl;

  return 0;
}
