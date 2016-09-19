#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;

int main(int argc, char **argv){
	ifstream input;
	string line;
	vector<string> data; 
	if(argc==1){

		while(!cin.eof()){
			getline(cin,line);
			data.push_back(line);
		}
		data.pop_back();
		
		sort(data.begin(),data.end());
		for(unsigned int i=0;i<data.size();i++){
			cout<<data[i]<<endl;
		}
	}
	else{
		for(int i=1;i<argc;i++){
			input.open(argv[i]);
			if(input.fail()){
				cerr<<"can not open file\n";
				return EXIT_FAILURE;
			}	
			while(!input.eof()){
				getline(input,line);
				data.push_back(line);
			}
			data.pop_back();
		  
			sort(data.begin(),data.end());
			for(unsigned int j=0;j<data.size();j++){
				cout<<data[j]<<endl;
			}
			data.clear();
			input.close();
		}
	}
	
	return EXIT_SUCCESS;
}

