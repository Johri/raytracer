

#ifndef POINT2D_H
#define POINT2D_H

#include <ostream>

class point3d {
private:
	double x_;
	double y_;
	double z_;
public:
	point3d();
	point3d(double x, double y, double z);
	point3d(point3d const& rhs);
	~point3d();
	double getX() const;
	double getY() const;
	double getZ() const;
	double& operator [](int wert);
	void print_on(std::ostream& str) const;
	
};
point3d operator *(point3d const& p1, point3d const& p2);
point3d operator -(point3d const& p1, point3d const& p2);
bool operator==(point3d const& lhs, point3d const& rhs);
std::ostream& operator<<(std::ostream& str, point3d const& p);



#endif