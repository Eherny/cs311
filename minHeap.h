/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: Eric Hernandez
Your programmer number: 18
Hours spent making and testing your min heap class: 4
Any difficulties?: nothing cause you jsut flip signs
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;
#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c){ capacity = c;ar=new T[capacity]; num = 0;}
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int i);
  //  void build_min_heap();
  void bubbleUp(int i);
  void insert(const T& el);
  int find(const T& key) const;
  void remove(int i);
  T getMin();

  class Overflow{};
  class BadIndex{};
  class NotFound{};
};
template <class T>
void minHeap<T>::min_heapify(int i)
{
  
  int l = (2*i)+1; //the index of the left child of i
  int r = (2*i)+2; //the index of the right child of i
  int smallest = i; //the index of the smallest value amoung the values at i, l a

  //look for the smallest among 3 elements at i, l and r. largest gets
  //Make sure l and r don't go over the heap's range.
  //I have 4 lines of code here. You can have more or less
  if(l<num && ar[l]<ar[smallest]) //make sure l is in range and checks if smallest
    {
      smallest=l;
    }
  if(r<num && ar[r]<ar[smallest]) //makes sure r is in range and the smallest 
    {
      smallest=r;
    }
  
  if(smallest !=i) //if smakkest is not parent
    {
      mySwap(ar[i],ar[smallest]); //swaps values
      min_heapify(smallest); //runs heapify to fix error
      
    }
}

template <class T>
void minHeap<T>::bubbleUp(int i)
{
  int parent=(i-1)/2; //finds the parent
  int baby=i; //assumes child is i
  while(baby > 0&&ar[baby]< ar[parent] ) //while baby is < parent
    {
      mySwap(ar[parent],ar[baby]); //exchanges values
      baby=parent; //baby equals the new parent
      parent=(parent-1)/2; //finds new baby
    }
  
}


template <class T>
void minHeap<T>::insert(const T& el)
{
  if(num >= capacity)
    throw Overflow(); //"The array is full";
  ar[num++]=el; //put the elemnt in and incriment
  bubbleUp(num-1);  //call bubble up from last element
}

template <class T>
int minHeap<T>::find(const T& key) const
{
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return i;
  
  //The element doesn't exist 
  throw NotFound();// "The element doesn't exist";                                                                                             
}

template<class T>
void minHeap<T>::remove(int i)
{
  
  
  if(i>num-1 || i<0) //if not inbounds
    throw BadIndex(); //call bad index
  
  mySwap(ar[i],ar[num-1]); //exchanges the element and the second to last element
  num--; //decrements to remove it
  if(ar[i]<ar[(i-1)/2] && i>0)
    
    {
      bubbleUp(i); //calls bubbleUp
    }
  else min_heapify(i); //if not calls heapify 
  
}
 
template <class T>
T minHeap<T>::getMin()
{
  //This function removes the top element and returns it.
  //You should be calling remove()
  T top= ar[0]; //get the top  
  remove(0); //remove it
  return top; //return it
}
template<class T>
ostream& operator<<(ostream& o,const minHeap<T>& h)
{
  if(h.num==0) //if queue is empty
    o<< "none"; //say none
  for(int i=0;i<h.num;i++) //if not show the whole queue
    o<<h.ar[i]<<" ";
  cout<< endl;
  return o;
}

#endif
