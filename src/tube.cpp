/*
 *  tube.cpp
 *  Objects
 */

#include "tube.hpp"


tube::tube()
:shape("standard tube", material()), start_(0,0,0), end_(0,1,0), r_(0)
{
	std::cout<<"Standardobjekt Tube erzeugt"<<"\n"<<std::endl;
}


tube::tube(std::string const& name, material const& mtr, math3d::point3d bcenter, math3d::point3d tcenter, double rad):
shape(name, mtr), start_(bcenter), end_(tcenter), r_(rad)
{
	std::cout<<"Tube erzeugt"<<"\n"<<std::endl;
}


tube::tube(tube const& copy):
shape(copy.shape::get_name(), copy.shape::get_material()), start_(copy.start_), end_(copy.end_), r_(copy.r_)
{
	std::cout<<"Tube kopiert"<<"\n"<<std::endl;
}

tube::~tube()
{
	std::cout<<"Tube gelöscht"<<"\n"<<std::endl;
}



math3d::point3d const&
tube::get_start() const
{
	return start_;
}


math3d::point3d const&
tube::get_end() const
{
	return end_;
}



double
tube::get_radius() const{
	return r_;
}


math3d::point3d
tube::make_normal(math3d::point3d const& schnittpunkt) const
{
	math3d::point3d q= normalize(end_-start_); //Richtungsvektor der Zylindermittelachse normalisiert
	double unbekannte=scaleproduct(q, start_);
	double unbekannte2=scaleproduct(q, end_);

	if (scaleproduct(q, schnittpunkt)==unbekannte) {
		return -q;
	}else if (scaleproduct(q, schnittpunkt)==unbekannte2) {
		return q;
	}else {
		double zaehler=schnittpunkt[0]*q[0]-start_[0]*q[0]+schnittpunkt[1]*q[1]-start_[1]*q[1]+schnittpunkt[2]*q[2]-start_[2]*q[2];
		double nenner=q[0]*q[0]+q[1]*q[1]+q[2]*q[2];
		double temp=zaehler/nenner;
		//std::cout<<"Zähler:"<<zaehler<<std::endl;
		math3d::point3d m=start_+temp*q;
		//std::cout<<"temp: "<<temp<<std::endl;
		//std::cout<<"Lotfusspunkt: "<<m<<std::endl;
		math3d::point3d norm=schnittpunkt-m;
		return normalize(norm);
	}
}


math3d::point3d tube::teleport(math3d::point3d const& p)
{
	return start_=p;
}


