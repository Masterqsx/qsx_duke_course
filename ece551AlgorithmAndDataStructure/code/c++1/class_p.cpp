#include<iostream>
using namespace std;

class Shape
{
	public:
		float x_r;
		float y;
        Shape(float _x_r, float _y)
	{
		x_r=_x_r;
		y=_y;
	}
	virtual float area() =0;
};

class Rect :public Shape
{
	public:
	Rect(float x,float y):Shape(x,y)
	{

	}
	float area()
	{
		return x_r*y;
	}
};


class Cir :public Shape
{
	public:
	Cir(float x,float y):Shape(x,y)
	{
		
	}
	float area()
	{
		return 3.14*x_r*x_r/4;
	}
};

class Trian :public Shape
{
  public:
	Trian(float x,float y):Shape(x,y)
	{
	}
	float area()
	{
		return 0.5*x_r*y;
	}
};

int main()
{
	Rect oRect(1,1);
	Cir oCir(1,1);
	Trian oTrian(1,1);
//	cout<<oRect.area()<<endl;
	cout<<oCir.area()<<endl;
	cout<<oTrian.area()<<endl;
	return 0;
}
