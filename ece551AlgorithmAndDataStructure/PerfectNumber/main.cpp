#include<iostream>
#include<math.h>
using namespace std;

int main()
{
//	int *number;
	int input,i=0;
//	number = new int;
	cout <<"Enter your number"<<endl;
	cin >>input;
	while((pow(2,i-1)*(pow(2,i)-1))<=input )
	{
	 	if(pow(2,i-1)*(pow(2,i)-1)==input)
		{
			cout<<input<<"  is perfect number"<<endl;
			return input;
		}
		else
		{
			i++;
		}
	}	
	
	cout<<input<<"  is not perfect"<<endl;

	
//	delete []number;
	return 0;
}

