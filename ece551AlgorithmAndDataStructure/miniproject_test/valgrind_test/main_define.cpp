#include<iostream>
#include<cstdlib>
#include<cstdio>
#include"define_parsing.h"
#include<map>
#include"eval_parsing.h"
#include<string>
#include"equation_tree.h"
#include<vector>
#include<fstream>
#include"parsing.h"
int main(int args, char** argv){
	map<string,Nodes*> function_map;
	vector<string> command_list;
	command_list.push_back("define");
	command_list.push_back("evaluate");
  command_list.push_back("numint");
	command_list.push_back("mcint");
	command_list.push_back("max");
  command_list.push_back("min");
	string shell_input;

  if(args==1){
	  while(!getline(cin,shell_input).eof()){
		 parsing(shell_input,command_list,function_map);
	  }
	}
  else if(args==2){
		ifstream input;
		input.open(argv[1]);
		if(input.fail()){
			perror("Could not open file");
			return EXIT_FAILURE;
		}
		while(!getline(input,shell_input).eof()){
			parsing(shell_input,command_list,function_map);
		}
		input.close();
	}
	else{
		cerr<<"Could only enter less than one argument"<<endl;
		return EXIT_FAILURE;
	}
	map<string,Nodes*>::iterator it;
	for(it=function_map.begin();it!=function_map.end();it++){
		delete it->second;
	}
	return EXIT_SUCCESS;
}
