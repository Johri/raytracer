/*
 *  point3d.cpp
 *  Vererbung
 */

#include "point3d.hpp"
#include <cmath>
#include <iostream>
#include <ostream>

using namespace std;


point3d::point3d():
x_(0),
y_(0),
z_(0)
{}

point3d::point3d(double x, double y, double z):
x_(x),
y_(y),
z_(z)
{}

point3d::point3d(point3d const& rhs):
x_(rhs.x_),
y_(rhs.y_),
z_(rhs.z_)
{}

point3d::~point3d(){

}

double point3d::getX() const{
	return x_;
}

double point3d::getY()const{
	return y_;
}

double point3d::getZ()const{
	return z_;
}

bool operator==(point3d const& lhs, point3d const& rhs) {
	return (lhs.getX()==rhs.getX() && lhs.getY()==rhs.getY() && lhs.getZ()==rhs.getZ());
}

double& point3d::operator [](int wert){
	if (wert==0) {
		return x_;
	}else if (wert==1) {
		return y_;
	}else if (wert==2) {
		return z_;
	}
}

point3d operator *(point3d const& p1, point3d const& p2){

	double x=p1.getX()*p2.getX();
	double y=p1.getY()*p2.getY();
	double z=p1.getZ()*p2.getZ();
	point3d p(x,y,z);
	return p;
}
point3d operator -(point3d const& p1, point3d const& p2){

	double x=p2.getX()-p1.getX();
	double y=p2.getY()-p1.getY();
	double z=p2.getZ()-p1.getZ();
	point3d p(x,y,z);
	return p;
}

void point3d::print_on(std::ostream& str) const{
	str <<"("<< x_ <<", "<< y_ <<", "<< z_ <<")"<< std::endl;
}

std::ostream& operator<<(std::ostream& str, point3d const& p){
	p.print_on(str);
	return str;
}
