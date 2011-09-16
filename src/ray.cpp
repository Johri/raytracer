/*
 *  ray.cpp
 *  Objects
 */

#include "ray.hpp"
#include "shape.hpp"

ray::ray()
:origin_(0,0,0), direction_(1,1,-1)
{

}


ray::ray(point3d const& origin, point3d const& direction)
:origin_(origin), direction_(direction)
{

}


ray::ray(ray const& copy)
:origin_(copy.origin_), direction_(copy.direction_)
{

}


ray::~ray()
{

}





point3d const&
ray::getOrigin()const
{
	return origin_;
}


point3d const&
ray::getDir()const
{
	point3d dir=direction_-origin_;
	return dir;
}


/*ray& operator=(ray const& rhs)
{

}*/

color const&
ray::getColor(double t, shape const& s, ray const& r) const
{
 color black(0,0,0);
	 if (t>=0)
	 {
		 color clr;
		 return clr;
	 }
	 else
	 {
		 return black;
	 }
}


point3d
ray::getSchnitt(double t) const
{
	point3d p=origin_+t*normalize(direction_-origin_);
	return p;
}


void
ray::print_on(std::ostream& str) const
{
	str <<"RAY"<<"\n"<<"   Origin: "<< origin_<<"   Direction: "<<direction_<<std::flush;
}


std::ostream& operator <<(std::ostream& str, ray const& r)
{
	r.print_on(str);
	return str;
}


