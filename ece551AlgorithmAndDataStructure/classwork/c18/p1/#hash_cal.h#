#include<iostream>
#include<string>
using namespace std;
int hash_calculator(string & input_file,map<long,string>& file_hash){
	ifstream input;
	string line;
	string file_content;
	map<long,string>::iterator it;
	input.open(input_file);
	if(input.fail()){
		perror("can not open file count hash");
		return EXIT_FAILURE;
	}
	while(!input.eof()){
		getline(input,line);
		file_content+=line;
	}
	hash<string> str_hash;
	long hash_value=str_hash(file_content);
	if((it=file_hash.find(hash_value))==file_hash.end()){
		file_hash.insert(pair<long,string>((long)str_hash(file_content),input_file));
	}
	else{
		if(it->second!=input_file){
			cout<<"#Removing "<<input_file<<" (duplicate of "<<it->second<<")."<<endl;
			cout<<"rm "<<input_file<<endl;
		}
	}
	return EXIT_SUCCESS;
}

