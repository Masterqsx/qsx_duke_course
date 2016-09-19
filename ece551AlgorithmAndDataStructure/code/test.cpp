#include<iostream>
using namespace std;
int a=20;
class test{
	public:
		int a;
		test(){
			test::a=0;
		}
		int get(){
			return ::a;
		}
};

int main()
{
	test s;
	cout<<s.get()<<endl;
	return 0;
}
