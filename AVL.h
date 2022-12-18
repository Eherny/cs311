/****************
Template created by Kazumi Slott
CS311

Your name: Eric Hernandez
Your programmer number: 18
Hours spent?:1
Any difficulties?: nah i had 211
*****************/

#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template <class T>
class AVL;

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>  //make it a templare class
class Node
{
  friend class AVL<T>; //BST wants to access private members of Node
private:
  T el;
  Node* right;
  Node* left;
  Node* up;
  int BF;
public:
  Node() {right = left = up =  NULL;BF = 0;}; //default constructor. set right and left to N0ULL
  Node(const T& e){el=e;right = NULL;  left = NULL; up = NULL; BF = 0;}; 
  T getEl() const {return el;} //returns el
};

//Make it a template class
template <class T>
class AVL
{
private:
  Node<T>* root; //check stack_L_T.h to see how to declare top
  void destroy(Node<T>* p);
  void inOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  Node<T>* rightRotation(Node<T>* P);
  Node<T>* leftRotation(Node<T>* P);
  void balanceTree(Node<T>* newNode);
  Node<T>* updateBF(Node<T>* Q);
  
   //You will need 10 private functions here.  WHY private?
  // these private functions are needed in for when the publics
  //functions call the root it can access the private data function

 public:
  AVL() {root=NULL;} //implement constructor here
  ~AVL(); 
  void insertNodeI(const T& e);
  void inOrderPrint();
  void BFTprint();
  int getMaxLength();
  
};

//implement the member functions in the header if you are making a template class


//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
AVL<T>::~AVL()
{
  destroy(root); //calls the recursive function
}

template <class T>
void AVL<T>::destroy(Node<T>* p) //private function. WHY?
{
  if(p == NULL)  //destroy all nodes //if root is null return
    return;
  destroy(p->left); //destroy left child
  destroy(p->right);//then destory right
  delete p; //then delete the pointer
}



//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST – insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()





//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void AVL<T>::insertNodeI(const T& e)
{
  Node<T>* newNode =new Node<T>(e); //set the new node to a new node with e in it
  Node<T>* p = root; //set parent to root
  Node<T>* parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      
      parent = p; //make the parent p
      if(e < p->el)  //if the element is less than the element
	p = p->left;  //make the element the left
      else //p->el <= e
	p = p->right; //make the element the right
    }

  if(parent == NULL) //tree is empty
    root = newNode; //make the root the newNode
  else if(e < parent->el) //insert a child as the parent's left child
    {
      parent->left = newNode; //make the parents left a new node
      
    }
  else //parent->el <= e //insert a child as the parent's left child
    {
      parent->right = newNode; //make the parents right child a new node
    }
  newNode->up=parent; //make the new nodes up node to parent
  balanceTree(newNode); //call balance tree with it
}



//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void AVL<T>::inOrderPrint()
{
  inOrderPrint(root); //call the private function

}

template <class T> //private function. WHY?
void AVL<T>::inOrderPrint(Node<T>* p)
{
  if(p==NULL) //if node is null
    return; //return
  inOrderPrint(p->left); // call it for t he left
  cout<<p->el<<" "<<p->BF<<"-->"; // cout the element
  inOrderPrint(p->right); //call the right
}




template <class T>
void AVL<T>::BFTprint()
{
  Node<T>* front;//create a node called front
  queue<Node<T>*> q; //create a queue
  if(root==NULL)
    return;
  q.push(root); //push the root into the queue
  
  while(!q.empty()) //while queue is not empty
    {
      front=q.front(); //get the front value
      if(front==root)
	{
	  cout<<front->el<<" "<<front->BF<<" -->"; //cout the element
	q.pop(); //pop it out
	}
      else
	{    
	  cout<<front->el<<" "<< front->BF<<" "<<front->up->el<<"-->";//cout the element
	  q.pop();  //pop it out
	}
      if(front->left!=NULL) //if there is a left child push it in
	q.push(front->left);
      if(front->right!=NULL) //if there is a right child push it in
	q.push(front->right);
      
      
    }
}
template <class T>
int AVL<T>::getMaxLength()
{
  return getMaxLength(root); //get max lenght
  
}


