/*
 *  tube.hpp
 *  Objects
 */

#ifndef Tube_H
#define Tube_H

#include <string>
#include <iostream>


#include "shape.hpp"


class tube:public shape
{

public:
	tube();
	tube(std::string const& name, material const& mtr, point3d bcenter, point3d tcenter, double rad);
	tube(tube const& copy);
	~tube();

    point3d const& get_bottom_center() const;
    point3d const& get_top_center() const;
    double get_radius() const;

	point3d make_normal(point3d const& schnittpunkt) const;
	point3d teleport(point3d const& p);
	double intersect(ray const& r) const;

	void print_on(std::ostream& str) const;

private:
    point3d bottom_center_;
    point3d top_center_;
	double radius_;
	double higth_;

};

#endif
