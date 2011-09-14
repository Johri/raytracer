#include "material.hpp"

material::material()
:name_("stdmaterial"), ambient_(0.1,0.1,0.1), defuse_(1,1,1), specular_(1,1,1), reflectivity_(1)
{
	//std::cout<<"Standard Material erzeugt"<<"\n"<<std::endl;
}

material::material (std::string const& name, color const& ambient, color const& defuse, color const& specular, float reflectivity)
:name_(name), ambient_(ambient), defuse_(defuse), specular_(specular), reflectivity_(reflectivity)
{
	//std::cout<<"Material erzeugt"<<"\n"<<std::endl;
}

material::material(material const& copy)
:name_(copy.name_), ambient_(copy.ambient_), defuse_(copy.defuse_), specular_(copy.specular_), reflectivity_(copy.reflectivity_)
{
	//std::cout<<"Material gelöscht"<<"\n"<<std::endl;
}

material::~material()
{
    //dtor
}


std::string const&
material::getName() const
{
	return name_;
}


color const&
material::get_ambient() const
{
	return ambient_;
}


color const&
material::get_defuse() const
{
	return defuse_;
}


color const&
material::get_specular() const
{
	return specular_;
}


float
material::get_reflectivity() const
{
	return reflectivity_;
}

void
material::print_on(std::ostream& str) const
{
    str<<"MATERIAL"<<"\n"<<"   Name: "<<name_<<"\n"<<"   ambient: ["<<ambient_[0]<<", "<<ambient_[1]<<", "<<ambient_[2]<<"]"<<"\n"<<"   defuse: ["<<defuse_[0]<<", "<<defuse_[1]<<", "<<defuse_[2]<<"]"<<"\n"<<"   specular: ["<<specular_[0]<<", "<<specular_[1]<<", "<<specular_[2]<<"]"<<"\n"<<"   reflectivity: "<<reflectivity_<<std::endl;
}


std::ostream&
operator<<(std::ostream& str, material const& mtr)
{
    mtr.print_on(str);
    return str;
}
