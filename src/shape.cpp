/*
 *  shape.cpp
 *  Vererbung
 */

#include "shape.hpp"

shape::shape()
:name_("Standard Shape"), material_(material())
{
	//std::cout<<"Standardobjekt Shape erzeugt"<<"\n"<<std::endl;
}


shape::shape(std::string const& name, material const& mat)
:name_(name), material_(mat)
{
	//std::cout<<"Shape erzeugt"<<"\n"<<std::endl;
}


shape::~shape()
{
	//std::cout<<"Shape gelöscht"<<"\n"<<std::endl;
}


std::string const&
shape::get_name() const
{
    return name_;
}


material const&
shape::get_material() const
{
    return material_;
}


double
shape::distance (math3d::point3d origin, math3d::point3d a, math3d::point3d b) const
{
	double t;

	double d1=sqrt((origin[0]-a[0])*(origin[0]-a[0])+(origin[1]-a[1])*(origin[1]-a[1])+(origin[2]-a[2])*(origin[2]-a[2]));
	double d2=sqrt((origin[0]-b[0])*(origin[0]-b[0])+(origin[1]-b[1])*(origin[1]-b[1])+(origin[2]-b[2])*(origin[2]-b[2]));

	if (d1==d2 || d1<d2)
	{ //Berührung -> eine Lsg. oder t1 mit kleinerem Abstand zum Strahlursprung
		return t=d1;
	}
	 else if (d1>d2)
	{
		return t=d2;
	}
}


void
shape::print_on(std::ostream& str) const
{
	str <<"SHAPE"<<"\n"<<"   Name: "<< name_<<std::endl;
	str << material_ <<std::flush;
}


std::ostream& operator <<(std::ostream& str, shape const& s)
{
	s.print_on(str);
	return str;
}

//std::cout<<"Meine Box"<<box.volumen()<<endl;
