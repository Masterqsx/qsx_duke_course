#include "point.h"
class Circle
{
  public:
	
	Circle(Point p,double ra);
	void move( double dx, double dy);
	double intersectionArea(const Circle & otherCircle);
	double Test(Circle otherCircle,int n);
  private:
	Point center;
	const double radius;


};
