#include<iostream>
#include<math.h>
#include"function.h"
#include<cstdlib>

using namespace std;

int binarySearchForZero_helper(Function<int, int> *f, int low, int high){
  if(low==high){
    return low;
  }
  int middle=f->invoke((low+high)/2);
	int temp=0;
  if(middle==0){
    return (low+high)/2;
  }
  else if(low==(high-1)){
		if((low+high)>=0){
				temp=f->invoke(high);
    		if(abs(middle)>abs(temp))
      		return high;
				else if(abs(middle)==abs(temp)){
					if(middle<0)
						return high;
					else
						return low;
				}
    		else 
      		return low;
		}
		else{
			temp=f->invoke(low);
			if(abs(middle)>abs(temp))
				return low;
			else if(abs(middle)==abs(temp)){
				if(middle<0)
					return high;
				else
					return low;
			}
			else
				return high;
		}
  }
  else if(low==(high-2)){
    if(middle<0){
      if(abs(middle)>=abs(f->invoke(high)))
				return high;
      else
				return (low+high)/2;
    }
    else{
      if(abs(middle)>=abs(f->invoke(low)))
				return low;
      else 	
				return (low+high)/2;
    }
  }
  
  else if(middle<0){
    return binarySearchForZero_helper(f, (low+high)/2, high);
  }
  else{
    return binarySearchForZero_helper(f, low, (low+high)/2);
  }
}

int binarySearchForZero(Function<int,int>*f, int low, int high){
	if(f->invoke(high-1)<=0)
		return (high-1);
	if(low>=(high-1))
		return low;
	return binarySearchForZero_helper(f,low,high-1);
}

int main(){
	SinFunction f;
	cout<<binarySearchForZero(&f,0,150000)<<endl;
	cout<<f.n<<endl;
	return 0;
}
