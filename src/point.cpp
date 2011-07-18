// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2008 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  point.cpp                                                                       */
/*  project    :  lectures in programming && software engineering, winter 08/09                   */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "point.hpp"

// includes, system

#include <algorithm> // std::swap_ranges
#include <cmath>     // std::abs
#include <limits>    // std::numeric_limits
#include <ostream>   // std::ostream

// includes, project

// #include <>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace math3d {
  
  // variables, exported
  
  // functions, exported
  
  point::point()
  {
    data_[0] = data_[1] = data_[2] = 0.0; data_[3] = 1.0;
  }
  
  point::point(point const& a)
  {
    data_[0] = a.data_[0];
    data_[1] = a.data_[1];
    data_[2] = a.data_[2];
    data_[3] = a.data_[3];
  }
  
  point::point(double a, double b, double c, double d)
  {
    data_[0] = a;
    data_[1] = b;
    data_[2] = c;
    data_[3] = d;
  }

  point::~point()
  {}

  void
  point::swap(point& rhs)
  {
    std::swap_ranges(data_, data_+4, rhs.data_);
  }

  point&
  point::operator=(point const& rhs)
  {
    point tmp(rhs);

    swap(tmp);
    
    return *this;
  }

  double const&
  point::operator[](unsigned idx) const
  {
    return data_[idx];
  }

  double&
  point::operator[](unsigned idx)
  {
    return data_[idx];
  }

  point&
  point::operator+=(vector const& rhs)
  {
    data_[0] += rhs[0];
    data_[1] += rhs[1];
    data_[2] += rhs[2];
    // data_[3] += rhs[3];
    
    return *this;
  }

  point&
  point::operator-=(vector const& rhs)
  {
    data_[0] -= rhs[0];
    data_[1] -= rhs[1];
    data_[2] -= rhs[2];
    // data_[3] -= rhs[3];
    
    return *this;
  }

  /* static */ point const& 
  point::origin() 
  {
    static point origin_(0.0, 0.0, 0.0);
    return origin_;
  }

  point
  operator-(point const& rhs)
  {
    return point(-rhs[0], -rhs[1], -rhs[2], rhs[3]);
  }
  
  point
  operator+(point const& lhs, vector const& rhs)
  {
    return point(lhs) += rhs;
  }

  point
  operator-(point const& lhs, vector const& rhs)
  {
    return point(lhs) -= rhs;
  }
  
  double
  distance(point const& a, point const& b)
  {
    return std::abs(length(vector(a, b)));
  }
  
  std::ostream&
  operator<<(std::ostream& os, point const& a)
  {
    std::ostream::sentry const cerberus(os);

    if (cerberus) {
      os << '['
         << a[0] << ','
         << a[1] << ','
         << a[2] << ','
         << a[3]
         << ']';
    }

    return os;
  }
  
  bool    
  operator==(point const& lhs, point const& rhs)
  {
  return (std::fabs(rhs[0] - lhs[0]) < std::numeric_limits<double>::epsilon() && 
          std::fabs(rhs[1] - lhs[1]) < std::numeric_limits<double>::epsilon() && 
          std::fabs(rhs[2] - lhs[2]) < std::numeric_limits<double>::epsilon());
  }


} // namespace math3d {
