/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: 
Your name: Eric Hernandez
Your programmer number: 18
Hours spent making this application: 3
Are you rejecting invalid inputs?: yes 
Any difficulties:  i got an infinite loop forgetting what getData does
********************************************************/
#include <iostream>
#include <stdexcept>//for exception, invalid_argument
#include <string>//for stoi()
using namespace std; 
#include "minHeap.h"
#include "/cs/slott/cs211/checkInput.h" //You might want to check this header to see if you could use getData(min, max, errorMessage). You don't have to use it.

//I made a total of 5 functions in addition to main(). You can make as many functions as you need.
void showMenu();
void getNextP(minHeap<int>& h);
void checkIn(minHeap<int>& h);
int getNum();
int getSeverity();

const int START = 1000; //assuming this number will not go over 9999
int numP=0;
int main()
{
  //call showMenu() to show the menu
  int ans;
  minHeap<int> h(9999-START+1); //make a heap called h
  do{
    showMenu(); //shjow menu
    ans =getNum(); //get input of user
    if(ans==1) //if its 1
       {
	 checkIn(h); //check in the next patient
	 
       }
    else if(ans==2) //if 2
       {
	 getNextP(h); //remove the first patient and display them as now serviung
       
       }
     cout<<"The queue has "<<h;
     }
  while(ans!=3); //if its 3 exit program

  //You need to have the following prompt somewhere. You can move it to a different function.
  //cout << "Enter a severity, 1 most severe, .. 5 least severe: ";

  return 0;
}

//Show the menu
void showMenu()
{
  cout << "---------------------------------------------------" << endl;
  cout << "1: Patient Check in" << endl;
  cout << "2: Doctor takes a next patient" << endl;
  cout << "3: End" << endl;
}

//You don't need to use this function. If you decide to use it, compile your program using -std=c++11 (check my homework instructions)
//This function rejects non-integers. It returns an integer only.
int getNum()
{
   string choice; //For example, when asking for 10, the user enters ab 
   bool bad;
   int num;

   do
     {
       bad = false;
       cout << "Enter a number: ";
       cin >> choice; 

       try
	 {

	   num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
	   if(num<1||num>3)
	     {
	     cout<< "Invalid choice. The choice should be 1, 2, or 3.";
	     bad =true;
	     }
	 }
       catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
	 {
	   cout << "Your choice has to be a number. ";
	   bad = true;
	 }
     }while(bad == true);

   return num;
}

void getNextP(minHeap<int>& h)
{
  try
    {
      cout << h.getMin()<<" is going to be treated now"<<endl; //try to get next patient
       
    }
  catch(minHeap<int>::BadIndex)
    {
      cout<<"There are no patients waiting"<<endl; //if bad index means no one is waiting
    }
}
void checkIn(minHeap<int>& h)
{
  cout<< "Enter a severity, 1 most severe, .. 5 least severe: ";
  int severity=getSeverity(); //ask for the severity
  severity=(severity* 10000) +START +numP; //multiply by 10000 +start +num
  h.insert(severity);// insert it into the queue
  numP++; //incrimnet patient count
  

}
int getSeverity() //get num for severity to account for 1-5
{
  string choice; //For example, when asking for 10, the user enters ab
  bool bad;
  int num;

   do
     {
       bad = false;
       cin >> choice;

       try
         {

           num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
           if(num<1||num>5)
             {
	       cout<< "Invalid choice. Needs to be 1-5";
	       bad =true;
             }
         }
       catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
         {
           cout << "Your choice has to be a number. ";
           bad = true;
         }
     }while(bad == true);

   return num;

}
     
