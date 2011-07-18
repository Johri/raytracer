// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2011 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  matrix.hpp                                                                      */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(BUW_MATH3D_MATRIX_HPP)

#define BUW_MATH3D_MATRIX_HPP

// includes, system
#include <iosfwd> // fwd. decl: std::ostream

// includes, project
#include <vector.hpp>

namespace math3d {

  // types, exported (class, enum, struct, union, typedef)

  class point;
  
  class matrix {

  public:
    
    matrix();
    matrix(matrix const&);
    matrix(double const [16]);

    ~matrix();

    void swap(matrix&);
    
    
    double const& operator[](unsigned) const;
    double&       operator[](unsigned);
    matrix& operator=(matrix const&);
    matrix& operator*=(matrix const&);
    matrix& operator*=(double);
    matrix& operator/=(double);
    
    double determinant() const;
    double trace() const;
 
    bool invert();
    void transpose();

    bool is_invertible() const; // det(M) != 0

    static matrix const& null();     // m[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    static matrix const& identity(); // m[[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]
    
  private:

    double data_[16];

  };

  // variables, exported (extern)
  
  // functions, inlined (inline)
  
  // functions, exported (extern)

  matrix operator-(matrix const&);
  
  matrix operator*(matrix const&, matrix const&);
  matrix operator*(matrix const&, double);
  matrix operator*(double, matrix const&);
  matrix operator/(matrix const&, double);
  
  point  operator*(matrix const&, point const&);
  vector operator*(matrix const&, vector const&);

  bool operator==(matrix const&, matrix const&);

  matrix make_translation(double, double, double);
  matrix make_translation(vector const&);

  matrix make_scale(double, double, double);
  matrix make_scale(vector const&);

  matrix make_rotation_x(double);
  matrix make_rotation_y(double);
  matrix make_rotation_z(double);

  double determinant(matrix const&);
  double trace(matrix const&);
  matrix inverse(matrix const&);
  matrix transpose(matrix const&);

  bool is_invertible(matrix const&);
  
  std::ostream& operator<<(std::ostream&, matrix const&);

} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_MATRIX_HPP)
