/*
 *  tube.cpp
 *  Objects
 */

#include "tube.hpp"


tube::tube()
:shape("standard tube", material()), bottom_center_(0,0,0), top_center_(0,0,0), radius_(0)
{
	std::cout<<"Standardobjekt Tube erzeugt"<<"\n"<<std::endl;
}


tube::tube(std::string const& name, material const& mtr, point3d bcenter, point3d tcenter, double rad):
shape(name, mtr), bottom_center_(bcenter), top_center_(tcenter), radius_(rad)
{
	std::cout<<"Tube erzeugt"<<"\n"<<std::endl;
}


tube::tube(tube const& copy):
shape(copy.shape::get_name(), copy.shape::get_material()), bottom_center_(copy.bottom_center_), top_center_(copy.top_center_), radius_(copy.radius_)
{
	std::cout<<"Tube kopiert"<<"\n"<<std::endl;
}

tube::~tube()
{
	std::cout<<"Tube gelöscht"<<"\n"<<std::endl;
}



point3d const&
tube::get_bottom_center() const
{
	return bottom_center_;
}


point3d const&
tube::get_top_center() const
{
	return top_center_;
}



double
tube::get_radius() const{
	return radius_;
}


point3d
tube::make_normal(point3d const& schnittpunkt) const
{
 //ändern (da nur von sphere kopiert)
	double a=(schnittpunkt.getX()-bottom_center_.getX())/radius_;
	double b=(schnittpunkt.getY()-bottom_center_.getY())/radius_;
	double c=(schnittpunkt.getZ()-bottom_center_.getZ())/radius_;
	point3d norm(a,b,c);
	return norm;
}


point3d tube::teleport(point3d const& p)
{
	return bottom_center_=p;
}


double
tube::intersect(ray const& r) const
{

	double t,t1,t2;
	point3d schnitt1, schnitt2;
	point3d dir=normalize(r.getDir());
	point3d q= normalize(top_center_-bottom_center_); //Richtungsvektor der Zylindermittelachse normalisiert
	point3d a= r.getOrigin()-bottom_center_;
	point3d e= dir-(scaleproduct(dir, q)/scaleproduct(q, q))*q;
	point3d f= a-(scaleproduct(a, q)/scaleproduct(q, q))*q;

	//übersichtlich zusammenfassen:
	double one, two, three;
	one=scaleproduct(e, e);
	two=scaleproduct(e, f)*2;
	three=scaleproduct(f, f)-radius_*radius_;
	double nenner=2*one;

	if (nenner==0 || two*two<(4*one*three))
	{
		std::cout<<"Kein Schnittpunkt mit Zylinder"<<std::endl;
		t=-1;
	}
	else
	{
        t1=-two+sqrt(two*two-(4*one*three))/nenner;
		schnitt1=r.getOrigin()+t1*dir;
        t2=-two-sqrt(two*two-(4*one*three))/nenner;
		schnitt2=r.getOrigin()+t2*dir;


        if(t1>t2)
        {
            if (schnitt2.getY()<bottom_center_.getY() || schnitt2.getY()>top_center_.getY())
            {
                std::cout<<"Gerade liegt über dem Zylinder"<<std::endl;
                t=-1;
            }
            else
            {
                std::cout<<"Schnittpunkt mit Zylinder"<<std::endl;
                t=t2;
            }
        }
        else
        {
            if (schnitt1.getY()<bottom_center_.getY() || schnitt1.getY()>top_center_.getY())
            {
                std::cout<<"Gerade liegt über dem Zylinder"<<std::endl;
                t=-1;
            }
            else
            {
                std::cout<<"Schnittpunkt mit Zylinder"<<std::endl;
                t=t1;
            }
        }

        /*std::cout << "Richtungsvektor von Tube: "<<q<<std::endl;
        std::cout << "a: "<<a<<std::endl;
        std::cout << "e: "<<e<<std::endl;
        std::cout << "f: "<<f<<std::endl;
        std::cout << "one: "<<one<<std::endl;
        std::cout << "two: "<<two<<std::endl;
        std::cout << "three: "<<three<<std::endl;
        std::cout << "Nenner: "<<2*one<<std::endl;
        std::cout << "Skalar von q: "<<scaleproduct(q, q)<<std::endl;
        std::cout << "t1:"<<t1<<std::endl;
        std::cout << "t2:"<<t2<<std::endl;
        */
	}
	return t;
}


void
tube::print_on(std::ostream& str) const
{
    str<<"*TUBE*"<<std::endl;
	shape::print_on(str);
	str<<"TUBE"<<"\n"<<"   unterer Mittelpunkt: "<<bottom_center_<<"   oberer Mittelpunkt: "<<top_center_<< "   Radius: " << radius_<<std::endl;
}
