/*****************************************
Template written by Kazumi Slott
CS311

Your name: Eric Hernandez
Your programmer number: 18
Hours spent: 3
Any difficulties?: understanding the algo's
*******************************************/
#include <iostream>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include "/cs/slott/cs211/checkInput.h"
using namespace std;
void heapSort(int ar[],int n);
void runSort( int ar[])
{
clock_t start,end;
 ifstream fin;
 cout<<"How many numbers do you want to put into the array? ";
 int s=getData(1,1000000,"Please Enter a number between 1 and 1000000: ");
 fin.open("/cs/slott/cs311/sort.in");
 if(!fin)
   {
     cout<< "The input file doesnt open" <<endl;
     exit(1);
   }
 for(int i=0;i<s;i++)
     fin>>ar[i];
 fin.close();
 start=clock();
 heapSort(ar,s);
 end=clock();
  cout<< "Elaped time: " << (end-start) / double(CLOCKS_PER_SEC) * 1000 << " milliseconds" << endl;
}

//print an integer array of size n
void print(int ar[], int n)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
  cout << endl;
}

//called from max_heapify and heapSort
void exchange(int& i,int& j) // is basically swap function
{
  //I have 3 lines of code here.
  int temp=i;  //swaps values
  i=j;
  j=temp;

}


//turns a heap rooted at i into a max-heap, assuming the left and right subtrees are already max-heaps.
//n is the number of elements in the heap
void max_heapify(int ar[], int n, int i)
{
  
  int l = (2*i)+1; //the index of the left child of i
  int r = (2*i)+2; //the index of the right child of i
  int largest = i; //the index of the largest value amoung the values at i, l and r

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  //I have 4 lines of code here. You can have more or less
  if(l<n && ar[l]>ar[largest]) //make sure l is in range and checks if largest
    {
      largest=l;
    }
  if(r<n && ar[r]>ar[largest]) // checks if right is out of bounds and if its the largest
      {
	largest=r;
      }
  //The largest is either the right or left child. We need to exchange the parent with it.
  if(largest !=i) //if largest is not parent
    {
      exchange(ar[i],ar[largest]); //swaps values
      max_heapify(ar,n,largest); //runs heapify to fix error
      //exchange the 2 values
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
    }
  
}

//turns the entire array/tree into a max heap rooted at 0
//n is the number of elements we have in the array
void build_max_heap(int ar[], int n)
{
  //2 lines of code in this function
  
  for(int i=n/2; i>=0; i--) //if there are atleast a parents
    { 
      max_heapify(ar,n,i); //(turn the smallest subtrees into max-heaps and work your way up) 
    }
  
}

//a is an unordered list to start with
//use max_heapi,fy to sort a
//n is the number of elements in the array
void heapSort(int a[], int n)
{
  //I have 6 lines of code in this function. You can have more or less.
  
  build_max_heap(a,n);  //build max heap from an unordered list
  //call build_max_heap
  
  int size = n; //size of the unsorted portion of the array
  
  while(size>0) //repeat until heap is empty
    {  
      exchange(a[size-1],a[0]);    //swap max element with last element - max element is now the last element
      size--;
      //discard the last element from the heap
      max_heapify(a,size,0);
      //root may violate max-heap property, but children are max heaps. run max_heapify to fix it.

    }
}

//this function corrects a violiation at i by bubbling it up to the correct place                             
//a is a heap                                                                                                
void bubbleUp(int a[], int i)
{
  int parent=(i-1)/2; //finds the parent
  int baby=i; //assumes child is i
  while(a[baby] >a[parent] &&  baby>0) //if baby is more than parent and baby is atleast greeater than 0
      {
	exchange(a[parent],a[baby]); //exchanges values
	baby=parent; //baby equals the new parent
	parent=(parent-1)/2; //finds new baby
      }
  //Write this function after you made insert() and while you are making remove().
}

//a is a max heap                                                                                            
//cap is the capacity of the heap                                                                            
//n is the number of elements the heap currently has before insertion                                        
//el is the new element to be inserted                                                                       
void insert(int a[], int cap, int& n, int el)
{
  //refer to lecture notes
  //throw "The array is full" if the array is full.
  if (n==cap) //if the array is full
    throw "The array is full";
  a[n++]=el; //set element to n and incriment
  bubbleUp(a,n-1); //bubble app the second to last number
  
  //write this function without calling bubbleUp() first. When you work on remove(), you will notice you will
  //have to have the same code there. Move the code into bubbleUp() and call it to avoid redundancy.
}

//This function returns the index where key was found or throws an exception if key is not found.                                   
//a is a max heap.                                                                                 
//n is the number of elements in the heap.                                                                                
//key is the element we are looking for.                                                                                             
int find(const int a[], int n, int key)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)                                                                                            
    if(a[i] == key)
      return i;

  throw "The element doesn't exist";
}

