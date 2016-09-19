#ifndef _equ_cal_
#define _equ_cal_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<string>
#include<vector>
#include"equation_tree.h"
float equ_cal(Nodes* func, vector<float> input_paras){
	assert(input_paras.size()==(unsigned)func->paras_size);
	for(unsigned i=0;i<input_paras.size();i++){
		func->para_assign(vector[i]);
	}
	return func->eval();
}

#endif	
