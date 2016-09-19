#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(){
	string line;
	vector<string> data;
	while(!getline(cin,line).eof()){
		data.push_back(line);
	}
	for(unsigned int i=0;i<data.size();i++){
		cout<<data[i]<<endl;
	}
	return 0;
}
