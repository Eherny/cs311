/************************************
Template created by Kazumi Slott
CS311
Homework on radix sort

Description of this program: Radix sort program, that sorts a linked list of words from right to left to get it in the correct order
Your name: Eric Hernandez
Your programmer number: 18
Hours spent: 4
Any difficulties?: realizing what the radixsort function looks like visually
************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "/cs/slott/cs211/checkInput.h"
using namespace std;
clock_t start,end;

const int LEN = 3; //the length of words
const int ALPHABET = 26; //total number of letters

class Node
{
  friend class LL;
private:
  string el;
  Node* next;
public:
  Node(const string& s){el = s; next = NULL;}
  string getElem() const {return el;}
};

class LL
{
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL(){front = rear = NULL; num = 0;}
  ~LL();
  bool empty()const{return (front == NULL && rear == NULL && num == 0);}
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  void clear(){front = rear = NULL; num = 0;}
  Node* begin() const{return front;}
  Node* goToNext(Node* curr) const{return curr->next;}
  int size() const{return num;}
};

LL::~LL()
{
  //  cout << "destructor is called" << endl;
  Node* p = front;
  while(!empty())
    {
      front = front->next;
      delete p;
      p = front;
      if(front == NULL)
	rear = NULL;
      num--;
    }
}

//add a new node at the end of this list. The element of the new node is s.
void LL::addRear(const string& s)
{
  //This function is just like what you made in LL class from CS211.
  Node* p = new Node(s); //the new node has NULL in the next field.

  if(empty())
    front = rear = p;
  else
    {
      rear->next = p;
      rear = rear->next;
    }    
  num++;
}

//Implementing this function
//add the node pointed to by p (p points to one of the nodes in all list) at the end of this list
void LL::addRear(Node* p)
{
  //Don't make a new node.

  //You need a special case when the list is empty
  if(empty())
    {
      front=rear=p;
    }
  else
    {
      //Don't forget to place NULL in the next field of the rear node of this list.
      rear->next=p;
      rear=rear->next;  

      //don't forget to increment num
    }
  rear->next=NULL;     
 
  num++;
  //Note: this function should have complexity O(1). There is no loop required. 
}

//Implement this function
//appending another linked list at the end of this linked list 
void LL::append(const LL& other)
{
  //Don't forget to update num of this list
  if(empty()) //specioal case if the first array is empty
    {
      front=other.front; //sets the front of the array to the front of the other linked list
      rear=other.rear; //sets it to the end of the linked list
    }
else
  {
    rear->next=other.front; //sets the rear of the list to the front of the other 
    rear=other.rear;//sets the rear of the array to the end of the other one combing it
  } 
  num+=other.num; //incriments num depending on the num of the other list
  rear->next=NULL; //sets the next number to NULL


  //Note: this function should have complexity O(1). There is no loop required. 
}

void radixSort(LL& all);
void printLL(const LL& l);
void checkBuckets(const LL buckets[], int n);
void combineLists(LL& all, LL buckets[]);
void makeLL(LL& all);

int main()
{
  LL all; //holds all words
  makeLL(all); //all contains strings in the original order
  start=clock();
  radixSort(all);
  end=clock();
  cout<< "Elaped time: " << (end-start) / double(CLOCKS_PER_SEC) * 1000 << " milliseconds" << endl;
  cout << "Final result ----" << endl;
  //  printLL(all); //all contains strings in sorted sorter
  cout << endl;

  return 0;
}

//Implement this function
//using the radix sort algorithm to sort strings that contain lowercase letters. 
void radixSort(LL& all)
{
  //Each slot of the buckets array is a LL object.
  LL  buckets[ALPHABET]; //bucket[0] is for 'a'. There are 26 buckets.   
  Node* front;
  Node* cur;
  int ind;
  //checking each place
  //To go through each string in all list, check printLL() to see how to iterate
  //go to the correct bucket depending on the letter at the current place and add the node from the all list at the end of the bucket

  for(int j=LEN-1;j>=0;j--) //outer for loop goes through the length of each word
    {
      for(cur=all.begin(),front=all.begin();cur!=NULL;cur=front) //goes through the string in each list
      {
	front=all.goToNext(front); //incriments the front as to incriment for loop

	string elm =cur->getElem(); //gets the element string 
	ind= elm[j]- 'a'; //converts it to an int
	buckets[ind].addRear(cur); //adds the word to the correct bucket


      }
    combineLists(all,buckets); //recombines all the lists
    }
}

//Implement this function
//combining all lists from buckets
void combineLists(LL& all, LL buckets[])
{
  all.clear();  //call clear() to reset the all list. All the nodes went to correct buckets already.
  for(int i=0;i<ALPHABET;i++)
    {
      if(!buckets[i].empty()) //only go through if bucket is not empty
	{
	  all.append(buckets[i]);//populate the all list by combining the lists from the buckets by calling append()
	  buckets[i].clear(); //reset each list in b[i] by calling clear(). All the nodes were moved to the all list already.
	}
    }
}

//Make a linked list of words from an input file  
void makeLL(LL& all)
{
  string s;  
  ifstream fin;
  fin.open("/cs/slott/cs311/sortString1mil.in");
  cout<<"How many numbers do you want to put into the array?: ";
  int j=getData(1,1000000,"Please Enter a number between 1 and 1000000: ");
  if(!fin)
    {
      cout << "The input file doesn't exist" << endl;
      exit(1); //quits the program if the input program doesn't exist.
    }
  for(int i=0;i<j;i++)    
    {
      fin>>s;
      all.addRear(s);
    }

  fin.close();
  /*  
      fin >> s;
      while(fin)
      {
      all.addRear(s);
      fin >> s;
      }
  */ 
}

//This function shows the contents of all the buckets
void checkBuckets(const LL buckets[], int n)
{
  for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      printLL(buckets[i]);
      cout << endl;
    }
}

//This function prints all the elements in l
void printLL(const LL& l)
{
  int i;
  Node* p;

  //iterate l from the first node to last node
  for (i = 0, p = l.begin(); i < l.size(); i++, p = l.goToNext(p))
    cout << p->getElem() << ' ';
}

