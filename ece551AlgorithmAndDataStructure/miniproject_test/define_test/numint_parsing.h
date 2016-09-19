#ifndef _numint_parsing_
#define _numint_parsing_
#include<iostream>
#include<cstdlib>
#include<cstdlio>
#include<assert.h>
#include<string>
#include<map>
#include<vector>
#include"check_list.h"
#include<math.h>
#include"equ_cal.h"

float numint_parsing(string input,map<string,Nodes*> &function_map){
	char *command_temp=strdup(input.c_str());
  strtok(command_temp," ()");
  int paras_size=0;
  assert((Nodes* func=is_exist_function(strtok(NULL," ()"),function_map))!=NULL);
  assert((float delta=strtof(strtok(NULL," ()"),NULL))>0);
  while(1){
    if((char* low=strtok(NULL," ()"))==NULL)
			break;
    char* high=strtok(NULL," ()");
    assert((low!=NULL)&&(high!=NULL));
		vector<float> low_boundary.push_back(strtof(low,NULL));
    vector<float> high_boundary.push_back(strtof(high,NULL));
    assert((high_boundary[paras_size]-low_boundary[paras_size])>=delta);
		paras_size++;
	}
  assert(paras_size==func->paras_size);
  vector<float>::iterator it;
  for(it=low_boundary.begin();it!=low_boundary.end();it++){
		*it+=delta;
	}
  vector<float> input_paras=low_boundary;
	float integration=0;	
  float block=pow(delta,paras_size);
	while(input_paras[paras_size-1]<high[paras_size-1]){
		for(int i=0;i<paras_size-1;i++){
			if(input_paras[i]>=high[i]){
				input_paras[i]=low_boundary[i];
				input_paras[i+1]+=delta;
			}
      else if(i==0)
				input_paras[i]+=delta;
		}
		integration+=equ_cal(func,input_paras[i])*block;
	}		
	return integration;
}
#endif
