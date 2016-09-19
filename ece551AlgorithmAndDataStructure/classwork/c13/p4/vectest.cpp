#include <iostream>
#include <vector>
using namespace std;
int main()
{
		  vector< vector<int> > intvv;
      vector< vector<int> > intVV;
      vector<int> intV;
      int i,j,k;
      for(i=0;i<10;++i){
        intV.clear();
        for(j=0;j<10;++j)
        	intV.push_back(i*10+j);
        intVV.push_back(intV);
      }
/*			cout<<intVV.at(0).size()<<endl;
			intVV[0].clear();
			cout<<intVV.at(0).size()<<endl;
*/			cout<<intvv.size()<<endl;
        intvv.resize(10);
				cout<<intvv.size()<<endl;
				for(k=0;k<10;k++){
					intvv[k]=intVV[k];
				}
				cout<<intvv.size()<<endl;
				for(i=0;i<10;++i){
        	for(j=0;j<10;++j)
        		cout<<intVV[i][j]<<' ';
        		cout<<endl;
					for(k=0;k<10;k++)
						cout<<intvv[i][k]<<"* ";
						cout<<endl;
      }
      return 0;
}
