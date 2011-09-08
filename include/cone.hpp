/*
 *  cone.hpp
 *  Vererbung
 */

#ifndef KEGEL_H
#define KEGEL_H
#include "shape.hpp"
#include <iostream>
#include <cmath>
#include <string>

class cone:public shape
{

public:
	cone();
	cone(std::string const& name, material const& mtr, point3d const& center, double rad, double higth);
	~cone();

    point3d const& get_center() const;
	double get_radius() const;
	double intersect(ray const& r) const;
	point3d make_normal(point3d const& p) const;

	void print_on(std::ostream& str) const;

private:
    point3d center_;
	double radius_;
	double higth_;

};

#endif
