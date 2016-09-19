#ifndef _gradient_parsing_
#define _gradient_parsing_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<string>
#include<vector>
#include"equ_cal.h"
#include"check_list.h"
#include"gradient_cal.h"
using namespace std;

vector<double> gradient_parsing(string input,map<string,Nodes*> &function_map){
 char *command_temp=strdup(input.c_str());
 strtok(command_temp," ()");
 Nodes* func=is_exist_function(strtok(NULL," ()"),function_map);
 assert(func!=NULL);
 double gamma=strtod(strtok(NULL," ()"),NULL);
 assert(gamma!=0);
 double error=strtod(strtok(NULL," ()"),NULL);
 assert(error>0);
 
 char* initial_num=NULL;
 vector<double> input_paras;
 vector<double> gradient;
 
	while(1){
	if((initial_num=strtok(NULL," ()"))==NULL)
		break;
	assert(is_num(initial_num));
	input_paras.push_back(strtod(initial_num,NULL));
  }
  
  assert(input_paras.size()==(unsigned)func->paras_size);
  double distance_n=0;

  gradient=gradient_cal(func,input_paras,equ_cal(func,input_paras),gamma,distance_n);
  while(1){
		for(unsigned i=0;i<input_paras.size();i++){
		  input_paras[i]+=gamma*gradient[i];
		}
		if(distance_n<=error){
			break;
		}
		gradient=gradient_cal(func,input_paras,equ_cal(func,input_paras),gamma,distance_n);
	}
	cout<<input<<":"<<endl;
	for(unsigned i=0;i<input_paras.size();i++){
		cout<<" "<<input_paras[i];
	}
	cout<<endl;
	free(command_temp);
  return gradient;	
}

#endif