//a is a max heap                                                                                            
//n is the number of elements the heap currently has before deletion, then decrememted after deletion                                         
//i is the index of the element to be removed.                                             
void remove(int a[], int& n, int i)
{
  //refer to lecture notes
  //throw "The index to be removed is invalid" if i is an invalid index.
  //Call bubbleUp or max_heapify (the lecture notes show 2 possibilities).
  //FYI, I have a total of 8 lines of code in this function. You can have more or less.
  if(i>n-1 || i<0) //checks if it is out of bounds index
    throw "The index to be removed is invalid";
  
  exchange(a[i],a[n-1]); //exchanges the element and the second to last element
  n--; //decrements to remove it
  if(a[i]>a[(i-1)/2] && i>0) //checks the condition if it is not parent is greater than child and if greater thanb 0
    {
      bubbleUp(a,i); //calls bubbleUp
    }
  else max_heapify(a,n,i); //if not calls heapify
  
}

int main()
{
  int ar[10] = {11, 3, 4, 5, 7, 19, 20, 2, 8, 1};
  int ar2[10] = {5, 3, 10, 4, 7, 9, 11, 2, 8, 1};
  int ar3[2] = {2,1};
  int n;
  int max=1000000;
  int ar4[max];
  cout << "testing max_heap rooted at index 3" << endl;
  max_heapify(ar, 10, 3); //max-heapify rooted at index 3
  print(ar, 10);//11 3 4 8 7 19 20 2 5 1  --> the tree rooted at 3 is now a max-heap (8 is at root. 2 and 5 are its children)

  cout << endl << "testing max_heap rooted at index 1" << endl;
  max_heapify(ar, 10, 1); //max-heapify rooted at index 1
  print(ar, 10);//11 8 4 5 7 19 20 2 3 1  --> the tree rooted at 1 is now a max-heap (8 is at root. 5 and 7 are its children. 5's children are 2 and 3)

  cout << endl << "testing build_max_heap" << endl;
  build_max_heap(ar, 10);
  print(ar, 10);//20 8 19 5 7 11 4 2 3 1

  cout << endl << "testing heapSort" << endl;
  
  heapSort(ar2, 10);
  
  print(ar2, 10);//1 2 3 4 5 7 8 9 10 11

  cout << endl << "testing heapSort" << endl;
  
  heapSort(ar3, 2);
  
  
  print(ar3, 2);//1 2

  runSort(ar4);

  try
    {
      cout << "\ntesting insert" << endl;
      int ar4[15] = {20, 8, 19, 9, 5, 11, 4, 2, 3, 1, -1, -1, -1, -1, -1}; //max heap with 10 elements already
      n = 10; //n is the number of elements in the heap
      insert(ar4, 15, n, 15); //trying to insert 15
      print(ar4, n); //20 15 19 9 8 11 4 2 3 1 5

      n = 2;
      cout << "\ntesting exception from insert() - The array is full" << endl;
      insert(ar3, 2, n, 100); //throws "The array is full"
    }
  catch(const char* msg)
    {
      cout << msg << endl;
    }

  try
    {
      cout << "\ntesting remove - bubble down" << endl;
      int ar5[15] = {16, 14, 12, 8, 7, 10, 2, 3, 4, 1, -1, -1, -1, -1, -1}; //max heap with 10 elements already
      n = 10; //n is the number of elements in the heap
      remove(ar5, n, find(ar5, n, 14)); //trying to remove 14
      print(ar5, n); //16 8 12 4 7 10 2 3 1

      cout << "\ntesting remove - bubble up" << endl;
      int ar6[15] = {100, 15, 80, 13, 14, 60, 20, 12, 5, 10, 9, 50, -1, -1, -1}; //max heap with 12 elements already
      n = 12; //n is the number of elements in the heap
      remove(ar6, n, find(ar6, n, 12)); //trying to remove 12
      print(ar6, n); //100 50 80 15 14 60 20 13 5 10 9

      cout << "\ntesting exception from find() - The element doesn't exist" << endl;
      remove(ar6, n, find(ar6, n, 999)); //throws an exception
    }
  catch(const char* msg)
    {
      cout << msg << endl;
    }

  try
    {
      int ar7[3] = {7, 8, 9};
      n = 3;
      cout << "\ntesting exception from remove() - The index to be removed is invalid" << endl;
      remove(ar7, n, n); //throws exception. The index, n, is invalid when there are n elements in the heap (the index goes [0..n-1]).
    }
  catch(const char* msg)
    {
      cout << msg << endl;
    }

  return 0;

}

