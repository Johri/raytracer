/*
 *  tube.hpp
 *  Objects
 */

#ifndef Tube_H
#define Tube_H

#include <string>
#include <iostream>


#include "shape.hpp"

using namespace math3d;

class tube:public shape
{

public:
	tube();
	tube(std::string const& name, material const& mtr, math3d::point3d bcenter, math3d::point3d tcenter, double rad);
	tube(tube const& copy);
	~tube();

    math3d::point3d const& get_start() const;
    math3d::point3d const& get_end() const;
    double get_radius() const;

	math3d::point3d make_normal(math3d::point3d const& schnittpunkt) const;
	math3d::point3d teleport(math3d::point3d const& p);
	double intersect(ray const& r) const;

	void print_on(std::ostream& str) const;

private:
    math3d::point3d start_;
    math3d::point3d end_;
	double r_;

};

#endif
