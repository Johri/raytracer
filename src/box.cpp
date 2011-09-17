/*
 *  box.cpp
 *  Vererbung
 */

#include "box.hpp"
#include "point3d.hpp"

box::box()
:shape("standardBox", material()),p1_(0,0,0),p2_(1,1,1)
{
	std::cout<<"Standardobjekt Box erzeugt"<<"\n"<<std::endl;
}
box::box(std::string const& name, material const& mat, point3d const& x, point3d const& y):
shape(name,mat), p1_(x), p2_(y)
{
    std::cout<<"Box erzeugt"<<"\n"<<std::endl;
}

box::~box()
{
	std::cout<<"Box gelöscht"<<"\n"<<std::endl;
}

point3d const&
box::getX() const
{
	return p1_;
}


point3d const&
box::getY() const
{
	return p2_;
}


bool
box::is_inside(point3d const& p) const
{
	return p.getX()<=p1_.getX() && p.getX()>=p2_.getX() && p.getY()>=p2_.getY() && p.getY()<=p1_.getY() && p.getZ()>=p2_.getZ() && p.getZ()<=p1_.getZ();
}


point3d
normalenvektor(point3d p1,point3d p2)
{
	double a=p1.getY()*p2.getZ()-p1.getZ()*p2.getY();
	double b=p1.getZ()*p2.getX()-p1.getX()*p2.getZ();
	double c=p1.getX()*p2.getY()-p1.getY()*p2.getX();
	point3d normalenvektor(a,b,c);
	return normalenvektor;
}


double
unbekannte(point3d p,point3d aufziehpunkt)
{
     //identisch zu scaleproduct
	double unbekannte=p.getX()*aufziehpunkt.getX()+p.getY()*aufziehpunkt.getY()+p.getZ()*aufziehpunkt.getZ();
	return unbekannte;
}


double min(double a, double c)
{
	if (a<c)
	{
		return a;
	}
	else
	{
		return c;
	}
}


double max(double a, double c)
{
	if (a>c)
	{
		return a;
	}
	else
	{
		return c;
	}
}


double max(double a, double b, double c)
{
	double tmp = max(a, b);

	if (tmp > c)
	{
		return tmp;
	}
	else
	{
		return c;
	}
}


double min(double a, double b, double c)
{
	if (min(a,b)<c)
	{
		return min(a,b);
	}
	else
	{
		return c;
	}
}


/*void box::rotate (double bog_z, double bog_x, double bog_y)
{
    double radius=std::sqrt(x_*x_+y_*y_);
    double phi=asin(y_/ radius);
    x_=radius*cos(phi+bog);
    y_=radius*sin(phi+bog);
}*/


