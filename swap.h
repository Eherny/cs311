/********************************
The following mySwap works like the swap function in the library.

Your name:Eric Hernandez
Your programmer number:18
Hours spent:.02 
Any difficulties?:forgetting not to put const for changing paramaters
********************************/

template <class T>
const T& mySwap( T& a, T& b)
{
  T temp;
  temp=a;
  a=b;
  b=temp;

}
