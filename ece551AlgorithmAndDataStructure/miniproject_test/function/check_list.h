#ifndef _check_list_
#define _check_list_
#include"equation_tree.h"
#include<cstdlib>
#include<cstdio>
#include<string.h>
Nodes* is_exist_function(char *equ_name,map<string,Nodes*>&function_map){
	map<string,Nodes*>::iterator it;
  string equ(equ_name);
	if((it=function_map.find(equ))!=function_map.end()){
		return it->second;
	}
	else
		return NULL;
}

bool is_digit(char input){
	if( ((input-'0')>=0)&&((input-'0')<=9) )
		return true;
	else 
		return false;
}

bool is_num(char *input){
	//int flag=0;
	int dot_num=0;
	if( is_digit(*input)||(*input=='+')||(*input=='-')||(*input=='.') ){
		if(*input=='.')
			dot_num++;
    input++;
		while(*input!='\0'){
			if(is_digit(*input)){
				input++;
				continue;
			}
			else if(*input=='.'){
				if(dot_num>=1)
         return false;
				dot_num++;
				input++;
				continue;
			}
			else
				return false;
		}
		
		return true;	
	}
	else
		return false;
}

bool is_symbol(char *input){
	if((strcmp(input,"+")==0)||(strcmp(input,"-")==0)||(strcmp(input,"*")==0)||(strcmp(input,"/")==0))
		return true;
	else
		return false;
}

Nodes* check_type(char *input,map<string,Nodes*> &function_map){
	Nodes* return_Nodes=is_exist_function(input,function_map);
	if(return_Nodes!=NULL){
		cout<<return_Nodes->e_name<<endl;
		return return_Nodes;
	}
	else if(is_symbol(input)){
		cout<<input<<endl;
		return_Nodes=new symbol(*input);
		return return_Nodes;
	}
	else if(is_num(input)){
		cout<<strtof(input,NULL)<<endl;
		return_Nodes=new Nodes(strtof(input,NULL));
		return return_Nodes;
	}
	else{
		string v_name(input);
		cout<<v_name<<endl;
		return_Nodes=new variable(v_name);
		return return_Nodes;
	}
}	

#endif	
