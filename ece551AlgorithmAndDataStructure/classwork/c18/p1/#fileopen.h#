#include<dirent.h>
#include<fstream>
#include<sys/stat.h>
#include<cstring>
#include<functional>
#include<map>
#include<cstdlib>
#include"hash_cal.h"
using namespace std;
int myopen_helper(char* input_dirname, map<long,string>& file_hash){
	DIR *dp;
	struct dirent *dirp;
	char* next_dirname=NULL;
	string addressing;
	if((dp=opendir(input_dirname))==NULL){
		cerr<<"Should input file or dir"<<endl;
		return EXIT_FAILURE;
	}
	while((dirp=readdir(dp))!=NULL){
		if(strncmp(dirp->d_name,".",1)==0)//dir has .. and . two different special file would not be used
			continue;
		else if(dirp->d_type==DT_DIR){ //check whether is dir
			free(next_dirname);
			next_dirname=strdup(input_dirname);
			next_dirname=(char*)realloc(next_dirname,strlen(next_dirname)+strlen(dirp->d_name)+2);
			strcat(next_dirname,"/");
			strcat(next_dirname,dirp->d_name);
			myopen_helper(next_dirname,file_hash);
		}
		else if(dirp->d_type==DT_REG){ //check whether is regular file
			addressing.clear();
			addressing+=input_dirname;addressing+='/';addressing+=dirp->d_name;
			hash_calculator(addressing,file_hash);
		}
		else{
		//	cout<<"unknown file"<<dirp->d_name<<endl;
		}
	}
	free(next_dirname);
	next_dirname=NULL;
	closedir(dp);
	return EXIT_SUCCESS;
}

int myopen(char* dirname,map<long,string>& file_hash){
	if(access(dirname,F_OK)==-1){  //check the input file exist
		perror("Could not open file");
		return EXIT_FAILURE;
	}
	struct stat info;
	stat(dirname,&info);
	if(S_ISDIR(info.st_mode))
		return myopen_helper(dirname,file_hash);
	else if(S_ISREG(info.st_mode)){
		string addressing(dirname);
		hash_calculator(addressing,file_hash);
		return EXIT_SUCCESS;
	}
	else
		return EXIT_SUCCESS;
}

