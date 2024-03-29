#include "light.hpp"

#include <iomanip>                // std::fixed, std::setprecision
#include <ostream>

light::light()
:name_("standard light"), location_(0,0,0), ambient_(1,1,1), diffuse_(1,1,1)
{
    //ctor
}


light::light(std::string const& name, point3d const& loc, color const& amb, color const& diff)
:name_(name), location_(loc), ambient_(amb), diffuse_(diff)
{

}

light::~light()
{
    //dtor
}



point3d const&
light::get_location() const
{
    return location_;
}


color const&
light::get_ambient() const
{
    return ambient_;
}


color const&
light::get_diffuse() const
{
    return diffuse_;
}


void
light::rotate()
{

}


void
light::print_on(std::ostream& str) const
{
	str<<"LIGHT"<<"\n"<<"   Name: "<< name_<<"\n"<<"   Location: "<<location_<<"   ambient: "<<ambient_<<"   diffuse: "<<diffuse_<<std::flush;
}


std::ostream& operator <<(std::ostream& str, light const& l)
{
	l.print_on(str);
	return str;
}
