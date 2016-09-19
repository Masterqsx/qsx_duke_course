#ifndef _parsing_
#define _parsing_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<map>
#include<assert.h>
#include<string>
#include"define_parsing.h"
#include"eval_parsing.h"
#include"numint_parsing.h"
#include"mcint_parsing.h"
#include"gradient_parsing.h"

void parsing(string input, vector<string> &command_list, map<string,Nodes*> &function_map){
	char *command_temp=strdup(input.c_str());
	string command_name(strtok(command_temp," ()"));
  for(unsigned int i=0;i<command_list.size();i++){
		if(command_list[i]==command_name){
			delete command_temp;
      switch(i){
				case 0:
					define_parsing(input,function_map);
					break;
				case 1:
					eval_parsing(input,function_map);
					break;
				case 2:
					numint_parsing(input,function_map);
					break;
				case 3:
					mcint_parsing(input,function_map);
          break;
        case 4:
					gradient_parsing(input,function_map);
          break;
			}
			return;
		}
	}
	cerr<<"Unknown command"<<endl;
	abort();
}
#endif
