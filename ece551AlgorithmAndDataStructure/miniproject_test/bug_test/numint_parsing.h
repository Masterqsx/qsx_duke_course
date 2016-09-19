#ifndef _numint_parsing_
#define _numint_parsing_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<string>
#include<map>
#include<vector>
#include"check_list.h"
#include<math.h>
#include"equ_cal.h"
using namespace std;
double numint_parsing(string input,map<string,Nodes*> &function_map){
	char *command_temp=strdup(input.c_str());
  strtok(command_temp," ()");
  int paras_size=0;
  Nodes* func=is_exist_function(strtok(NULL," ()"),function_map);
  assert(func!=NULL);
  double delta=strtod(strtok(NULL," ()"),NULL);
  assert(delta>0);
  char* low=NULL;
 	vector<double> low_boundary;
  vector<double> high_boundary;
   
  while(1){
    if((low=strtok(NULL," ()"))==NULL)
			break;
    char* high=strtok(NULL," ()");
    assert((low!=NULL)&&(high!=NULL));
	  low_boundary.push_back(strtod(low,NULL));
    high_boundary.push_back(strtod(high,NULL));
    assert((high_boundary[paras_size]-low_boundary[paras_size])>=delta);
		paras_size++;
	}
  assert(paras_size==func->paras_size);
  vector<double>::iterator it;
  for(it=low_boundary.begin();it!=low_boundary.end();it++){
		*it+=delta/2;
	}
	assert(low_boundary.size()==high_boundary.size());
  vector<double> input_paras=low_boundary;
	double integration=0;	
  double block=pow(delta,paras_size);
	while(input_paras[paras_size-1]<=high_boundary[paras_size-1]){
		if(paras_size!=1){
			for(int i=0;i<paras_size-1;i++){
				if(input_paras[i]>high_boundary[i]){
					input_paras[i]=low_boundary[i];
					input_paras[i+1]+=delta;
				}
      	else if(i==0)
					input_paras[i]+=delta;
			}
		}
		else{
			input_paras[0]+=delta;
		}
		integration+=equ_cal(func,input_paras)*block;
	}	
  cout<<"The Numerical Integration of "<<input<<"  "<<integration<<endl;	
	free(command_temp);
	return integration;
}
#endif
