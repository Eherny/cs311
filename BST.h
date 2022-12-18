/****************
Template created by Kazumi Slott
CS311

Your name: Eric Hernandez
Your programmer number: 18
Hours spent?:1
Any difficulties?: nah i had 211
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template <class T>
class BST;

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>  //make it a templare class
class Node
{
  friend class BST<T>; //BST wants to access private members of Node
private:
  T el;
  Node* right;
  Node* left;
public:
  Node() {right = left = NULL;}; //default constructor. set right and left to N0ULL
  Node(const T& e){el=e;right=NULL;left=NULL;}; 
  T getEl() const {return el;} //returns el
};

//Make it a template class
template <class T>
class BST
{
private:
  Node<T>* root; //check stack_L_T.h to see how to declare top
  void insertNodeR(Node<T>*& p, const T& e);
  void inOrderPrint(Node<T>* p);
  void preOrderPrint(Node<T>* p);
  void postOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  int getMinLength(Node<T>* p);
  int getNumNodes(Node<T>* p); 
  int getEvenNodes(Node<T>* p);
  Node<T>* searchR(Node<T>* p,const T& el);
  void destroy(Node<T>* p);
  void remove(Node<T>*& p);  
  //You will need 10 private functions here.  WHY private?
  // these private functions are needed in for when the publics
  //functions call the root it can access the private data function

 public:
  BST() {root=NULL;} //implement constructor here
  ~BST(); 
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  int getMaxLength();
  int getMinLength();
  int getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  Node<T>* searchR(const T& e);
  bool remove(const T& e);
  void DFTprint();
  void BFTprint();
};

//implement the member functions in the header if you are making a template class


//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
BST<T>::~BST()
{
  destroy(root); //calls the recursive function
}

template <class T>
void BST<T>::destroy(Node<T>* p) //private function. WHY?
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

template <class T>
void  BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e); //call the private root, e function
}

template <class T>
void BST<T>::insertNodeR(Node<T>*& p, const T& e) //private function. WHY?
{
  if(p==NULL) //if p== NULL
    p=new Node<T>(e); //make the root and new node intothe element
  else if(e<p->el) //else if e is < the element
    insertNodeR(p->left,e); //insert it into the left
  else
    insertNodeR(p->right,e); //insert it into the right
}



//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void BST<T>::insertNodeI(const T& e)
{
  Node<T>* newNode =new Node<T>(e);// make a new node.  Check stack_L_T.h to see how you made a new node.
  Node<T>* p = root;
  Node<T>* parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; //make the parent p
      if(e < p->el)  //if the element is less than the element
	p = p->left;  //make the element the left
      else //p->el <= e
	p = p->right; //make the element the right
    }

  if(parent == NULL) //tree is empty
    root = newNode; //make the root the newNode
  else if(e < parent->el) //insert a child as the parent's left child
    parent->left = newNode; //make the parents left a new node
  else //parent->el <= e //insert a child as the parent's left child
    parent->right = newNode; //make the parents right child a new node
}



//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void BST<T>::inOrderPrint()
{
  inOrderPrint(root); //call the private function

}

template <class T> //private function. WHY?
void BST<T>::inOrderPrint(Node<T>* p)
{
  if(p==NULL) //if node is null
    return; //return
  inOrderPrint(p->left); // call it for t he left
  cout<<p->el<<"-->"; // cout the element
  inOrderPrint(p->right); //call the right
}



template <class T>
void BST<T>::preOrderPrint()
{
  preOrderPrint(root);  //pre means print parent->left child ->right child
}

template <class T>
void BST<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if(p==NULL)//if node is empty
    return; 
  cout<<p->el<<"-->"; //cout the element
  preOrderPrint(p->left); //call ffor the left
  preOrderPrint(p->right); //call for the right
}



template <class T>
void BST<T>::postOrderPrint()
{
  postOrderPrint(root);  //post means left->right->parent last
}

template <class T>
void BST<T>::postOrderPrint(Node<T>* p) //private function. WHY?
{
  if(p==NULL) //if p is null
    return; //reutnr
  postOrderPrint(p->left); //call left
  postOrderPrint(p->right); //call right
  cout<<p->el<<"-->"; //cout element
}



//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions – getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

template <class T>
int BST<T>::getNumNodes()
{
  return getNumNodes(root);  //call private function
}

template <class T>
int BST<T>::getNumNodes(Node<T>* p) //private function WHY?
{
  if(p==NULL) //if tree is empty
    return 0;
  else
    return getNumNodes(p->left) + getNumNodes(p->right) + 1; //call left nd right and incriment each time
}



//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{
  return getMaxLength(root); //get max lenght

}

template <class T>
int BST<T>::getMaxLength(Node<T>* p) //private function. Why?
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
int BST<T>::getMinLength()
{
  getMinLength(root); //get min length private function
  
}

template <class T>
int BST<T>::getMinLength(Node<T>* p) //private function. WHY?
{
  if(p==NULL)//if tree is empty
    return 0; //return 0
  else
    {
      int left,right;
      left=getMinLength(p->left)+1; //call for left and incriment each time
      right=getMinLength(p->right)+1; //call for right and incriment each time
      if(left<right) //is left is less than right
	return left; //call left
      if(right<=left) //if right is less than equak
	return right; //call right
    }  
}


                                                                                                    
//This function will return the number of even elements
template <class T>                                                                                   
int BST<T>::getEvenNodes()                                                                            
{                                                                                                     
  getEvenNodes(root);             //call private function                                                                                         
}                                                                                                     
                                                                                                      
template <class T>                                                                                    
int BST<T>::getEvenNodes(Node<T>* p) //private function. WHY?                                              
{ 
  int num=0; //
  if( p==NULL )//if p tree is empty
    return 0;  //return 0
  else
    {
      if((p->el)%2==0) //do math to check if its even
	num++; //incriment
      return num+getEvenNodes(p->left)+getEvenNodes(p->right); //add number and call keft and right
    }                                                                                                    
                                                                                                      
}                                                                                                     




//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchI(const T& e)
{
  Node<T>* p = root; //make the node the root

  while(p !=  NULL)
    {
      if(p->el==e)  //if element is it return
	return p; //return p
      else if(p->el>e) //if its > e call for the left
	p=p->left;
      else
	p=p->right; //else call for the right
    }
  return p; //return null at end if it its empty or doesnt find 
  //Where do you return NULL?  

}



//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchR(const T& e)
{
  return searchR(root,e); //call private function

}

template <class T>
Node<T>* BST<T>::searchR(Node<T>* p, const T& e) //private function. WHY?
{
  if(p==NULL) //if p is empty
    return NULL; //return null
  else
    {
      if(p->el==e) //if its element return p
	return p;
      else if(e<p->el) //if element is less than
	searchR(p->left,e); //call it again for left
      else if(e>p->el)
	searchR(p->right,e); //call it from the right
    }

}
template <class T>
void BST<T>::BFTprint()
{
  Node<T>* front;//create a node called front
  queue<Node<T>*> q; //create a queue
  if(root==NULL) //if root is null hit return
    return;
  q.push(root); //push the root into the queue
  while(!q.empty()) //while queue is not empty
    {
      front=q.front(); //get the front value     
      cout<<front->el<<"-->"; //print it out
      q.pop(); //pop out the value
      if(front->left!=NULL) //if there is a left child push it in
	q.push(front->left);
      if(front->right!=NULL) //if there is a right child push it in
	q.push(front->right);

 
    }
}

template <class T>
void BST<T>::DFTprint()
{
  Node<T>* top; //make a node called top
  stack<Node<T>*> s; //create a template stack
  if(root==NULL) //if root is empty return
    return;

  s.push(root); //push the root into the stack

  while(!s.empty()) //while stack is not empty
    {
      top=s.top(); //get the top value
      s.pop(); //pop it out
      cout<<top->el<<"-->"; //then display it

      if(top->right!=NULL) //if right child exists push it in
	s.push(top->right);
      if(top->left!=NULL) //if left child exists push it in
	s.push(top->left);

      
    }
}
template <class T>
bool BST<T>::remove(const T& e)
{
  Node<T>* del = root; //del will point to the node to be deleted
  Node<T>* parent = NULL; //parent will 

  //look for e in the tree
  while(del!=NULL && del->el!=e) //If root is NULL, del is NULL to start with
    {
      //While won't be entered and return false down below.
      //parent follows del. In other words, del is ahead of parent. --> you did	\
      // something similar in insertI()
      //del will eventually point to the node to be deleted.
      parent=del;
      if(e<del->el)
	del=del->left;
      else
	del=del->right;
      
    }
  
  //e doesn't exist or tree is empty.
  if(del==NULL)
    return false;
  
  //check to see if root should be removed
  if(parent==NULL)
    remove(root); //root will change. call the other remove function down below
  //We are deleting a node other than the root node. Figure out if del's node i	\
  //s left or right child of parent's node
  else if(parent->left->el==e) //parent's left child to be removed
    remove(parent->left);
  else //parent's right child to be removed
    remove(parent->right);
  
  //deleted the node with e
  return true;
  
}


template <class T>
void BST<T>::remove(Node<T>*& p) //private function
{
  Node<T>* temp = p; //temp points to the node to be deleted initially
  Node<T>* t_parent; //t_parent will point to the parent node of temp's node

  //the node to be deleted has no right child (Check Diagram1-Right and Left in\
  //  the homework document "HMWK BST - BFT, DFT and remove" under "Assignments")
//If the node to be deleted has no children, the following if will be execute\
  //d.(Check Diagram2-Right and Left)
  if(p->right==NULL)
    p = p->left; //p(The left or right coming out of parent of del's node) now \
  //points to the root of the left subtree under del's node. DONE.  If the node to \
  //be deleted has no children, p is set to NULL because p->left is NULL.
  //the node to be deleted has no left child (Check Diagram 3-Right and Left)
  else if(p->left==NULL)
    p=p->right;
  //p(The left or right coming out of parent of del's node) now poin	\
  //ts to the root of the right subtree under del's node. DONE.
  //If the node to be deleted has 2 children
  else
    {
      //we are going to replace e by the largest value in the left subtree
      temp = p->left; //temp points to the root of the left subtree under the no \
      //de to be deleted to start with
      t_parent = p; //t_parent points to the node to be deleted to start with

      //go to the largest value in the left subtree under the node to be delete\
      //d by going all the way down to right
      while(temp->right!=NULL)
        {
          t_parent = temp; //temp is ahead of t_parent
          temp = temp->right; //temp will eventually point to the largest value
        }
      //copy the largest value into the node to be deleted
      p->el=temp->el;

      if(temp==p->left) //the largest value is the direct left child of the node who\
	//se value was replaced by the largest (Diagram 4-one child or no children)
        p->left=temp->left; //connect the left of the node whose value was replaced by th\
      //e largest value to the left child of the node that has the largest value
      else //the largest value is NOT the direct left child of the node whose v\
	//alue was replaced by the largest (Diagram 5-one child and no children)
        t_parent->right=temp->left; //If the node with the largest value doesn't have any childre\
	//n, t_parent->right is set to NULL.
									}
//finally delete temp;
delete temp;
}

#endif
