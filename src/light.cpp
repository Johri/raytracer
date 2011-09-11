#include "light.hpp"



light::light()
:name_("standard light"), location_(0,0,0), ambient_(1,1,1), defuse_(1,1,1)
{
    //ctor
}


light::light(std::string const& name, point3d const& loc, color const& amb, color const& def)
:name_(name), location_(loc), ambient_(amb), defuse_(def)
{

}

light::~light()
{
    //dtor
}


void
light::rotate()
{

}


void
light::print_on(std::ostream& str) const
{
	str <<"LIGHT"<<"\n"<<"   Name: "<< name_<<"\n"<<"   Location: "<<location_<<"   ambient: "<<ambient_<<"   defuse: "<<defuse_<<std::flush;
}


std::ostream& operator <<(std::ostream& str, light const& l)
{
	l.print_on(str);
	return str;
}
