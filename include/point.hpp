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

// includes, project
#include <vector.hpp>

namespace math3d {

  // types, exported (class, enum, struct, union, typedef)
  
  class point {
    
  public:

    point();
    point(point const&);
    point(double, double, double, double = 1.0); // x, y, z, w
    
    ~point();

    void swap(point&);
    
    point& operator=(point const&);
    
    double const& operator[](unsigned) const;
    double&       operator[](unsigned);

    point& operator+=(vector const&);
    point& operator-=(vector const&);

    static point const& origin();     // p[0,0,0,1]

  private:
    
    double data_[4];
    
  };
  
  // variables, exported (extern)
  
  // functions, inlined (inline)
  
  // functions, exported (extern)
  
  point operator-(point const&);
  
  point operator+(point const&, vector const&);
  point operator-(point const&, vector const&);
  bool operator==(point const&, point const&);
    
  double distance(point const&, point const&);
  
  std::ostream& operator<<(std::ostream&, point const&);
  
} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_POINT_HPP)
