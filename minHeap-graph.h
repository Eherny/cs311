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
  void min_heapify(int* curDist,int* locator,int i);
  //  void build_min_heap();
  void bubbleUp(int* curDist,int* locator,int i);    //add curdist and locator to all
  void insert(int* curDist,int* locator,const T& el);
  int find(const T& key) const;
  void remove(int* curDist,int* locator,int i);
  T getMin(int* curDist,int* locator);
  void fixHeap(int* curDist,int* locator,int i);
  int getNum()const;
  class Overflow{};
  class BadIndex{};
  class NotFound{};
};
template <class T>
void minHeap<T>::min_heapify(int* curDist,int* locator,int i)
{
  
  int l = (2*i)+1; //the index of the left child of i
  int r = (2*i)+2; //the index of the right child of i
  int smallest = i; //the index of the smallest value amoung the values at i, l a

  //look for the smallest among 3 elements at i, l and r. largest gets
  //Make sure l and r don't go over the heap's range.
  //I have 4 lines of code here. You can have more or less
  if(l<num && curDist[ar[l]]<curDist[ar[smallest]]) //make sure l is in range and checks if smallest
    {
      smallest=l;
    }
  if(r<num && curDist[ar[r]]<curDist[ar[smallest]]) //makes sure r is in range and the smallest 
    {
      smallest=r;
    }
  
  if(smallest !=i) //if smakkest is not parent
    {
      locator[ar[i]]=smallest;  //swap locaters
      locator[ar[smallest]]=i;
      mySwap(ar[i],ar[smallest]); //swaps values
      min_heapify(curDist,locator,smallest); //runs heapify to fix error
	       
    }
}

template <class T>
  void minHeap<T>::bubbleUp(int* curDist,int* locator,int i)
{
  int parent=(i-1)/2; //finds the parent
  int baby=i; //assumes child is i
  while(baby > 0&&curDist[ar[baby]]< curDist[ar[parent]] ) //while baby is < parent
    {
      locator[ar[baby]]=parent; //swap locaters
      locator[ar[parent]]=baby;
      mySwap(ar[parent],ar[baby]); //exchanges values
      baby=parent; //baby equals the new parent
      parent=(parent-1)/2; //finds new baby
    }
  
}


template <class T>
  void minHeap<T>::insert(int* curDist,int* locator,const T& el)
{
  if(num >= capacity)
    throw Overflow(); //"The array is full";
  ar[num++]=el; //put the elemnt in and incriment
  bubbleUp(curDist,locator,num-1);  //call bubble up from last element
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
void minHeap<T>::remove(int* curDist,int* locator,int i)
{
  
  
  if(i>num-1 || i<0) //if not inbounds
    throw BadIndex(); //call bad index
  
  locator[ar[i]]=num-1; //exchanges the element and the second to last element
  locator[ar[num-1]]=i;
  mySwap(ar[i],ar[num-1]);
  num--; //decrements to remove it
  
  fixHeap(curDist,locator,i); //call fixheap to rfix the heap
  
}
 
template <class T>
  T minHeap<T>::getMin(int* curDist,int* locator)
{
  //This function removes the top element and returns it.
  //You should be calling remove()
  if(num>0)
    {
      T top= ar[0]; //get the top  
      remove(curDist,locator,0); //remove it
      return top; //return it
    }
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
template <class T>
int minHeap<T>::getNum() const
{
  return num; //get the num 
}
template<class T>
void minHeap<T>::fixHeap(int* curDist, int* locator, int i)
{

  //We need to maintain the min heap based on curDist. When 2 vertices swap within the heap, their locations will change, hence you need to update the locator array. Make sure you understand how \
  //  each array works by reading the homework document (there are pictures to explain).
  if(i<num&&&i>=0) //while the fixheap i is less than the amount of elements and also greater than 0
    {
      if(curDist[ar[i]]<curDist[ar[(i-1)/2]]) //if its less than parent call bubble up
	bubbleUp(curDist,locator,i);
      else if(curDist[ar[i]] > curDist[ar[2*i+1]] || curDist[ar[i]] > curDist[ar[2*i+2]]) //else the other conditions
	min_heapify(curDist,locator,i); //call min heapify
    }
  //From i, either bubble up or down.
  //For up, call bubbleUp(). For down, call min_heapify().
  
  //Reminder: A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.
  
  //Since I have the same code inside minHeap::remove(), I am now calling fixHeap() from remove() so I won't have duplicate code.
    }

#endif
