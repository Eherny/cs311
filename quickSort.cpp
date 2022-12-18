/**********************************
Templated created by Kazumi Slott
CS311

Your name:Eric Hernandez
Your programmer number: 18
Hours spent: 2
Any difficulties?:Understanding the algorhythm taking the mid point and not just assume pivot is the end value
***********************************/
#include <iostream>
using namespace std;
#include "swap.h" //include your swap.h for mySwap().  If you didn't make it for our first homework or it didn't work, you could implement it down below within this program.

void printAr(const int ar[], int s)
{
  for(int i = 0; i < s; i++) //prints out the array in order 
    cout << ar[i] << " ";
  cout << endl;
}


//Implement mySwap() here if you didn't make mySwap() in swap.h for our first homework.
//It is good to have the swap function so partition() won't get crowded. 
/*/void mySwap(int a,int b)
//{
  int temp;
  temp=a;   //swaps all the indicated values with each other
  a=b;
  b=temp;
}
*/

int partition(int ar[],int start,int end )
{
  //I have 3 variables: pivot, i and swap_index. You may have any local variables.
  int mid=((end+start)/2); //finds the mid point
  int i; //intializes i
  int swap_index=start; //indicates swap index to start
  int pivot=end; //sets pivot point to the end
  mySwap(ar[pivot],ar[mid]); //swaps the mid point and mid
  //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).
  for(i=start;i<pivot;i++) //tranverses array until the pivot point
    {
      //For implementation of this function, refer to my lecture notes "quick sort". 
      //If you used a different algorithm, I would assume you cheated and give you zero points.
      if(ar[i]<=ar[pivot]) //compares the values
	{
	  mySwap(ar[swap_index],ar[i]); //swaps the index and i
	  swap_index++; //incriments index
	}

  }
  mySwap(ar[swap_index],ar[pivot]); //swaps it back with pivot point
  
  //This function returns the index where the pivot value went in.
  return swap_index;  //returns the swap index
}

void quickSort(int ar[], int start, int end)
{
  
  if(start<end) //If the partition has only one element or none, return. 
                   //In other words, if the partition has at least 2 elements, go inside the if.
                   //use start and end to figure out how many elements you have in the partition.
    {
      int n=partition(ar,start,end);   //call partition.
      quickSort(ar,start,n-1);//quickSort on the left partition
      quickSort(ar,n+1,end); //quickSort on the right partition
    }
  
}

int main()
{
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
