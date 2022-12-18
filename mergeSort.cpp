/**********************************
Templated created by Kazumi Slott
CS311

Your name:Eric Hernandez
Your programmer number: 18
Hours spent: 2
Any difficulties?: copying the array correctly
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

void merge(int ar[],int first,int last)
{
  //For implementation of this function, refer to my lecture notes "merge sort"
  //If you are using a different technique, I assume you cheated and will give you zero points.
  int* temp=new int[(last-first)+1]; //establish an dynamic array with correct size
  int mid=(first+last)/2; //establish a mid value
  int right=mid+1; //right side is always mid +1
  int left=first; //establish left as the first
  int start=0; //counter that starts at 0
  while(left<=mid&&right<=last) //while not overlapping values
    {
      if(ar[left]<=ar[right]) //compares the values 
	temp[start++]=ar[left++]; //copies values into temp array
      else
	temp[start++]=ar[right++]; //copies right values into array
    }
  while(left<=mid) //while left is less than mid
    {
      temp[start++]=ar[left++]; //copies left values to temp array
    }
  while(right<=last) //while right is less than last
    {
      temp[start++]=ar[right++]; //puts right values into the array
    }
  start--;   //has to decrement or else start is out of bounds
  while(start>=0) //while start is not finished
    {
      ar[start+first]=temp[start]; //copies sorted array to the ouputting array
      start--; //decrements start
    }
  delete[] temp; //deletes the temp array
  //Don't forget to destroy temp array, which is created dynamically
}

void mergeSort(int ar[], int first, int last)
{
  //For implementation of this function, refer to my lecture notes "merge sort"
  int mid=(first+last)/2;//estiblish the middle value
  if(first<last){ //as long as there are two numbers in the array

    mergeSort(ar,first,mid); //call mergeSort for first to mid
    mergeSort(ar,mid+1,last); //call mid +1 to last for mergSort
    merge(ar,first,last); //merge the first and last arrays
  }
}

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