double
tube::intersect(ray const& r) const
{
	double t,t1,t2,t_temp1, t_temp2,t_temp3, t_temp;
	point3d schnitt1, schnitt2;
	double height=length_two_points(start_, end_);
	point3d dir=normalize(r.getDir());
	point3d q= normalize(end_-start_); //Richtungsvektor der Zylindermittelachse normalisiert
	point3d a= r.getOrigin()-start_;

	//Erstmal Schnittpunkte mit Zylinder ermitteln:
	point3d e= dir-(scaleproduct(dir, q)/scaleproduct(q, q))*q;
	point3d f= a-(scaleproduct(a, q)/scaleproduct(q, q))*q;

	//übersichtlich zusammenfassen: t_temp1
	double one, two, three;
	one=scaleproduct(e, e);
	two=scaleproduct(e, f)*2;
	three=scaleproduct(f, f)-r_*r_;
	double nenner=2*one;

	/*std::cout << "Richtungsvektor von Tube: "<<q<<std::endl;
	std::cout << "a: "<<a<<std::endl;
	std::cout << "e: "<<e<<std::endl;
	std::cout << "f: "<<f<<std::endl;
	std::cout << "one: "<<one<<std::endl;
	std::cout << "two: "<<two<<std::endl;
	std::cout << "three: "<<three<<std::endl;
	std::cout << "Nenner: "<<2*one<<std::endl;
	std::cout << "Skalar von q: "<<scaleproduct(q, q)<<std::endl;
    */

	if (nenner==0 || two*two<(4*one*three)) {
		//std::cout<<"Kein Schnittpunkt mit Zylinder"<<std::endl;
		t_temp1=-1;
	}else {
	t1=(-two-sqrt(two*two-(4*one*three)))/nenner;
		schnitt1=r.getOrigin()+t1*dir;
	t2=(-two+sqrt(two*two-(4*one*three)))/nenner;
		schnitt2=r.getOrigin()+t2*dir;

		//std::cout << "t1:"<<t1<<std::endl;
		//std::cout << "t2:"<<t2<<std::endl;

	/*	double x1=scaleproduct(schnitt1, q)/scaleproduct(q, q);
		double x2=scaleproduct(schnitt2, q)/scaleproduct(q, q);

	std::cout<<"x1: "<<x1<<std::endl;
	std::cout<<"x2: "<<x2<<std::endl;*/


		//gucken, welcher der Abstände kleiner ist, aber größer als 0:

	if (t1>0) {
		if (t2>0) {
			if (t1>t2) {
				t_temp1=t2;
			}else {
					t_temp1=t1;
			}
		}else {
				t_temp1=t1;
		}

	}else {
			t_temp1=t2;
	}
	//std::cout<<"Schnittpunkt mit dem Zylinder"<<t_temp1<<std::endl;

		//hier gucken wir, ob die Länge des Zylinders nicht überschritten wird:
		point3d mittelpunkt=start_+height/2*normalize(end_-start_);
		double hypothenuse_x1=length_two_points(schnitt1, mittelpunkt)+0.001;
		double radius=r_*r_;

		double this_height_x1=sqrt(hypothenuse_x1*hypothenuse_x1-radius);

		double hypothenuse_x2=length_two_points(schnitt1, mittelpunkt)+0.001;
		double this_height_x2=sqrt(hypothenuse_x2*hypothenuse_x2-radius);

	if (t_temp1==t2) {
		if (this_height_x2<=height/2) {
			t_temp1=t2;
		}else {
			t_temp1=-1;
		}
	}else {
		if (this_height_x1<=height/2) {
			t_temp1=t1;
		}else {
			t_temp1=-1;
		}
	}
	}


	// Die Kreise (Deckel und Boden des Zylinders):
	double s=scaleproduct(q, start_);
	double s2=scaleproduct(q, end_);

	if (scaleproduct(q, dir)!=0) {
		double temp=(scaleproduct(q, r.getOrigin())+s)/scaleproduct(q, dir);
		point3d schnitt=r.getOrigin()+temp*dir;
		if (length_two_points(schnitt, start_)<=r_) {
			t_temp2=temp;
		}else {
			t_temp2=-1;
			//std::cout<<"Schnittpunkt mit Ebene aber nicht mit Kreis"<<std::endl;
		}

	}else {
		t_temp2=-1;
		//std::cout<<"Kein Schnittpunkt mit Kreisebene"<<std::endl;
	}
	if (scaleproduct(q, dir)!=0) {
		double temp=(scaleproduct(q, r.getOrigin())+s2)/scaleproduct(q, dir);
		point3d schnitt=r.getOrigin()+temp*dir;
		if (length_two_points(schnitt, end_)<=r_) {
			t_temp3=temp;
		}else {
			t_temp3=-1;
			//std::cout<<"Schnittpunkt mit Ebene aber nicht mit Kreis"<<std::endl;
		}

	}else {
		t_temp3=-1;
		//std::cout<<"Kein Schnittpunkt mit Kreisebene"<<std::endl;
	}

	//gucken, welcher der Abstände kleiner ist, aber größer als 0:


	if (t_temp2>0) {
		if (t_temp3>0) {
			if (t_temp2>t_temp3) {
				t_temp=t_temp3;
			}else {
				t_temp=t_temp2;
			}
		}else {
			t_temp=t_temp2;
		}
	}else {
		if (t_temp3>0) {
			t_temp=t_temp3;
		}else {
			t_temp=-1;
			//std::cout<<"Kein Schnittpunkt mit den Deckel/Boden"<<std::endl;
		}
	}


	//gucken, welcher Abstand (entweder Kreis oder Zylinder) kleiner, aber nicht 0 ist:

	if (t_temp>0) {
		if (t_temp1>0) {
			if (t_temp>t_temp1) {
				t=t_temp1;
			}else {
				t=t_temp;
			}
		}else {
			t=t_temp;
		}
	}else {
		if (t_temp1>0) {
			t=t_temp1;
		}else {
			t=-1;
			//std::cout<<"Schnittpunkt weder mit Deckel/Boden noch Zyliderhülle"<<std::endl;
		}
	}
	if (t>200) {
		t=-1;
	}
	//std::cout<<"t-temp1: "<<t_temp1<<std::endl;
	//std::cout<<"Schnittpunkt mit Zylinder ist: "<<t<<std::endl;
	return t;
}


void
tube::print_on(std::ostream& str) const
{
    str<<"*TUBE*"<<std::endl;
	shape::print_on(str);
	str<<"TUBE"<<"\n"<<"   unterer Mittelpunkt: "<<start_<<"   oberer Mittelpunkt: "<<end_<< "   Radius: " << r_<<std::endl;
}
