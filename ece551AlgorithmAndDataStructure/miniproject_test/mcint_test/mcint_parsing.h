#ifndef _mcint_parsing_
#define _mcint_parsing_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<string>
#include<vector>
#include<ctime>
#include"equ_cal.h"
using namespace std;

float mcint_parsing(string input,map<string,Nodes*>&function_map){
	char *command_temp=strdup(input.c_str());
	strtok(command_temp," ()");
	int paras_size=0;
  Nodes* func=is_exist_function(strtok(NULL," ()"),function_map);
  assert(func!=NULL);
  float times=strtof(strtok(NULL," ()"),NULL);
  assert(times>0);
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
    assert((high_boundary[paras_size]-low_boundary[paras_size])>0);
		paras_size++;
	}
  assert(paras_size==func->paras_size);
  vector<float> width;
  vector<float> input_paras;
	float integration=0;	
  
  vector<float>::iterator it0;
  vector<float>::iterator it1;
  assert(low_boundary.size()==high_boundary.size());
  
  float block=1;
	for(it0=low_boundary.begin(),it1=high_boundary.begin();it0!=low_boundary.end();it0++,it1++){
		block*=(*it1-*it0);
    width.push_back(*it1-*it0);
	}
  block/=times;
  srand((unsigned)time(0));
	for(int i=0;i<times;i++){
		input_paras.clear();
		for(it0=width.begin(),it1=low_boundary.begin();it0!=width.end();it0++,it1++){
			input_paras.push_back((float)((rand()/(double)(RAND_MAX))*(*it0)+*it1));
		}
		integration+=equ_cal(func,input_paras)*block;
	}
  cout<<"The MC Integration of "<<input<<"  "<<integration<<endl;	
	return integration;
}
	


#endif
