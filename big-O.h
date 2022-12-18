/**********************************
CS311 Kazumi Slott

Your name:Eric Hernandez
Your program number:18
Hours spent:5
Describe any difficulties here:understanding pseudo code and translating it into code 
*********************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
********************************************************************/


//What is the runtime complexity of this algorithm? O(n^3)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
int algoA(const int a[], int sz)//Don't change the function headers
{
  
  int sum = 0;//the new sum to be totaled up
  int max = 0;//declare the sum as 0 -- max value
  for(int i = 1; i <= sz; i++)//used to increment the size 
    {
      for(int j = 0; j < sz; j++)//to tranverse the array
	{
	  for(int k = j; k <= i-1; k++)// to tranverse the array
	    {
	      sum += a[k];//this collects the sum of values 
	    }
	  if(sum >= max)//if new sum is higher value than current max
	    max = sum;//sum has to be set to the newest sum that was recorded.
	  sum = 0;//resets it to zero 
	}
    }
  return max;//returns the highest value of sum to 
}

//What is the runtime complexity of this algorithm? O( n^2)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoB(const int a[], int sz)
{
  int max = 0;//max sum
  int sum=0;
  for(int i = 0; i < sz; i++)//tranverse the array
    {
      for(int j = i; j <= sz; j++)//to tranverse the array
	{
	  sum += a[j];//adds the sum of the subarray
	  if(sum >= max)//if new sum is greater than the max value
	    max = sum;//sets new sum as max
	}
      sum = 0;//this is to reset the value in order to view on the next index
    }
  return max;//to return the value that has been totaled for the high max value
}

//What is the runtime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoC(const int a[], int sz)
{
  int max=0; //initilizing the max sum
  int sum=0; //intitializing the sum
  
  for(int i=0;i<sz;i++)//tranverse array
    {
      sum+=a[i]; //finds sum of subarray
      if(sum>max) //if sum is greater than max,sum becomes new amx
	max=sum;

      if(sum<0) //if sum is anegative reset and start from next incriment
	{
	  sum=0;
	}
    }
  return max; //return the max sum
}
