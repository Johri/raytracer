#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.hpp"
#include "point3d.hpp"

using namespace math3d;

class triangle: public shape
{

public:
	triangle();
	triangle(std::string const& name, material const& mat, point3d const& first, point3d const& second,point3d const& third);
	~triangle();
	point3d const& getFirst() const;
	point3d const& getSecond() const;
	point3d const& getThird() const;

	double intersect(ray const& r) const;
	point3d make_normal(point3d const& p) const;

	virtual void print_on(std::ostream& str) const;

private:
	point3d first_;
	point3d second_;
	point3d third_;


};

    //std::ostream& operator << (std::ostream& str, shape const& s);

#endif
