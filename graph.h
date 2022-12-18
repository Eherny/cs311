/****************************
Templated created by Kazumi Slott
CS311

Your name: Eric Hernandez
Your programmer number: 18
Hours spent: 5
Any difficulties?:graph is most complicated program to date
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include "minHeap-graph.h"
using namespace std;

class edge
{
  friend class graph;  //You want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {neighbor=u; wt=w;};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  void DijkstraShortestPath(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object
  num_ver=num; //make num_ver equal to num
  ver_ar = new list<edge*>[num_ver];  //create a dynamic array with edges with num_ver size

}

graph::~graph()
{
  //destroy all the edge objects created in heap                                                                                                        
  //For each vertex in ver_ar
  //    go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.  

  //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
  //https://www.cplusplus.com/reference/list/list/~list/

  //destroy the ver_ar dynamic array
  for(int i =0;i<num_ver;i++) //goes through all vertexes 
    {
      for (list<edge*>::iterator u =ver_ar[i].begin(); u != ver_ar[i].end(); u++) //iterates through the graph
	{
	  delete *u; //deleting the objects
	}
    }
  delete[] ver_ar; //finally deleting the dynamic array
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.
  ver_ar[v].push_back(new edge(u,w)); //adds a new edge with
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.                                
template<class T>
void displayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  //The algorithm is in my lecture notes.
  //I made dynamic array called "num"
  int *num = new int[num_ver]; //create a dynamic array and fill it with 0
  for(int j=0; j<num_ver;j++) 
    {
      num[j]=0;
    }
  int i=1; //initilize i to 1
  int v=start; //initizlize v to start

  //I created a queue object of string data type from the library's queue class to save all the paths.
  queue<string> edges; //create a string queue call edges

  //I used do-while
  //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.
  do
    {

      DFT_helper(v,i,num,edges); //call dft helper 
      v=nextUnvisitedNodes(num,v,v+1); //call the next unvisted node


    }while(v!=-1); //do while not -1

  //You could call displayQueue() implemented above to display all the paths. 
  displayQueue(edges);
  //Don't forget to destroy the dynamic array
  delete[] num;
  cout<<endl;
}

//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.                                                                                            
//num is the array of vertices                                                                                                          
//start is the start vertex                                                                      
//s is the vertext right after the vertex we started last time                                                                          
int graph::nextUnvisitedNodes(int* num, int start, int s)
{
  //go through the num array from s to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  //don't start from index 0!
  for(int i=s%num_ver;i!=start;i=(i+1) % num_ver)//increiment through the queue
    {
      {
	if(num[i]==0)//if num is 0 return i
	  return i;
      }
    }
  return -1; //if not its -1

  //Althought this function may be called multiple times because there may be multiple disconnected graphs, we are checking each vertex only once.
}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  //The algorithm is in my lecture notes
  num[v]=i++; //incriment the num array
  cout<<v<<" "; //cout v


  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/ 
  //iterator class is nested inside list class
  for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++) //iterate through the grph
    {
      //From the example on https://www.cplusplus.com/reference/list/list/end/
      //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
      //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.  
      if(num[(*u)->neighbor]==0) //if the num neighbor is 0
	{
	  q.push(to_string(v) + "->" + to_string((*u)->neighbor)); //push the v and its neighbor to the queue
	  DFT_helper(((*u)->neighbor),i,num,q); //push each path e.g. 0->1 into q. to_string(int) converts int to string. 
      //to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp
	} 
      
      
    }

  /***********************************************************************************************
   **********************************************************************************************
    Compile with a c++11 option if you are using to_string()
        g++ -std=c++11 graphClient.cpp 
   **********************************************************************************************
   ***********************************************************************************************/
}

