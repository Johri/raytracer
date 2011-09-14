/*
 *  tube.cpp
 *  Objects
 */

#include "tube.hpp"


tube::tube()
:shape("standard tube", material()), center_(0,0,0), radius_(0), higth_(1)
{
	std::cout<<"Standardobjekt Tube erzeugt"<<"\n"<<std::endl;
}


tube::tube(std::string const& name, material const& mtr, point3d center, double rad, double higth):
shape(name, mtr), center_(center), radius_(rad), higth_(higth)
{
	std::cout<<"Tube erzeugt"<<"\n"<<std::endl;
}


tube::tube(tube const& copy):
shape(copy.shape::get_name(), copy.shape::get_material()), center_(copy.center_), radius_(copy.radius_), higth_(copy.higth_)
{
	std::cout<<"Tube kopiert"<<"\n"<<std::endl;
}

tube::~tube()
{
	std::cout<<"Tube gelöscht"<<"\n"<<std::endl;
}



point3d const&
tube::get_center() const
{
	return center_;
}



double
tube::get_radius() const{
	return radius_;
}


point3d
tube::make_normal(point3d const& p) const
{

}


double
tube::intersect(ray const& r) const
{
	double t;
	return t;
}


void
tube::print_on(std::ostream& str) const
{
    str<<"*TUBE*"<<std::endl;
	shape::print_on(str);
	str<<"TUBE"<<"\n"<<"   Mittelpunkt: "<<center_<< "   Radius: " << radius_<<"\n"<<"   Höhe: "<<higth_<<std::endl;
}
