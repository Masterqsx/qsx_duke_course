#ifndef _equ_cal_
#define _equ_cal_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<vector>
#include"equation_tree.h"
float equ_cal(Nodes* func, vector<float> input_paras){
	assert(input_paras.size()==(unsigned)func->paras_size);
	func->paras_num.clear();
	for(unsigned i=0;i<input_paras.size();i++){
		func->para_assign(input_paras[i]);
	}
	return func->eval();
}

#endif	
