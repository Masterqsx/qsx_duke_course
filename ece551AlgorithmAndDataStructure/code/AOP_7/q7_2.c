#include<stdio.h>
#include<stdlib.h>

double fabs(double in){
	if(in>=0)
		return in;
	else
		return -1*in;
}

double mySqrt_helper(double d,double h,double l,double guess){
	if(fabs(guess*guess-d)<=0.001)
	  return guess;
	if(guess*guess>d){
		return mySqrt_helper(d,guess,l,(guess-l)/2+l);
	}
	else{
		return mySqrt_helper(d,h,guess,(h-guess)/2+guess);
	}
}

double mySqrt(double d){
	return mySqrt_helper(d,d,0,d/2);
}

int main(int args,char **argv){
	if(args!=2){
		fprintf(stderr,"invalid input argument\n");
		return EXIT_FAILURE;
	}
	printf("%f\n",mySqrt(atof(argv[1])));
	return EXIT_SUCCESS;
}
		
