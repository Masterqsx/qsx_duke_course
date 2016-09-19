#ifndef _gradient_cal_
#define _gradient_cal_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<vector>
#include"equ_cal.h"
#include<math.h>
vector<double> gradient_cal(Nodes* func, vector<double> input_paras,double base,double gamma,double &distance_n){
	assert(input_paras.size()==(unsigned)func->paras_size);
  vector<double> gradient;
  vector<double> step_paras;
  distance_n=0;
  for(unsigned i=0;i<input_paras.size();i++){
		step_paras=input_paras;
    step_paras[i]+=0.00000001;
		gradient.push_back((equ_cal(func,step_paras)-base)/0.00000001);
    distance_n+=gamma*gamma*gradient[i]*gradient[i];
	}
	distance_n=sqrt(distance_n);
	return gradient;
}
	
#endif