double box::intersect(ray const& r) const
{
	double t;
	point3d schnitt1, schnitt2, schnitt3, schnitt4, schnitt5, schnitt6;

	point3d norm_d=normalize(r.getDir());

	//1.Ebene (vorder):
	point3d p3 ((p2_.getX()-p1_.getX()),0,0);
	point3d p4 (0, (p2_.getY()-p1_.getY()), 0);
	point3d n1 = normalenvektor(p3, p4);
	double u1 = unbekannte(n1,p1_);

	double t1,t2,t3,t4,t5,t6;

	if(scaleproduct(n1, norm_d)!=0)
	{
		double temp=(scaleproduct(n1,r.getOrigin())+u1)/scaleproduct(n1, norm_d);
		schnitt1=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt1))
		{
		    //std::cout<<"temp1"<<temp<<std::endl;
			t1=temp;
		}
		else
		{
			t1=	1.7E+308;
		}

	}
	else
	{
		t1=-1;
	}
	//std::cout<<"t1= "<< t1<<std::endl;

	//2.Ebene (rechts):
	point3d p5 (0,0,(p2_.getZ()-p1_.getZ()));
	point3d n2 = normalenvektor(p5, p4);
	double u2 = unbekannte(n2, p1_);

	if(scaleproduct(n2, norm_d)!=0)
	{
		double temp=(scaleproduct(n2,r.getOrigin())+u2)/scaleproduct(n2, norm_d);
		schnitt2=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt2))
		{
		    //std::cout<<"temp2"<<temp<<std::endl;
			t2=temp;
		}
		else
		{
			t2=	1.7E+308;
		}
	}
	else
	{
		t2=-1;
	}
	//std::cout<<"t2= "<< t2<<std::endl;


	//3.Ebene (links):
	point3d n3 = normalenvektor(-p5, -p4);
	double u3 = unbekannte(n3, p2_);

	if(scaleproduct(n3, norm_d)!=0)
	{
		double temp=(scaleproduct(n3,r.getOrigin())+u3)/scaleproduct(n3, norm_d);
		schnitt3=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt3))
		{
		    //std::cout<<"temp3"<<temp<<std::endl;
			t3=temp;
		}
		else
		{
			t3=	1.7E+308;
		}
	}
	else
	{
		t3=-1;
	}
	//std::cout<<"t3= "<< t3<<std::endl;

	//4.Ebene (oben):
	point3d n4 = normalenvektor(p3, p5);
	double u4 =unbekannte(n4, p1_);

	if(scaleproduct(n4, norm_d)!=0)
	{
		double temp=(scaleproduct(n4,r.getOrigin())+u4)/scaleproduct(n4, norm_d);
		schnitt4=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt4))
		{
		    //std::cout<<"temp4"<<temp<<std::endl;
			t4=temp;
		}
		else
		{
			t4=	1.7E+308;
		}
	}
	else
	{
		t4=-1;
	}
	//std::cout<<"t4= "<< t4<<std::endl;


	//5.Ebene (unten):
	point3d n5 =normalenvektor(-p5, -p3);
	double u5 = unbekannte(n5, p2_);

	if(scaleproduct(n5, norm_d)!=0)
	{
		double temp=(scaleproduct(n5,r.getOrigin())+u5)/scaleproduct(n5, norm_d);
		schnitt5=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt5))
		{
		    //std::cout<<"temp5"<<temp<<std::endl;
			t5=temp;
		}
		else
		{
			t5=	1.7E+308;
		}
	}
	else
	{
		t5=-1;
	}
	//std::cout<<"t5= "<< t5<<std::endl;

	//6.Ebene (hinten):
	point3d n6 =normalenvektor(-p4, -p3);
	double u6 = unbekannte(n6, p2_);

	if(scaleproduct(n6, norm_d)!=0)
	{
		double temp=(scaleproduct(n6,r.getOrigin())+u6)/scaleproduct(n6, norm_d);
		schnitt6=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt5))
		{
		    //std::cout<<"temp6"<<temp<<std::endl;
			t6=temp;
		}
		else
		{
			t6=	1.7E+308;
		}
	}
	else
	{
		t6=-1;
	}
	//std::cout<<"t6= "<< t6<<std::endl;

	double t_links_rechts_min, t_oben_unten_min, t_links_rechts_max, t_oben_unten_max, t_min, t_max, t_vorne_hinten_min, t_vorne_hinten_max;

	t_links_rechts_min = min(t2,t3);

	if (t_links_rechts_min==t2)
	{
		t_links_rechts_max=t3;
	}
	else
	{
		t_links_rechts_max=t2;
	}

	t_oben_unten_min= min(t4,t5);

	if (t_oben_unten_min==t4)
	{
		t_oben_unten_max=t5;
	}
	else
	{
		t_oben_unten_max=t4;
	}

	t_vorne_hinten_min= min(t1,t6);

	if (t_vorne_hinten_min==t1)
	{
		t_vorne_hinten_max=t6;
	}
	else
	{
		t_vorne_hinten_max=t1;
	}

	t_min=max(t_links_rechts_min,t_oben_unten_min, t_vorne_hinten_min);
	t_max=min(t_links_rechts_max, t_oben_unten_max, t_vorne_hinten_max);



	if(t_min>=t_max)
	{

		double temp=min(t_links_rechts_min, t_oben_unten_min);
		double max_=max(t_links_rechts_min, t_oben_unten_min);

		if(max_>0)
		{
			if (temp>0)
			{
				if (t_vorne_hinten_min>0)
				{
					t=min(temp,t_vorne_hinten_min);
				}
				else
				{
					t=temp;
				}
			}
			else
			if (min(t_vorne_hinten_min, max_)>0)
			{
				t=min(t_vorne_hinten_min,max_);
			}
			else
			if (max(t_vorne_hinten_min, max_)>0)
			{
				t=max(t_vorne_hinten_min, max_);
			}
			else
			{
				t=-1;
			}

		}
		else
		if (t_vorne_hinten_min>0)
		{
			t=t_vorne_hinten_min;
		}
		else
		{
			t=-1;
		}

		if (t < 0)
		{
			//std::cout << "Schnittpunkt hinter der Kamera!"<<std::endl;
		}
		else
		{
			//std::cout << "Es gibt einen Schnittpunkt mit Abstand "<<t<<std::endl;
		}

		return t;
	}
	else
	{
		//std::cout<<"Kein Schnittpunkt"<<std::endl;
		return -1;
	}

}


point3d
box::make_normal(point3d const& p) const
{

}


void
box::print_on(std::ostream& str) const
{
    str<<"*BOX*"<<std::endl;
	shape::print_on(str);
	str<<"BOX"<<"\n"<<"   Punkt 1: " << p1_<<"   Punkt 2: "<<p2_<<std::flush;
}
