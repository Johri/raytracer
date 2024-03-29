// header i/f
#include "color.hpp"

// header, system
#include <iostream>

// header, project


////////////////////////////////////////////////////////////////////////////////
color::color()
{
  data_[0] = 0;
  data_[1] = 0;
  data_[2] = 0;
}


////////////////////////////////////////////////////////////////////////////////
color::color(color const& rhs)
{
  data_[0] = rhs.data_[0];
  data_[1] = rhs.data_[1];
  data_[2] = rhs.data_[2];
}


////////////////////////////////////////////////////////////////////////////////
color::color(float r, float g, float b)
{
  data_[0] = r;
  data_[1] = g;
  data_[2] = b;
}


////////////////////////////////////////////////////////////////////////////////
color::~color()
{}


////////////////////////////////////////////////////////////////////////////////
void
color::swap(color& rhs)
{
  std::swap(data_[0], rhs.data_[0]);
  std::swap(data_[1], rhs.data_[1]);
  std::swap(data_[2], rhs.data_[2]);
}



////////////////////////////////////////////////////////////////////////////////
void
color::print(std::ostream& os) const
{
  os << '(' << data_[0] << '|' << data_[1] << '|' << data_[2] << ')' << std::endl;
}



////////////////////////////////////////////////////////////////////////////////
color::value_t&
color::operator[](unsigned c)
{
  return data_[c];
}



////////////////////////////////////////////////////////////////////////////////
const color::value_t&
color::operator[](unsigned c) const
{
  return data_[c];
}



////////////////////////////////////////////////////////////////////////////////
color&
color::operator=(color const& rhs)
{
  color tmp(rhs);
  swap(tmp);
  return *this;
}


////////////////////////////////////////////////////////////////////////////////
void
color::operator+=(color const& a)
{
  data_[0]+=a.data_[0];
  data_[1]+=a.data_[1];
  data_[2]+=a.data_[2];
}


////////////////////////////////////////////////////////////////////////////////
color
color::operator*=(color const& a)
{
  data_[0]*=a.data_[0];
  data_[1]*=a.data_[1];
  data_[2]*=a.data_[2];
  return *this;
}



////////////////////////////////////////////////////////////////////////////////
color
color::operator*=(double a)
{
  data_[0]*=a;
  data_[1]*=a;
  data_[2]*=a;
  return *this;
}



////////////////////////////////////////////////////////////////////////////////
color
operator*(color const& a, color const& b)
{
  color result(a);
  result *= b;
  return result;
}



////////////////////////////////////////////////////////////////////////////////
color
operator*(color const& a, double b)
{
  color result(a);
  result *= b;
  return result;
}



////////////////////////////////////////////////////////////////////////////////
color
operator+(color const& a, color const& b)
{
  color result(a);
  result += b;
  return result;
}



////////////////////////////////////////////////////////////////////////////////
std::ostream&
operator<<(std::ostream& os, color const& color)
{
  color.print(os);
  return os;
}
