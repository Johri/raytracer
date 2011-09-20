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
	return p[0]<=p1_[0] && p[0]>=p2_[0] && p[1]>=p2_[1] && p[1]<=p1_[1] && p[2]>=p2_[2] && p[2]<=p1_[2];
}


/*point3d
normalenvektor(point3d p1,point3d p2)
{
	double a=p1[1]*p2[2]-p1[2]*p2[1];
	double b=p1[2]*p2[0]-p1[0]*p2[2];
	double c=p1[0]*p2[1]-p1[1]*p2[0];
	point3d normalenvektor(a,b,c);
	return normalenvektor;
}*/


double
unbekannte(point3d p,point3d aufziehpunkt)
{
     //identisch zu scaleproduct
	double unbekannte=p[0]*aufziehpunkt[0]+p[1]*aufziehpunkt[1]+p[2]*aufziehpunkt[2];
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
	point3d p3 ((p2_[0]-p1_[0]),0,0);
	point3d p4 (0, (p2_[2]-p1_[2]), 0);
	point3d n1 = normalenvektor(p3, p4);
	double u1 = unbekannte(n1,p1_);

	double t1,t2,t3,t4,t5,t6;

	//std::cout<<"scale= "<<scaleproduct(n1, r.getOrigin())<<std::endl;
	if(scaleproduct(n1, norm_d)!=0){
		double temp=(scaleproduct(n1,r.getOrigin())+u1)/scaleproduct(n1, norm_d);
		schnitt1=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt1)) {
			t1=temp;
		}else {
			t1=	1.7E+308;
		}

	}else {
		t1=-1;
	}
	//std::cout<<"t1= "<< t1<<std::endl;

	//2.Ebene (rechts):
	point3d p5 (0,0,(p2_[2]-p1_[2]));
	point3d n2 = normalenvektor(p5, p4);
	double u2 = unbekannte(n2, p1_);

	if(scaleproduct(n2, norm_d)!=0){
		double temp=(scaleproduct(n2,r.getOrigin())+u2)/scaleproduct(n2, norm_d);
		schnitt2=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt2)) {
			t2=temp;
		}else {
			t2=	1.7E+308;
		}
	}else {
		t2=-1;
	}
	//std::cout<<"t2= "<< t2<<std::endl;


	//3.Ebene (links):
	point3d n3 = normalenvektor(-p5, -p4);
	double u3 = unbekannte(n3, p2_);

	if(scaleproduct(n3, norm_d)!=0){
		double temp=(scaleproduct(n3,r.getOrigin())+u3)/scaleproduct(n3, norm_d);
		schnitt3=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt3)) {
			t3=temp;
		}else {
			t3=	1.7E+308;
		}
	}else {
		t3=-1;
	}
	//std::cout<<"t3= "<< t3<<std::endl;

	//4.Ebene (oben):
	point3d n4 = normalenvektor(p3, p5);
	double u4 =unbekannte(n4, p1_);

	if(scaleproduct(n4, norm_d)!=0){
		double temp=(scaleproduct(n4,r.getOrigin())+u4)/scaleproduct(n4, norm_d);
		schnitt4=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt4)) {
			t4=temp;
		}else {
			t4=	1.7E+308;
		}
	}else {
		t4=-1;
	}
	//std::cout<<"t4= "<< t4<<std::endl;


	//5.Ebene (unten):
	point3d n5 =normalenvektor(-p5, -p3);
	double u5 = unbekannte(n5, p2_);

	if(scaleproduct(n5, norm_d)!=0){
		double temp=(scaleproduct(n5,r.getOrigin())+u5)/scaleproduct(n5, norm_d);
		schnitt5=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt5)) {
			t5=temp;
		}else {
			t5=	1.7E+308;
		}
	}else {
		t5=-1;
	}
	//std::cout<<"t5= "<< t5<<std::endl;

	//6.Ebene (hinten):
	point3d n6 =normalenvektor(-p4, -p3);
	double u6 = unbekannte(n6, p2_);

	if(scaleproduct(n6, norm_d)!=0){
		double temp=(scaleproduct(n6,r.getOrigin())+u6)/scaleproduct(n6, norm_d);
		schnitt6=r.getOrigin()+temp*norm_d;
		if (is_inside(schnitt5)) {
			t6=temp;
		}else {
			t6=	1.7E+308;
		}
	}else {
		t6=-1;
	}
	//std::cout<<"t6= "<< t6<<std::endl;

	if (t1>0 && t1<1.7E+308) {
		if (t2>0 && t2<1.7E+308)
			t=min(t1, t2);
		else if (t3>0 && t3<1.7E+308)
			t=min(t1, t3);
		else if (t4>0 && t4<1.7E+308)
			t=min(t1, t4);
		else if (t5>0 && t5<1.7E+308)
			t=min(t1, t5);
		else if (t6>0 &&t6<1.7E+308)
			t=min(t1, t6);
		else {
			t=t1;
		}
	}else if (t2>0 &&t2<1.7E+308) {
		if (t3>0 && t3<1.7E+308)
			t=min(t2, t3);
		else if (t4>0 && t4<1.7E+308)
			t=min(t2, t4);
		else if (t5>0 && t5<1.7E+308)
			t=min(t2, t5);
		else if (t6>0 && t6<1.7E+308)
			t=min(t2, t6);
		else if (t1>0 && t1<1.7E+308)
			t=min(t2, t1);
		else {
			t=t2;
		}
	}else if (t3>0 && t3<1.7E+308) {
		if (t4>0 && t4<1.7E+308)
			t=min(t3, t4);
		else if(t5>0 && t5<1.7E+308)
			t=min(t3, t5);
		else if(t6>0 && t6<1.7E+308)
			t=min(t3, t6);
		else if (t2>0 && t2<1.7E+308)
			t=min(t3, t2);
		else if (t1>0 && t1<1.7E+308)
			t=min(t3, t1);
		else {
			t=t3;
		}
	}else if (t4>0 &&t4<1.7E+308) {
		if (t5>0 && t5<1.7E+308)
			t=min(t4, t5);
		else if (t6>0 && t6<1.7E+308)
			t=min(t4, t6);
		else if (t3>0 && t3<1.7E+308)
			t=min(t4, t3);
		else if (t2>0 && t2<1.7E+308)
			t=min(t4, t2);
		else if (t1>0 && t1<1.7E+308)
			t=min(t4, t1);
		else {
			t=t4;
		}
	}else if (t5>0 && t5<1.7E+308) {
		if (t6>0 &&t6<1.7E+308)
			t=min(t5, t6);
		else if(t4>0 && t4<1.7E+308)
			t=min(t5, t4);
		else if (t3>0 && t3<1.7E+308)
			t=min(t5, t3);
		else if (t2>0 && t2<1.7E+308)
			t=min(t5, t2);
		else if (t1>0 && t1<1.7E+308)
			t=min(t5, t1);
		else {
			t=t5;
		}
	}else if (t6>0 && t6<1.7E+308) {
		if (t5>0 &&t5<1.7E+308)
			t=min(t6, t5);
		else if(t4>0 && t4<1.7E+308)
			t=min(t6, t4);
		else if (t3>0 && t3<1.7E+308)
			t=min(t6, t3);
		else if (t2>0 && t2<1.7E+308)
			t=min(t6, t2);
		else if (t1>0 && t1<1.7E+308)
			t=min(t6, t1);
		else {
		t=t6;
		}
	}else {
		t=-1;
	}
	return t;
}


