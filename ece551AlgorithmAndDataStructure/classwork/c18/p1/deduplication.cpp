#include<iostream>
#include<functional>
#include"fileopen.h"
#include<cstring>
#include<unistd.h>
using namespace std;

int main(int args, char** argv){
	char* final_dash_check=NULL;
	char final_dash_check_value='/';
	char * dirname=NULL;
	if(args<=1){
		perror("Should input file or dir");	
		return EXIT_FAILURE;
	}
	cout<<"#!/bin/bash"<<endl;
	map<long,string> file_hash;
	for(int i=1;i<args;i++){
		final_dash_check=strrchr(argv[i],final_dash_check_value);
		if(argv[i][0]!='/'){    //check whether is relative address
			dirname=getcwd(NULL,0);
			dirname=(char*)realloc(dirname,strlen(dirname)+2+strlen(argv[i]));
			if((final_dash_check==NULL)||(final_dash_check[1]!='\0'))
				strcat(strcat(dirname,"/"),argv[i]);
			else{
				strcat(strcat(dirname,"/"),argv[i]);
				final_dash_check=strrchr(dirname,final_dash_check_value);
				*final_dash_check='\0';
			}
			if(myopen(dirname,file_hash)==EXIT_FAILURE){
				free(dirname);
//				return EXIT_FAILURE;
			}
			else
				free(dirname);
		}
		else
			if((final_dash_check==NULL)||(final_dash_check[1]!='\0')){
				if(myopen(argv[i],file_hash)==EXIT_FAILURE);
//					return EXIT_FAILURE;
			}
			else{
				dirname=strdup(argv[i]);
				final_dash_check=strrchr(dirname,final_dash_check_value);
				*final_dash_check='\0';
				if(myopen(dirname,file_hash)==EXIT_FAILURE){
					free(dirname);
//					return EXIT_FAILURE;
				}
				else
					free(dirname);
			}
	}
	return EXIT_SUCCESS;

}


