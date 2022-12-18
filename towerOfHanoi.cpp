#include <iostream>
using namespace std;

void towerOfHanoi(int n,int from,int to,int spare);
int moves;
int main()
{
  int n;
  cout<<"type in how many circles"<<endl;
  cin>>n;
  towerOfHanoi(n,1,3,2);
  cout<< moves<<endl;
}

void towerOfHanoi(int n,int from,int to,int spare)
{
  int x;
  if(n==1)
    {
      cout<<"Moving the disk from " << from<<" to "<<to<<" "<<endl;
      cin>>x;
      moves++;
    }
  else
    {
      towerOfHanoi(n-1,from,spare,to);
      towerOfHanoi(1,from,to,spare);
      towerOfHanoi(n-1,spare,to,from);
    }
  
  
}