point3d
box::make_normal(point3d const& schnittpunkt) const
{
	//1.Ebene (vorder):
	point3d p3 ((p2_[0]-p1_[0]),0,0);
	point3d p4 (0, (p2_[1]-p1_[1]), 0);
	point3d n1 = normalenvektor(p3, p4);
	double u1 = unbekannte(n1,p1_);

	//2.Ebene (rechts):
	point3d p5 (0,0,(p2_[2]-p1_[2]));
	point3d n2 = normalenvektor(p5, p4);
	double u2 = unbekannte(n2, p1_);

	//3.Ebene (links):
	point3d n3 = normalenvektor(-p5, -p4);
	double u3 = unbekannte(n3, p2_);

	//4.Ebene (oben):
	point3d n4 = normalenvektor(p3, p5);
	double u4 =unbekannte(n4, p1_);

	//5.Ebene (unten):
	point3d n5 =normalenvektor(-p5, -p3);
	double u5 = unbekannte(n5, p2_);

	//6.Ebene (hinten):
	point3d n6 =normalenvektor(-p4, -p3);
	//double u6 = unbekannte(n6, p2_);


	if (scaleproduct(n1, schnittpunkt)==u1) {
		return normalize(n1);
	}else if (scaleproduct(n2, schnittpunkt)==u2) {
		return normalize(n2);
	}else if (scaleproduct(n3, schnittpunkt)==u3) {
		return normalize(n3);
	}else if (scaleproduct(n4, schnittpunkt)==u4) {
		return normalize(n4);
	}else if (scaleproduct(n5, schnittpunkt)==u5) {
		return normalize(n5);
	}else {
		return normalize(n6);
	}



}


void
box::print_on(std::ostream& str) const
{
    str<<"*BOX*"<<std::endl;
	shape::print_on(str);
	str<<"BOX"<<"\n"<<"   Punkt 1: " << p1_<<"   Punkt 2: "<<p2_<<std::flush;
}
