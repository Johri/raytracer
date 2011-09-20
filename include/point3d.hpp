// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2011 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  point.hpp                                                                       */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(BUW_MATH3D_POINT_HPP)

#define BUW_MATH3D_POINT_HPP

// includes, system
#include <iosfwd> // fwd. decl: std::ostream


namespace math3d {

  // types, exported (class, enum, struct, union, typedef)

  class point3d {

  public:

    point3d();
    point3d(point3d const&);
    point3d(double, double, double, double = 1.0); // x, y, z, w

    ~point3d();

    void swap(point3d&);

    point3d& operator=(point3d const&);

    double const& operator[](unsigned) const;
    double&       operator[](unsigned);

    point3d& operator+=(point3d const&);
    point3d& operator-=(point3d const&);

	void translate (double x, double y, double z);
	void teleport (point3d const& destination);

    static point3d const& origin();     // p[0,0,0,1]

  private:

    double data_[4];

  };

  // variables, exported (extern)

  // functions, inlined (inline)

  // functions, exported (extern)

    std::ostream& operator<<(std::ostream&, point3d const&);


	point3d operator *(point3d const& p1, point3d const& p2);
	point3d operator *(double d, point3d const& p);
	point3d operator -(point3d const& p1, point3d const& p2);
	point3d operator -(point3d const& p);
	point3d operator +(point3d const& p1, point3d const& p2);
	bool operator==(point3d const& lhs, point3d const& rhs);
	point3d crossproduct(point3d const& p1, point3d const& p2);
	double scaleproduct(point3d const& p1, point3d const& p2);
	point3d normalize(point3d const& p);
	point3d normalenvektor(point3d p1,point3d p2);
	double length(point3d const& p);
	double length_two_points(point3d const& p, point3d const& q);




} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_POINT_HPP)
