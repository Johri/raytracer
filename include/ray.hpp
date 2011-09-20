/*
 *  ray.h
 *  Objects
 */


#ifndef Ray_H
#define Ray_H

#include "point3d.hpp"
#include "color.hpp"


class shape;


class ray{

public:
	ray();
	ray(math3d::point3d const& origin, math3d::point3d const& direction);
	ray(ray const& copy);
	~ray();

	ray& operator=(ray const& rhs);
	math3d::point3d const& getOrigin()const;
	math3d::point3d getDir()const;
	color getColor(double t, shape const& s, ray const& r) const;
	math3d::point3d getSchnitt(double t) const;

	void print_on(std::ostream& str) const;

private:
	math3d::point3d origin_;
	math3d::point3d direction_;
};

    std::ostream& operator <<(std::ostream& str, ray const& r);

#endif
