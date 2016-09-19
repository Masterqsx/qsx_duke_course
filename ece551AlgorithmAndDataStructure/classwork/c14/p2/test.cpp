#include<iostream>

class base{
	protected:
		int x1;int x2;
	public:
		base(){}
		base(int a):x1(a){}
		base(base *a,base *b):x1(a->x),x2(b->{}
};

class derive: public base{
	public:
		derive(base *a, base *b):base(a),base(b){}
		void print(){
			cout<<x1<<x2<<endl;
		}
};

int main(){
	base a(2);
	base b(3);
	derive(&a,&b);
	derive.print();
	return 0;
}
