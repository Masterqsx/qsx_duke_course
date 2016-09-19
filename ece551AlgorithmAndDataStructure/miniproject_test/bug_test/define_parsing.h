#ifndef _define_parsing_
#define _define_parsing_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<map>
#include<assert.h>
#include<string>
#include<stack>
#include"check_list.h"
using namespace std;
void define_parsing(string input,map<string,Nodes*> &function_map){
	char *command_temp=strdup(input.c_str());
  strtok(command_temp," ()");//delete the command name
 
	if(input.find("=")==string::npos){
		cerr<<"There is no = in input"<<endl;
		abort();
	} 
	char *command_element=strtok(NULL," ()");
  assert(command_element!=NULL);
  string equ_name(command_element);//get the equation name
  if(is_symbol(command_element)||is_num(command_element)){
		perror("Wrong equation name, already defined");
		abort();
	}
  assert((is_exist_function(command_element,function_map))==NULL);
	
	int input_size=0;//the parameter number
  vector<pair<string,Nodes*> > paras;
	
	while((command_element=strtok(NULL," ()"))!=NULL){
 		if(strcmp(command_element,"=")==0)
    	break;
		else{
  		if(is_symbol(command_element)||is_num(command_element)){
				perror("Wrong variable name");
				abort();
			}
      string v_name(command_element);
			vector<pair<string,Nodes*> >::iterator it;
			for(it=paras.begin();it!=paras.end();it++){
				if(it->first==v_name){
					perror("Variable name overlap");
					abort();
				}
			}
			paras.push_back(pair<string,Nodes*>(v_name,new variable(v_name)));
			input_size++;
		}
	} 
	assert(strcmp(command_element,"=")==0);
	Nodes* equ=new equation(equ_name,input_size);
  equ->paras=paras;
	function_map.insert(pair<string,Nodes*>(equ_name,equ));
  
  stack<char *> equ_Nodes;
	while((command_element=strtok(NULL," ()"))!=NULL){
		equ_Nodes.push(command_element);
	}
	
	while(equ_Nodes.size()>0){
		Nodes* new_Nodes=check_type(equ,equ_Nodes.top(),function_map);
		equ->add(new_Nodes);
		equ_Nodes.pop();
	}
	cout<<input<<endl;
	free(command_temp);
}
	
#endif	
