#include<stdio.h>
#include<stdlib.h>
#include"circle.h"
#include<math.h>
#include<time.h>



Circle::Circle(Point p,double ra):center(p),radius(ra){}

void Circle::move(double dx, double dy)
{
	center.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle)
{
	 double d=center.distanceFrom(otherCircle.center);
	 double r1=radius;
	 double r2=otherCircle.radius;
  if(r1>r2)
  {
	double temp=r1;
	r1=r2;
	r2=temp;
  }//make r1 the smaller one
  if(r1+r2<=d)
	return 0;
  else if(r2-r1>=d)
	return acos(-1.0)*pow(r1,2);
  else
  {
	double a1=acos( (pow(r1,2)+pow(d,2)-pow(r2,2))/(2.0*r1*d) );
	double a2=acos( (pow(r2,2)+pow(d,2)-pow(r1,2))/(2.0*r2*d) );
	return (a1*pow(r1,2)+a2*pow(r2,2)-r1*d*sin(a1));
  }
}

double Circle::Test(const Circle otherCircle,int n)
{
	double max_x=0,max_y=0,min_x=0,min_y=0,x_this=0,x_other,y_this,y_other;
	x_this=center.getx();
	x_other=otherCircle.center.getx();
	y_this=center.gety();
	y_other=otherCircle.center.gety();

	if((x_this+radius)>=(x_other+otherCircle.radius))
	{
		max_x=x_this+radius;
	}
	else
	{
		max_x=x_other+otherCircle.radius;
	}
	
	if((y_this+radius)>=(y_other+otherCircle.radius))
	{
		max_y=y_this+radius;
	}
	else
	{
		max_y=y_other+otherCircle.radius;
	}
	
	if((y_this-radius)<=(y_other-otherCircle.radius))
	{
		min_y=y_this-radius;
	}
	else
	{
		min_y=y_other-otherCircle.radius;
	}
	
	if((x_this-radius)<=(x_other-otherCircle.radius))
	{
		min_x=x_this-radius;
	}
	else
	{
		min_x=x_other-otherCircle.radius;
	}


	srand((int)time(0));
	double temp_x=0,temp_y=0,intersection_hit=0;
	for(int i=0;i<n;i++)
	{
		temp_x=((double)(rand()%(int)((max_x-min_x)*100)))/100+min_x;
		temp_y=((double)(rand()%(int)((max_y-min_y)*100)))/100+min_y;
		
		if( (pow(x_this-temp_x,2)+pow(y_this-temp_y,2)<=pow(radius,2))&&(pow(x_other-temp_x,2)+pow(y_other-temp_y,2)<=pow(otherCircle.radius,2))   ) 	
				intersection_hit+=1;
		
	}
	return intersection_hit/n*(max_x-min_x)*(max_y-min_y);

}



	
	
