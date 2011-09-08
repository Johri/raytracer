/*
 *  sphere.h
 *  Vererbung
 */

#ifndef SPHERE_H
#define SPHERE_H
#include "shape.hpp"
#include <iostream>
#include <cmath>

class sphere :public shape {

public:
	sphere();
	sphere(std::string const& name, material const& mat, double r, point3d const& p);
	~sphere();
	double getRadius() const;
	point3d const& getMiddle() const;
	double volume() const;
	double surface() const;
	double intersect(ray const& r) const;
	bool is_inside(point3d const& p) const;
	point3d make_normal(point3d const& p) const;

	void print_on(std::ostream& str) const;

private:
	double radius_;
	point3d center_;
};

#endif
