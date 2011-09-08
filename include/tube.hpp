/*
 *  tube.hpp
 *  Objects
 */

#ifndef Tube_H
#define Tube_H

#include <string>
#include <iostream>
#include <cmath>

#include "shape.hpp"


class tube:public shape
{

public:
	tube();
	tube(std::string const& name, material const& mtr, point3d center, double rad, double higth);
	tube(tube const& copy);
	~tube();

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
