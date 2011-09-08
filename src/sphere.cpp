/*
 *  sphere.cpp
 *  Vererbung
 */

#include "sphere.hpp"

sphere::sphere():
shape("standard Sphere", material()),
radius_(1),
center_(0,0,0)
{
	std::cout<<"Standardobjekt Sphere erzeugt"<<"\n"<<std::endl;
}

sphere::sphere(std::string const& name, material const& mat, double r, point3d const& p):
shape(name,mat),
radius_(r),
center_(p)
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
	return radius_*radius_*radius_*4/3*M_PI;
}


double
sphere::surface() const
{
	return radius_*radius_*4*M_PI;
}


bool
sphere::is_inside(point3d const& point) const
{
	return ((point.getX()-center_.getX())<radius_ && (point.getY()-center_.getY())<radius_ && (point.getZ()-center_.getZ())<radius_);
}


double
sphere::intersect(ray const& r) const
{
	double var0, var1;

	//Kugelgleichung: (x-m)*(x-m)=r*r
	//Geradengleichung: x=origin_+var*direction_
	//Schnittpunkt durch Gleichsetzen:

//	(origin_.getX()-center_.getX()+var*direction_.getX())*(origin_.getX()-center_.getX()+var*direction_.getX())+
//	(origin_.getY()-center_.getY()+var*direction_.getY())*(origin_.getY()-center_.getY()+var*direction_.getY())+
//	(origin_.getZ()-center_.getZ()+var*direction_.getZ())*(origin_.getZ()-center_.getZ()+var*direction_.getZ())=radius_*radius_;

	//Zusammenfassen, um var zu ermitteln:
	double a=r.getOrigin().getX()-center_.getX();
	double b=r.getOrigin().getY()-center_.getY();
	double c=r.getOrigin().getZ()-center_.getZ();

	//Nach Umstellung folgt:
	double sum=radius_*radius_-a*a-b*b-c*c; //und:
	double var2=a*r.getDir().getX()+b*r.getDir().getY()+c*r.getDir().getZ();
	double var3=r.getDir().getX()*r.getDir().getX()+r.getDir().getY()*r.getDir().getY()+r.getDir().getZ()*r.getDir().getZ();

	//Mitternachtsformel: var*var*var3+var*var2-sum=0 -------->
	var0=sqrt(var2*var2-4*sum*var3)-var2/(2*var3);
	var1=-(sqrt(var2*var2-4*sum*var3))-var2/(2*var3);

	//var in Geradengleichung einsetzen:
	if(var3!=0){
		double t1x=r.getOrigin().getX()+var0*r.getDir().getX();
		double t1y=r.getOrigin().getY()+var0*r.getDir().getY();
		double t1z=r.getOrigin().getZ()+var0*r.getDir().getZ();
		point3d schnitt1 (t1x,t1y,t1z);

		double t2x=r.getOrigin().getX()+var1*r.getDir().getX();
		double t2y=r.getOrigin().getY()+var1*r.getDir().getY();
		double t2z=r.getOrigin().getZ()+var1*r.getDir().getZ();
		point3d schnitt2 (t2x,t2y,t2z);
		// diese Punkte sollten immer positiv sein, sonst ist ein schwarzer Punkt zu sehen.

	//Abstand zwischen Strahlursprung und den Schnittpunkten berechnen:
		shape::distance(r.getOrigin(), schnitt1, schnitt2);
	}
	else
	{
		std::cout << "var3 = 0 und somit kein Schnittpkt."<<std::endl;
	}
}


point3d
sphere::make_normal(point3d const& p) const
{
    double a=(p.getX()-center_.getX())/radius_;
	double b=(p.getY()-center_.getY())/radius_;
	double c=(p.getZ()-center_.getZ())/radius_;
	point3d norm(a,b,c);
	return norm;
}


void
sphere::print_on(std::ostream& str) const
{
    str<<"*SPHERE*"<<std::endl;
	shape::print_on(str);
	str<<"SPHERE"<<"\n"<<"   Radius: "<<radius_<<"\n"<<"   Mittelpunkt: "<<center_<<"   Fläche: "<<surface()<<" FE"<<"\n"<<"   Volumen: "<<volume()<<" VE"<<std::endl;
}