template <class T>
int AVL<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if(p==NULL) //if tree is empty
    return 0; //return 0
  else
    {
      int left,right;
      left=getMaxLength(p->left)+1; //call for left
      right=getMaxLength(p->right)+1; //call for right
      if(left>=right) //if left is more than right
        return left; //return left
      if(right>left) //call right more than left
        return right; //return right
    }
}

template <class T>
void AVL<T>::balanceTree(Node<T>* newNode)
{
  
  Node<T>* P = updateBF(newNode); //make a new node and update BF with new node
  if(P==NULL) //if tis null
    return;  //return and do nothing
  
  Node<T>* temp; //make a pointer
  if(P->BF == 2 && P->left !=NULL && P->left->BF == 1)//if its LL violation
    {
      P=rightRotation(P); //right rotate
    } 
  else if(P->BF == 2 && P->left != NULL && P->left->BF == -1)//if its LR violation
    {
      temp=leftRotation(P->left); //call left rotation of the left value
      temp->up= P; //update up pointer
      P->left = temp; //make p->lefts equal tot temp
      P=rightRotation(P); //right rotatte
    }
  else if(P->BF == -2 && P->right != NULL && P->right->BF == 1)//if its RL violation
    {
      temp =rightRotation(P->right); //make temp node equal to right rotation from right node
      temp->up = P; //update up pointer
      P->right= temp; //make right to temp 
      P = leftRotation(P); //call left rotation
    }
  else if(P->BF == -2 && P->right != NULL && P->right->BF == -1) //if its RR violatiuon
    {
      P= leftRotation(P); //call left rotation
    }


  if(P->up == NULL) // if its the root
    {
      root = P; //set root equal to the violation
    } 
  else
    {
      Node<T>* parent = P->up; //update pointer
      if(parent == root) //if its the root
	{
	  if(P->el < root->el) //if its left chjild
	    parent->left=P;
	  else if(P->el > root->el)  //if its right child
	    parent->right=P;
	}
      else
	{
	  if (parent->left == P) //if its left
	    parent->left=P; //connect iot
	  else
	    parent->right=P; //connect it
	}
    }
}

template <class T>
Node<T>* AVL<T>::rightRotation(Node<T>* P)
{
  
  Node<T>* n=P->left; //make an element equal to the inserted nodes left
  n->up = P->up; //make an elements up equal to new elements up
  Node<T>* r = n->right; //make a node r equal to the right
  if(r!=NULL) //if its not empty
    r->up = P; //the up is new node
  n->right = P; //the nodes right is p
  P->left = r; //new nodes left is the right soide
  P->up = n; // update up
  
   
  P->BF=getMaxLength(P->left)-getMaxLength(P->right); //calculate P bf
  n->BF=getMaxLength(n->left)-getMaxLength(n->right); //calculate n BF
  return n;
  
  
}

template <class T>
Node<T>* AVL<T>::leftRotation(Node<T>* P)
{
  
  Node<T>* n = P->right; //set a new element to the enw elements right
  n->up = P->up;   //update up pointer
  Node<T>* l = n->left; //make an element equal to the new pointers 
  if(l!=NULL) //if it doesnt exist
    l->up = P; // update the up pointer
  
  n->left = P; //make node to the left equal the new element
  P->right = l; //make new elements right the temp node
  P->up = n; //update up pointer
  
  P->BF=getMaxLength(P->left)-getMaxLength(P->right); //calculate new BF's
  n->BF=getMaxLength(n->left)-getMaxLength(n->right); 
  return n;
  
  
  
  
}

template <class T>
Node<T>* AVL<T>::updateBF(Node<T>* Q)
{
  Node<T>* P=Q->up; //P is the parent of q
  if(P == NULL) //if p is null
    return NULL; //return null
  if(P->left == Q) //if Q is the left child of p 
    P->BF++; //incriment bf
  else
    P->BF--; //decrement BF

  while(P != root && P->BF != 2 && P->BF != -2) //whjile its not root and not equal to 2 -2
    {
      Q = P; //q is p
      P = P->up; //p is parent 
      if(Q->BF == 0) //if BF is 0
	return NULL; //return null
      else if(P->left == Q) //if pleft is Q
	P->BF++; //incriment BF
      else
	P->BF--; //decrement BF
    }  
  if(P->BF == 2 || P->BF == -2) //if p not 2 or -2
    return P; //Return P
  return NULL;//return NULL if it runs throughb and nothing happens
  
}
#endif
