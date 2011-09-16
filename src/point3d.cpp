/*
 *  point3d.cpp
 *  Vererbung
 */

#include "point3d.hpp"
#include <cmath>
#include <iostream>
#include <ostream>

using namespace std;


point3d::point3d()
:x_(0), y_(0), z_(0)
{

}


point3d::point3d(double x, double y, double z)
:x_(x), y_(y), z_(z)
{

}


point3d::point3d(point3d const& rhs)
:x_(rhs.x_), y_(rhs.y_), z_(rhs.z_)
{

}


point3d::~point3d()
{

}


double
point3d::getX() const
{
	return x_;
}


double
point3d::getY() const
{
	return y_;
}


double
point3d::getZ() const
{
	return z_;
}


double
scaleproduct(point3d const& p1, point3d const& p2)
{
	double x=p1.getX()*p2.getX();
	double y=p1.getY()*p2.getY();
	double z=p1.getZ()*p2.getZ();
	double p=x+y+z;
	return p;
}

double
length(point3d const& p)
{
	double d=sqrt(p.getX()*p.getX()+p.getY()*p.getY()+p.getZ()*p.getZ());
	return d;
}


double
length_two_points(point3d const& p, point3d const& q)
{
	double d=sqrt((p.getX()-q.getX())*(p.getX()-q.getX())+(p.getY()-q.getY())*(p.getY()-q.getY())+(p.getZ()-q.getZ())*(p.getZ()-q.getZ()));
	return d;
}


point3d
normalize(point3d const& p)
{
	double d=length(p);
	double a=p.getX()/d;
	double b=p.getY()/d;
	double c=p.getZ()/d;
	point3d normal(a,b,c);
	return normal;
}


point3d
normalenvektor(point3d const& p1,point3d const& p2)
{
	double a=p1.getY()*p2.getZ()-p1.getZ()*p2.getY();
	double b=p1.getZ()*p2.getX()-p1.getX()*p2.getZ();
	double c=p1.getX()*p2.getY()-p1.getY()*p2.getX();
	point3d normalenvektor(a,b,c);
	return normalenvektor;
}


point3d
crossproduct(point3d const& p1, point3d const& p2)
{
	double a=p1.getY()*p2.getZ()-p1.getZ()*p2.getY();
	double b=p1.getZ()*p2.getX()-p1.getX()*p2.getZ();
	double c=p1.getX()*p2.getY()-p1.getY()*p2.getX();
	point3d normalenvektor(a,b,c);
	return normalenvektor;
}


void
point3d::translate (double x, double y, double z)
{
    x_+=x;
    y_+=y;
    z_+=z;
}


void
point3d::teleport (point3d const& destination)
{
    x_=destination.getX();
    y_=destination.getY();
    z_=destination.getZ();
}


bool
operator==(point3d const& lhs, point3d const& rhs)
{
	return (lhs.getX()==rhs.getX() && lhs.getY()==rhs.getY() && lhs.getZ()==rhs.getZ());
}


double&
point3d::operator [](int wert)
{
	if (wert==0) {
		return x_;
	}else if (wert==1) {
		return y_;
	}else if (wert==2) {
		return z_;
	}
}


point3d
operator *(point3d const& p1, point3d const& p2)
{

	double x=p1.getX()*p2.getX();
	double y=p1.getY()*p2.getY();
	double z=p1.getZ()*p2.getZ();
	point3d p(x,y,z);
	return p;
}


point3d
operator *(double d, point3d const& p)
{
	double x=d*p.getX();
	double y=d*p.getY();
	double z=d*p.getZ();
	point3d point(x,y,z);
	return point;
}


point3d
operator -(point3d const& p1, point3d const& p2)
{

	double x=p1.getX()-p2.getX();
	double y=p1.getY()-p2.getY();
	double z=p1.getZ()-p2.getZ();
	point3d p(x,y,z);
	return p;
}


point3d
operator -(point3d const& p)
{
	double x=p.getX()*-1;
	double y=p.getY()*-1;
	double z=p.getZ()*-1;
	point3d point(x,y,z);
	return point;
}


point3d
operator +(point3d const& p1, point3d const& p2)
{
	double x=p1.getX()+p2.getX();
	double y=p1.getY()+p2.getY();
	double z=p1.getZ()+p2.getZ();
	point3d p(x,y,z);
	return p;
}


void
point3d::print_on(std::ostream& str) const
{
	str <<"("<< x_ <<", "<< y_ <<", "<< z_ <<")"<< std::endl;
}


std::ostream& operator<<(std::ostream& str, point3d const& p)
{
	p.print_on(str);
	return str;
}
