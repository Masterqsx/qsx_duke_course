#ifndef _mcint_parsing_
#define _mcint_parsing_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<string>
#include<vector>
#include<ctime>
#include"check_list.h"
#include"equ_cal.h"
using namespace std;

double mcint_parsing(string input,map<string,Nodes*>&function_map){
	char *command_temp=strdup(input.c_str());
	strtok(command_temp," ()");
	int paras_size=0;
  Nodes* func=is_exist_function(strtok(NULL," ()"),function_map);
  if(func==NULL){
		cerr<<"The input function does not exist"<<endl;
		abort();
	}
	assert(func!=NULL);
  double times=strtod(strtok(NULL," ()"),NULL);
	if(time<=0){
		cerr<<"The input times should larger than zero"<<endl;
		abort();
	}
  assert(times>0);
  char* low=NULL;
 	vector<double> low_boundary;
  vector<double> high_boundary;
   
  while(1){
    if((low=strtok(NULL," ()"))==NULL)
			break;
    char* high=strtok(NULL," ()");
		if((low==NULL)||(high==NULL)){
			cerr<<"The input boundary is not match"<<endl;
			abort();
		}
    assert((low!=NULL)&&(high!=NULL));
		if((!is_num(low))||(!is_num(high))){
			cerr<<"The input boundary is not num"<<endl;
			abort();
		}
	  low_boundary.push_back(strtod(low,NULL));
    high_boundary.push_back(strtod(high,NULL));
    assert((high_boundary[paras_size]-low_boundary[paras_size])>0);
		paras_size++;
	}
  if(paras_size!=func->paras_size){
		cerr<<"Miss some variables' range"<<endl;
		abort();
	}
  assert(paras_size==func->paras_size);
  vector<double> width;
  vector<double> input_paras;
	double integration=0;	
  
  vector<double>::iterator it0;
  vector<double>::iterator it1;
  assert(low_boundary.size()==high_boundary.size());
  
  double block=1;
	for(it0=low_boundary.begin(),it1=high_boundary.begin();it0!=low_boundary.end();it0++,it1++){
		block*=(*it1-*it0);
    width.push_back(*it1-*it0);
	}
  block/=times;
  srand((unsigned)time(0));
	for(int i=0;i<times;i++){
		input_paras.clear();
		for(it0=width.begin(),it1=low_boundary.begin();it0!=width.end();it0++,it1++){
			input_paras.push_back((double)((rand()/(double)(RAND_MAX))*(*it0)+*it1));
		}
		integration+=equ_cal(func,input_paras)*block;
	}
  cout<<"The MC Integration of "<<input<<"  "<<integration<<endl<<endl;	
	free(command_temp);
	return integration;
}
	


#endif
