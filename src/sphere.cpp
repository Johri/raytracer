/*
 *  sphere.cpp
 *  Vererbung
 */

#include "sphere.hpp"

sphere::sphere():
shape("standard Sphere", material()), radius_(1), center_(0,0,0)
{
	std::cout<<"Standardobjekt Sphere erzeugt"<<"\n"<<std::endl;
}

sphere::sphere(std::string const& name, material const& mat, double r, point3d const& p):
shape(name,mat), radius_(r), center_(p)
{
	std::cout<<"Sphere erzeugt"<<"\n"<<std::endl;
}

sphere::~sphere()
{
	std::cout<<"Sphere gelöscht"<<"\n"<<std::endl;
}

double
sphere::getRadius() const
{
	return radius_;
}

point3d
const& sphere::getMiddle() const
{
	return center_;
}


double
sphere::volume() const
{
	return pow(radius_,3)*4/3*M_PI;
}


double
sphere::surface() const
{
	return pow(radius_,2)*4*M_PI;
}


bool
sphere::is_inside(point3d const& point) const
{
	return ((point.getX()-center_.getX())<radius_ && (point.getY()-center_.getY())<radius_ && (point.getZ()-center_.getZ())<radius_);
}


double sphere::intersect(ray const& r) const
{
	double dist;

	double m;
	point3d l=center_-r.getOrigin();

	point3d dir=r.getDir();
	point3d d=normalize(dir);

	//std::cout<<"Normierter Richtungsvektor"<<d<<std::endl;

	//double d_length=length(d); //Länge
	double s=scaleproduct(l, d);
	m=scaleproduct(l, l)-s*s;

	if (m<radius_*radius_)
	{
		//std::cout<<"Schnittpunkt mit der Kugel"<<std::endl;
		double q;
		q=sqrt(radius_*radius_-m);
		double p1=s-q;
		//double p2=s+q; //try

			//point3d schnitt1=r.getOrigin()+p1*d;
			//point3d schnitt2=r.getOrigin()+p2*d;
			//dist=distance(r.getOrigin(),schnitt1,schnitt2);
			dist = p1;
			return dist;

	}
	else if (m==radius_*radius_)
	{
			//std::cout<<"Schnittpunkt=Berührungspunkt"<<std::endl;
			//point3d schnitt1=r.getOrigin()+s*d;
			//dist=sqrt((r.getOrigin().getX()-schnitt1.getX())*(r.getOrigin().getX()-schnitt1.getX())+(r.getOrigin().getY()-schnitt1.getY())*(r.getOrigin().getY()-schnitt1.getY())+(r.getOrigin().getZ()-schnitt1.getZ())*(r.getOrigin().getZ()-schnitt1.getZ()));
			return dist=s;

	}
	else
	{
		//std::cout<<"Kein Schnittpunkt mit der Kugel"<<std::endl;
		return -1;
	}

}


point3d
sphere::make_normal(point3d const& p) const
{
    double a=(p.getX()-center_.getX())/radius_;
	double b=(p.getY()-center_.getY())/radius_;
	double c=(p.getZ()-center_.getZ())/radius_;
	point3d norm(a,b,c);
	return normalize(norm);
}


void
sphere::print_on(std::ostream& str) const
{
    str<<"*SPHERE*"<<std::endl;
	shape::print_on(str);
	str<<"SPHERE"<<"\n"<<"   Radius: "<<radius_<<"\n"<<"   Mittelpunkt: "<<center_<<"   Fläche: "<<surface()<<" FE"<<"\n"<<"   Volumen: "<<volume()<<" VE"<<std::endl;
}

