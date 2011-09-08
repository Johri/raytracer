/*
 *  cone.cpp
 *  Vererbung
 */

#include "cone.hpp"

cone::cone()
:shape("standard cone", material()), center_(0,0,0), radius_(1), higth_(1)
{
	std::cout<<"Standardobjekt Cone erzeugt"<<"\n"<<std::endl;
}


cone::cone(std::string const& name, material const& mtr, point3d const& center, double rad, double higth):
shape(name, mtr), center_(center), radius_(rad), higth_(higth)
{
    std::cout<<"Cone erzeugt"<<"\n"<<std::endl;
}


cone::~cone()
{
	std::cout<<"Standardobjekt Cone gelöscht"<<"\n"<<std::endl;
}




double
cone::get_radius() const{
	return radius_;
}


point3d const&
cone::get_center() const
{
	return center_;
}


double
cone::intersect(ray const& r) const
{
	double t;
	return t;
}


point3d
cone::make_normal(point3d const& p) const
{

}

void
cone::print_on(std::ostream& str) const
{
    str<<"*CONE*"<<std::endl;
	shape::print_on(str);
	str<<"CONE"<<"\n"<<"   Mittelpunkt: "<<center_<< "   Radius: " << radius_<<"\n"<<"   Höhe: "<<higth_<<"\n"<<std::endl;
}
