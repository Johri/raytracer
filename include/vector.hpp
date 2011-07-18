// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2011 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  vector.hpp                                                                      */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(BUW_MATH3D_VECTOR_HPP)

#define BUW_MATH3D_VECTOR_HPP

// includes, system
#include <iosfwd> // fwd. decl: std::ostream

// includes, project
//#include <>

namespace math3d {

  // types, exported (class, enum, struct, union, typedef)
  
  class point;
  
  class vector {
    
  public:
 
    vector();
    vector(vector const&);
    vector(point const&, point const&);           // second - first
    vector(double, double, double, double = 0.0); // x, y, z, w
    
    ~vector();

    void swap(vector&);
    
    vector& operator=(vector const&);
    
    double const& operator[](unsigned) const;
    double&       operator[](unsigned);
    
    vector& operator+=(vector const&);
    vector& operator-=(vector const&);
    vector& operator*=(double);
    vector& operator/=(double);
    
    
    double length() const;
    double length_square() const;
    
    static vector const& null();   // v[0,0,0,0]
    static vector const& unit_x(); // v[1,0,0,0]
    static vector const& unit_y(); // v[0,1,0,0]
    static vector const& unit_z(); // v[0,0,1,0]

    vector& normalize();

  private:
    
    double data_[4];
    
  };
  
  // variables, exported (extern)
  
  // functions, inlined (inline)
  
  // functions, exported (extern)
  
  vector operator-(vector const&);
  
  vector operator+(vector const&, vector const&);
  vector operator-(point const&, point const&);
  vector operator-(vector const&, vector const&);
  vector operator*(vector const&, double);
  vector operator*(double, vector const&);
  vector operator/(vector const&, double);
  bool   operator==(vector const&, vector const&);

  double length(vector const&);
  double length_square(vector const&);
  double dot(vector const&, vector const&);
  vector cross(vector const&, vector const&);
  vector normalize(vector const&);
  
  std::ostream& operator<<(std::ostream&, vector const&);
  
} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_VECTOR_HPP)

