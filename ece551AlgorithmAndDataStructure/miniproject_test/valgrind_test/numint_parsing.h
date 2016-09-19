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
	if(func==NULL){
		cerr<<"unknown function name"<<endl;
		abort();
	}
  assert(func!=NULL);
  double delta=strtod(strtok(NULL," ()"),NULL);
  if(delta<=0){
		cerr<<"delta must larger than zero"<<endl;
		abort();
	}
  assert(delta>0);
  char* low=NULL;
 	vector<double> low_boundary;
  vector<double> high_boundary;
   
  while(1){
    if((low=strtok(NULL," ()"))==NULL)
			break;
    char* high=strtok(NULL," ()");
    assert((low!=NULL)&&(high!=NULL));
		if((!is_num(low))||(!is_num(high))){
			cerr<<"The input boundary is not num"<<endl;
			abort();
		}
	  low_boundary.push_back(strtod(low,NULL));
    high_boundary.push_back(strtod(high,NULL));
    if((high_boundary[paras_size]-low_boundary[paras_size])<delta){
			cerr<<"The range between high and low must larger than delta"<<endl;
			abort();
		}
    assert((high_boundary[paras_size]-low_boundary[paras_size])>=delta);
		paras_size++;
	}
  if(paras_size!=func->paras_size){
		cerr<<"Miss some variables' range"<<endl;
		abort();
	}
  assert(paras_size==func->paras_size);
  vector<double>::iterator it;
  for(it=low_boundary.begin();it!=low_boundary.end();it++){
		*it+=delta/2;
	}
	if(low_boundary.size()!=high_boundary.size()){
		cerr<<"The input high and low boundary could not match"<<endl;
		abort();
	} 
	assert(low_boundary.size()==high_boundary.size());
  vector<double> input_paras=low_boundary;
	double integration=0;	
  double block=pow(delta,paras_size);
	while(input_paras[paras_size-1]<high_boundary[paras_size-1]){
		if(paras_size!=1){
			for(int i=0;i<paras_size-1;i++){
				if(input_paras[i]>=high_boundary[i]){
					input_paras[i]=low_boundary[i];
					input_paras[i+1]+=delta;
				}
      	else if(i==0){
					integration+=equ_cal(func,input_paras)*block;
					input_paras[i]+=delta;
				}
			}
		}
		else{
			integration+=equ_cal(func,input_paras)*block;
			input_paras[0]+=delta;
		}
	}	
  cout<<"The Numerical Integration of "<<input<<"  "<<integration<<endl<<endl;	
	free(command_temp);
	return integration;
}
#endif
