#include "circle.hpp"

#include "point3d.hpp"
#include "shape.hpp"

circle::circle()
:shape("standard circle", material()), center_(0,0,0), p1_(1,1,0), p2_(1,0,0), radius_(get_radius())
{
    //ctor
}

circle::circle(std::string const& name, material const& mat, point3d const& center, point3d const& p1, point3d const& p2)
:shape(name, mat), center_(center), p1_(p1), p2_(p2), radius_(get_radius())
{
}

circle::~circle()
{
    //dtor
}



point3d const&
circle::get_center() const
{
	return center_;
}

double
circle::get_radius() const
{
	double radius=length_two_points(p1_, center_);
	return radius;
}

void
circle::teleport(point3d const& p)
{
	point3d temp=center_;
	center_=p;
	p1_=p1_-temp+center_;
	p2_=p2_-temp+center_;
}

bool
circle::is_inside(point3d const& point) const
{
	double abstand=length_two_points(point, center_);
	double radius=length_two_points(p1_, center_);
	if (abstand<=radius)
	{
		return true;
	}
	else
	{
		return false;
	}

}

double
circle::intersect(ray const& r) const
{
	double t;
	point3d v1, v2;
	v1=normalize(p1_-center_);
	v2=normalize(p2_-center_);
	point3d n=normalenvektor(v1, v2);
	double s=scaleproduct(n, center_);
	point3d dir=normalize(r.getDir());
	if (scaleproduct(n, dir)!=0)
	{
		double temp=(scaleproduct(n, r.getOrigin())+s)/scaleproduct(n, dir);
		point3d schnitt=r.getOrigin()+temp*dir;
		//std::cout<<"schnitt: "<<schnitt<<std::endl;
        if (is_inside(schnitt))
		{
		    //std::cout<<"Schnittpunkt mit dem Kreis"<<std::endl;
			return t=temp;
		}
		else
		{
		    //std::cout<<"Schnittpunkt mit Ebene aber nicht mit Kreis"<<std::endl;
			return t=-1;
		}

	}
	else
	{
	    //std::cout<<"Kein Schnittpunkt mit Kreisebene"<<std::endl;
		return t=-1;
	}
}

point3d
circle::make_normal(point3d const& p) const
{
    point3d v1=p1_-center_;
	point3d v2=p2_-center_;
	point3d normale=normalenvektor(v1, v2);
	return normalize(normale);
}


void
circle::print_on(std::ostream& str) const
{
    str<<"*CIRCLE*"<<std::endl;
	shape::print_on(str);
	str<<"TUBE"<<"\n"<<"   Mittelpunkt: "<<center_<<"   Rand: "<<p1_<<"   Ausrichtung: "<<p2_<< "   Radius: " << radius_<<std::endl;
}
