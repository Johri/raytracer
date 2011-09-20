#include <cmath>
#include "triangle.hpp"


triangle::triangle()
:shape("standard triangle", material()), first_(0,0,0), second_(1,0,0), third_(1,1,0)
{
	std::cout<<"Standardobjekt Triangle erzeugt"<<"\n"<<std::endl;
}


triangle::triangle(std::string const& name, material const& mat, point3d const& first, point3d const& second,point3d const& third)
:shape(name, mat), first_(first), second_(second), third_(third)
{
	std::cout<<"Triangle erzeugt"<<"\n"<<std::endl;
}

triangle::~triangle()
{
	std::cout<<"Triangle gelöscht"<<"\n"<<std::endl;
}

point3d
const& triangle::getFirst() const
{
	return first_;
}

point3d
const& triangle::getSecond() const
{
	return second_;
}

point3d
const& triangle::getThird() const
{
	return third_;
}


double
triangle::intersect(ray const& r) const
{
    double d;

	point3d a= second_-first_;
	point3d b= third_-first_;
	point3d c= r.getOrigin()-first_;

	double s;
	double t;
	double l;
	double bruch;

	point3d richtungsvektor=r.getDir();
	point3d dir=normalize(richtungsvektor);

	/*std::cout<<"richtungsvektor"<<r.getDir().getX()<<std::endl;
	std::cout<<"richtungsvektor"<<r.getDir().getY()<<std::endl;
	std::cout<<"richtungsvektor"<<r.getDir().getZ()<<std::endl;

	std::cout<<"normalisierter richtungsvektor"<<dir.getX()<<std::endl;
	std::cout<<"normalisierter richtungsvektor"<<dir.getY()<<std::endl;
	std::cout<<"normalisierter richtungsvektor"<<dir.getZ()<<std::endl;
    */

	point3d cross1=crossproduct(c, a);
	point3d cross2=crossproduct(dir, b);

	double scale=scaleproduct(cross2, a);

	bruch=1/scale;

	//s=bruch*(scaleproduct(crossproduct(-dir, b),c));
	//t=bruch*(scaleproduct(crossproduct(c, a),-dir));
	//l=bruch*(scaleproduct(crossproduct(c,a),b));

	l=bruch*scaleproduct(cross1, b);
	s=bruch*scaleproduct(cross2, c);
	t=bruch*scaleproduct(cross1, dir);

	double st=s+t;

	/*std::cout<<"cross="<<cross2.getX()<<std::endl;
	std::cout<<"cross="<<cross2.getY()<<std::endl;
	std::cout<<"cross="<<cross2.getZ()<<std::endl;
	std::cout<<"scale="<<scale<<std::endl;
	std::cout<<"s="<<s<<std::endl;
	std::cout<<"t="<<t<<std::endl;
    */

	if (s>=0 && s<1 && t>=0 && t<1 && st>0 && st<1)
	{
	    //std::cout<<"Schnittpunkt mit Dreieck"<<std::endl;
		//std::cout<<"Schnittpunkt mit Dreieck"<<std::endl;
		//in Geradengleichung l einsetzen:
		point3d schnitt=r.getOrigin()+l*dir;
		//Entfernung Origin-Schnitt berechnen:
		d=sqrt((r.getOrigin()[0]-schnitt[0])*(r.getOrigin()[0]-schnitt[0])+(r.getOrigin()[1]-schnitt[1])*(r.getOrigin()[1]-schnitt[1])+(r.getOrigin()[2]-schnitt[2])*(r.getOrigin()[2]-schnitt[2]));
		return d;
	}
	else
	{
		//std::cout<<"Kein Schnittpunkt mit Dreieck"<<std::endl;
		return -1;
	}
}


point3d
triangle::make_normal(point3d const& p) const
{
    point3d p1= second_-first_;
	point3d p2= third_-first_;

	point3d normale=normalenvektor(p1, p2);
	return normalize(normale);
}



void triangle::print_on(std::ostream& str) const
{
    str <<"*TRIANGLE*"<<std::endl;
    shape::print_on(str);
    str <<"TRIANGLE"<<"\n"<<"   first: "<< first_<<"   second: "<<second_<<"   third: "<<third_<<std::flush;

}
