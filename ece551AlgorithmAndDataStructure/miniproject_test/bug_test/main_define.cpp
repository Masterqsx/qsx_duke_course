#include<iostream>
#include<cstdlib>
#include<cstdio>
#include"define_parsing.h"
#include<map>
#include"eval_parsing.h"
#include<string>
#include"equation_tree.h"
#include<vector>
#include"parsing.h"
int main(){
	map<string,Nodes*> function_map;
	vector<string> command_list;
	command_list.push_back("define");
	command_list.push_back("evaluate");
  command_list.push_back("numint");
	command_list.push_back("mcint");
	command_list.push_back("gradient");
	string shell_input;
	while(!getline(cin,shell_input).eof()){
		parsing(shell_input,command_list,function_map);
	}
	map<string,Nodes*>::iterator it;
	for(it=function_map.begin();it!=function_map.end();it++){
		delete it->second;
	}
	return 0;
}
