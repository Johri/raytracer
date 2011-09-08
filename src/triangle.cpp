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
	std::cout<<"Objekt Triangle gelöscht"<<"\n"<<std::endl;
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

bool
triangle::is_inside(point3d const& point) const
{
	// c=s*a+t*b --->nach s und t ausflösen
	point3d a= second_-first_;
	point3d b= third_-first_;
	point3d c= point-first_;

	double t=(c.getY()-(a.getY()/a.getX())*c.getX())/(b.getY()-(a.getY()/a.getX())*b.getX());
	double s= (c.getX()-t*b.getX())/a.getX();

	double st=s+t;

	if (0<s<1 && 0<t<1 && 0<st<1)
        {
            return true;
        }

	else
        {
            return false;
        }
}


double
triangle::intersect(ray const& r) const
{
	double t;
	point3d second = second_-first_;
	point3d third = third_-first_;

	double a=second.getY()*third.getZ()-second.getZ()*third.getY();
	double b=second.getZ()*third.getX()-second.getX()*third.getZ();
	double c=second.getX()*third.getY()-second.getY()*third.getX();

	point3d normalenvektor(a,b,c);

	double d = a*first_.getX()+b*first_.getY()+c*first_.getZ();

	if(a*third_.getX()+b*third_.getY()+c*third_.getZ() !=0)
        {
            double unbekannte = d -(a*second_.getX()+b*second_.getY()+c*second_.getZ()/a*third_.getX()+b*third_.getY()+c*third_.getZ());
            point3d schnitt1 ((r.getOrigin().getX()+unbekannte*r.getDir().getX()), (r.getOrigin().getY()+unbekannte*r.getDir().getY()), (r.getOrigin().getZ()+unbekannte*r.getDir().getZ()));
            if (is_inside(schnitt1))
            {
                t=sqrt((r.getOrigin().getX()-schnitt1.getX())*(r.getOrigin().getX()-schnitt1.getX())+(r.getOrigin().getY()-schnitt1.getY())*(r.getOrigin().getY()-schnitt1.getY())+(r.getOrigin().getZ()-schnitt1.getZ())*(r.getOrigin().getZ()-schnitt1.getZ()));
                return t;
            }
        }

    else
        {
        std::cout<<"Kein Schnittpunkt"<<std::endl;
        return -1;
        }
}


point3d
triangle::make_normal(point3d const& p) const
{

}



void triangle::print_on(std::ostream& str) const
{
    str <<"*TRIANGLE*"<<std::endl;
    shape::print_on(str);
    str <<"TRIANGLE"<<"\n"<<"   first: "<< first_<<"   second: "<<second_<<"   third: "<<third_<<std::endl;

}
