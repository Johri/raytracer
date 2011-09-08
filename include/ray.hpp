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
private:
	point3d origin_;
	point3d direction_;
public:
	ray();
	ray(point3d const& origin, point3d const& direction);
	ray(ray const& copy);
	~ray();

	ray& operator=(ray const& rhs);
	point3d const& getOrigin()const;
	point3d const& getDir()const;

	color const& getColor(double t, shape const& s, ray const& r) const;
};

#endif
