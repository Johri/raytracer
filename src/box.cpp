/*
 *  box.cpp
 *  Vererbung
 */

#include "box.hpp"

box::box()
:shape("standardBox", material()),p1_(0,0,0),p2_(1,1,1)
{
	std::cout<<"Standardobjekt Box erzeugt"<<"\n"<<std::endl;
}
box::box(std::string const& name, material const& mat, point3d const& x, point3d const& y):
shape(name,mat),
p1_(x),
p2_(y)
{

}

box::~box()
{
	std::cout<<"Standardobjekt Box gelöscht"<<"\n"<<std::endl;
}

point3d
const& box::getX() const
{
	return p1_;
}


point3d
const& box::getY() const
{
	return p2_;
}


bool
box::is_inside(point3d const& p) const
{
	return p2_.getX()<p.getX()<p1_.getX() && p2_.getY()<p.getY()<p1_.getY() && p1_.getZ()<p.getZ()<p2_.getZ();
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
d_wert(point3d p, point3d p1)
{
	double d= p.getX()*p1.getX()+p.getY()*p1.getY()+p.getZ()*p1.getZ();
	return d;
}


double
unbekannte(point3d p,point3d aufziehpunkt, point3d a, point3d b)
{     //a und b von der Geradengleichung
	if(d_wert(p, b) !=0){
	double unbekannte=d_wert(p, aufziehpunkt) -(d_wert(p,a)/d_wert(p,b));
	return unbekannte;
	}else {
		std::cout<<"Kein Schnittpunkt"<<std::endl;
		return -1; //immer mit if angeben
	}

}


double
box::intersect(ray const& r) const
{
	double t;
	//Ebenengleichungen aufstellen, normieren (normalenvektor*ortsvektor=d) und in jede die Gerade vom Ray einsetzen
	//->> nach Unbekannte u auflösen:

	//1.Ebene (vorne):
	point3d p3 ((p2_.getX()-p1_.getX()),0,0);
	point3d p4 (0, (p2_.getY()-p1_.getY()), 0);
	point3d n1 = normalenvektor(p3, p4);
	double u1 = unbekannte(n1,p1_, r.getOrigin(), r.getDir());
	point3d schnitt1 ((r.getOrigin().getX()+u1*r.getDir().getX()), (r.getOrigin().getY()+u1*r.getDir().getY()), (r.getOrigin().getZ()+u1*r.getDir().getZ()));


	//2.Ebene (rechts):
	point3d p5 (0,0,(p2_.getZ()-p1_.getZ()));
	point3d p6 (0,p1_.getY(),0); //überlegen
	point3d n2 = normalenvektor(p5, p6);
	double u2 = unbekannte(n2, p2_, r.getOrigin(), r.getDir());
	point3d schnitt2 ((r.getOrigin().getX()+u2*r.getDir().getX()), (r.getOrigin().getY()+u2*r.getDir().getY()), (r.getOrigin().getZ()+u2*r.getDir().getZ()));


	//3.Ebene (links):
	point3d p7 (p1_.getX(),p1_.getY(),p2_.getZ());
	point3d p8 (p1_.getX(),p2_.getY(),p2_.getZ());
	point3d n3 = normalenvektor(p7, p4);
	double u3 = unbekannte(n3, p8, r.getOrigin(), r.getDir());
	point3d schnitt3 ((r.getOrigin().getX()+u3*r.getDir().getX()), (r.getOrigin().getY()+u3*r.getDir().getY()), (r.getOrigin().getZ()+u3*r.getDir().getZ()));


	//4.Ebene (oben):
	point3d n4 = normalenvektor(p7, p3);
	double u4 =unbekannte(n4, p1_, r.getOrigin(), r.getDir());
	point3d schnitt4 ((r.getOrigin().getX()+u4*r.getDir().getX()), (r.getOrigin().getY()+u4*r.getDir().getY()), (r.getOrigin().getZ()+u4*r.getDir().getZ()));


	//5.Ebene (unten):
	point3d n5 =normalenvektor(p5, p8);
	double u5 = unbekannte(n5, p2_, r.getOrigin(), r.getDir());
	point3d schnitt5 ((r.getOrigin().getX()+u5*r.getDir().getX()), (r.getOrigin().getY()+u5*r.getDir().getY()), (r.getOrigin().getZ()+u5*r.getDir().getZ()));

	//Schnittpunktentfernung prüfen:
	if (p1_.getX()<=schnitt1.getX()<=p2_.getX() && p2_.getY()<=schnitt1.getY()<=p1_.getY()) {
		if(p1_.getZ()<=schnitt2.getZ()<=p2_.getZ() && p2_.getY()<=schnitt2.getY()<=p1_.getY()){
			return t=shape::distance (r.getOrigin(), schnitt1, schnitt2);
		} else if (p1_.getZ()<=schnitt3.getZ()<=p2_.getZ() && p2_.getY()<=schnitt3.getY()<=p1_.getY()) {
			return t=shape::distance (r.getOrigin(), schnitt1, schnitt3);
		} else if (p1_.getX()<=schnitt4.getX()<=p2_.getX() && p1_.getZ()<=schnitt4.getZ()<=p2_.getZ()) {
			return t=shape::distance (r.getOrigin(), schnitt1, schnitt4);
		} else if (p1_.getX()<=schnitt5.getX()<=p2_.getX() && p1_.getZ()<=schnitt5.getZ()<=p2_.getZ()) {
			return t=shape::distance (r.getOrigin(), schnitt1, schnitt5);
		} else {
			return t=sqrt((r.getOrigin().getX()-schnitt1.getX())*(r.getOrigin().getX()-schnitt1.getX())+(r.getOrigin().getY()-schnitt1.getY())*(r.getOrigin().getY()-schnitt1.getY())+(r.getOrigin().getZ()-schnitt1.getZ())*(r.getOrigin().getZ()-schnitt1.getZ()));
		}
	} else 	if (p1_.getZ()<=schnitt2.getZ()<=p2_.getZ() && p2_.getY()<=schnitt2.getY()<=p1_.getY()) {
		if(p1_.getX()<=schnitt5.getX()<=p2_.getX() && p1_.getZ()<=schnitt5.getZ()<=p2_.getZ()){
			return t=shape::distance (r.getOrigin(), schnitt2, schnitt5);
		} else if (p1_.getZ()<=schnitt3.getZ()<=p2_.getZ() && p2_.getY()<=schnitt3.getY()<=p1_.getY()) {
			return t=shape::distance (r.getOrigin(), schnitt2, schnitt3);
		} else if (p1_.getX()<=schnitt4.getX()<=p2_.getX() && p1_.getZ()<=schnitt4.getZ()<=p2_.getZ()) {
			return t=shape::distance (r.getOrigin(), schnitt2, schnitt4);
		}  else {
			return t=sqrt((r.getOrigin().getX()-schnitt2.getX())*(r.getOrigin().getX()-schnitt2.getX())+(r.getOrigin().getY()-schnitt2.getY())*(r.getOrigin().getY()-schnitt2.getY())+(r.getOrigin().getZ()-schnitt2.getZ())*(r.getOrigin().getZ()-schnitt2.getZ()));
		}
	} else if (p1_.getZ()<=schnitt3.getZ()<=p2_.getZ() && p2_.getY()<=schnitt3.getY()<=p1_.getY()) {
		if(p1_.getX()<=schnitt5.getX()<=p2_.getX() && p1_.getZ()<=schnitt5.getZ()<=p2_.getZ()){
			return t=shape::distance (r.getOrigin(), schnitt3, schnitt5);
		} else if (p1_.getX()<=schnitt4.getX()<=p2_.getX() && p1_.getZ()<=schnitt4.getZ()<=p2_.getZ()) {
			return t=shape::distance (r.getOrigin(), schnitt3, schnitt4);
		} else {
			return t=sqrt((r.getOrigin().getX()-schnitt3.getX())*(r.getOrigin().getX()-schnitt3.getX())+(r.getOrigin().getY()-schnitt3.getY())*(r.getOrigin().getY()-schnitt3.getY())+(r.getOrigin().getZ()-schnitt3.getZ())*(r.getOrigin().getZ()-schnitt3.getZ()));
		}
	} else if (p1_.getX()<=schnitt4.getX()<=p2_.getX() && p1_.getZ()<=schnitt4.getZ()<=p2_.getZ()) {
		if(p1_.getX()<=schnitt5.getX()<=p2_.getX() && p1_.getZ()<=schnitt5.getZ()<=p2_.getZ()){
			return t=shape::distance (r.getOrigin(), schnitt4, schnitt5);
		}  else {
			return t=sqrt((r.getOrigin().getX()-schnitt4.getX())*(r.getOrigin().getX()-schnitt4.getX())+(r.getOrigin().getY()-schnitt4.getY())*(r.getOrigin().getY()-schnitt4.getY())+(r.getOrigin().getZ()-schnitt4.getZ())*(r.getOrigin().getZ()-schnitt4.getZ()));
		}
	} else if (p1_.getX()<=schnitt5.getX()<=p2_.getX() && p1_.getZ()<=schnitt5.getZ()<=p2_.getZ()) {
		return t=sqrt((r.getOrigin().getX()-schnitt5.getX())*(r.getOrigin().getX()-schnitt5.getX())+(r.getOrigin().getY()-schnitt5.getY())*(r.getOrigin().getY()-schnitt5.getY())+(r.getOrigin().getZ()-schnitt5.getZ())*(r.getOrigin().getZ()-schnitt5.getZ()));
	} else {
		std::cout<<"Kein Schnittpunkt"<<std::endl;
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
	str<<"BOX"<<"\n"<<"   Punkt 1: " << p1_<<"   Punkt 2: "<<p2_<<std::endl;
}
