#ifndef _gradient_cal_
#define _gradient_cal_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<vector>
#include"equ_cal.h"
#include<math.h>
vector<float> gradient_cal(Nodes* func, vector<float> input_paras,float base,float gamma,float &distance_n){
	assert(input_paras.size()==(unsigned)func->paras_size);
  vector<float> gradient;
  vector<float> step_paras;
  distance_n=0;
  for(unsigned i=0;i<input_paras.size();i++){
		step_paras=input_paras;
    step_paras[i]+=0.001;
		gradient.push_back((equ_cal(func,step_paras)-base)/0.001);
    distance_n+=gamma*gamma*gradient[i]*gradient[i];
	}
	distance_n=sqrt(distance_n);
	return gradient;
}
	
#endif
