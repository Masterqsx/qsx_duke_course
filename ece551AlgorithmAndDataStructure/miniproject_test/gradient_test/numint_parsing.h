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
float numint_parsing(string input,map<string,Nodes*> &function_map){
	char *command_temp=strdup(input.c_str());
  strtok(command_temp," ()");
  int paras_size=0;
  Nodes* func=is_exist_function(strtok(NULL," ()"),function_map);
  assert(func!=NULL);
  float delta=strtof(strtok(NULL," ()"),NULL);
  assert(delta>0);
  char* low=NULL;
 	vector<float> low_boundary;
  vector<float> high_boundary;
   
  while(1){
    if((low=strtok(NULL," ()"))==NULL)
			break;
    char* high=strtok(NULL," ()");
    assert((low!=NULL)&&(high!=NULL));
	  low_boundary.push_back(strtof(low,NULL));
    high_boundary.push_back(strtof(high,NULL));
    assert((high_boundary[paras_size]-low_boundary[paras_size])>=delta);
		paras_size++;
	}
  assert(paras_size==func->paras_size);
  vector<float>::iterator it;
  for(it=low_boundary.begin();it!=low_boundary.end();it++){
		*it+=delta;
	}
	assert(low_boundary.size()==high_boundary.size());
  vector<float> input_paras=low_boundary;
	float integration=0;	
  float block=pow(delta,paras_size);
	while(input_paras[paras_size-1]<high_boundary[paras_size-1]){
		if(paras_size!=1){
			for(int i=0;i<paras_size-1;i++){
				if(input_paras[i]>=high_boundary[i]){
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
	delete command_temp;
	return integration;
}
#endif