//start is the index for the start vertex
void graph::BFT(int start)
{
  //The algorithm is in my lecture notes

  //Use the queue class from the library
  queue<int> q; //create an integer q
  queue<string> edges; //create a string queue
  //I used another queue of strings to save all the paths.
  int *num =new int[num_ver];  //create a dynamic array
  for(int j=0; j<num_ver;j++) // add 0 for all num array
    {
      num[j]=0;
    }
  int i=1;//initialize i to 1
  int v=start; //initilize v to start
  do{
    
    num[v]=i++; //incriment v to i++
    q.push(v); //push v into q
    while(!q.empty()) //while q not empty
      {
	v=q.front(); //make v equal to the front
	q.pop(); //pop it out
	cout<<v<<" ";	 //cout v
	for(list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++)//iterate through graph
	  {
	    if(num[(*u)->neighbor]==0) //if the neighbor is unvisited
	      {
		num[(*u)->neighbor]=i++; //make the neighbor incriment
		q.push((*u)->neighbor); //push the neighbor into q
		edges.push(to_string(v) + "->" + to_string((*u)->neighbor)); //push the v and its neighbor into the edge 
	      }
	  }
      }
    v=nextUnvisitedNodes(num,v,v+1); //call nextr unvisted node
  }while(v!=-1); //stop when the values are not -1
  displayQueue(edges); //display the edges queue
  delete[] num; //delete num array
  //I used do-while to visit all unconnected graphs. Call nextUnvisitedNodes() to check to see if there are more unvisited verteces.
  
  //Check the manual to figure out what member functions of the queue class you need to use.
  // https://www.cplusplus.com/reference/queue/queue/
  
  //You could call show all paths by calling displayQueue()                                                                     
  
  //Don't forget to destroy the dynamic array if you used one
}
void showShortestDistance(int* curDist, int* predecessor, int start)
{
  int dest; //destination                                                      
  stack<int> s;//using stack to show
  cout << "Enter the destination: ";                                           
  
  cin >> dest;                      //get in user input for destination                                           
  int res=curDist[dest]; //set result to destination
  cout << "The shortest path from " << start << " to " << dest << " is ";
  while(dest!=start) // while destination isnt the start
    {
      s.push(dest); //push the element to the stack
      dest=predecessor[dest]; //set preveious element as destination
    }
  s.push(start); //push start into the stack
  while(!s.empty()) //while stack not empty
    {
      cout<<s.top()<<" "; //cout the top
      s.pop(); //pop it out
    }
  
  
  //trace the shortest path from dest back to start
  //I suggest you use either library's stack or queue. Which one will work?
  
  
  cout << "\nThe distance is " << res << endl; //cout the result
}
void printHeapArrays(const minHeap<int>& h, int* curDist, int* locator, int* predecessor, int num_ver)
{
  cout << "heap ------" << endl;
  cout << h << endl;  //This works if you made operator<<() to display a heap
  
  cout << "locator ------" << endl;
  for(int i = 0; i < num_ver; i++)                                             
    
    cout << locator[i] << " ";                                                 
  
  cout << endl;
  
  cout << "curDist ------- " << endl;                                          
  
  for(int i = 0; i < num_ver; i++)                                             
    
    cout << curDist[i] << " ";                                                 
  
  cout << endl << endl;
  
  cout << "Predecessor ------- " << endl;                                      
  
  for(int i = 0; i < num_ver; i++)                                             
    
    cout << predecessor[i] << " ";                                             
  
  cout << endl << endl;
}

void graph::DijkstraShortestPath(int start)
{
  minHeap<int> toBeChecked(num_ver); //minheap called to bechecked
  
  int* curDist = new int[num_ver];//establish dyanmic arrays
  int* predecessor = new int[num_ver];
  int* locator = new int[num_ver];
  
  for(int i=0;i<num_ver;i++) //initialize curdist to 999
    curDist[i]=999;
  for(int i=0;i<num_ver;i++)
    {
      toBeChecked.insert(curDist,locator,i); //initilize to be checked to 123456 etc
      locator[i]=i; //set locater array to 1233456 etc
      predecessor[i]=-1; //set all predecessor to -1
    }
  curDist[start]=0; //set curr distance to 0
  int v= start; //set v to start
  while(toBeChecked.getNum()>0) //while the min heap isnt empty
    {
      //      printHeapArrays(toBeChecked,curDist,locator,predecessor,num_ver);
      toBeChecked.fixHeap(curDist,locator,locator[v]); //fix the heap from the spot
      v=toBeChecked.getMin(curDist,locator); //set v to get min
      for(list<edge*>::iterator u=ver_ar[v].begin();u!=ver_ar[v].end();u++) //incriment through the gaph
	{
	  if(locator[(*u)->neighbor]<toBeChecked.getNum()) //if the neighbor is less thatn the to be checked
	    {
	      if(curDist[(*u)->neighbor]>((*u)->wt+curDist[v])) //if the neighbor is greater than the wt and distance of v
		{
		  curDist[(*u)->neighbor]=((*u)->wt+curDist[v]); //set the neighbor to the weight plus curent distance
		  predecessor[(*u)->neighbor]=v; //set the predecessor to v
		  toBeChecked.fixHeap(curDist,locator,locator[(*u)->neighbor]);//fix the heap of to be checked
		}
	    }
	}
    }
  showShortestDistance(curDist,predecessor,start); //send all info to show shortest distance
  delete[] curDist; //delete all  arrays
  delete[] predecessor;
  delete[] locator;
}


#endif
  
