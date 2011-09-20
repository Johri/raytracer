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

#include "point3d.hpp"

// includes, system

#include <algorithm> // std::swap_ranges
#include <cmath>     // std::abs
#include <limits>    // std::numeric_limits
#include <ostream>   // std::ostream

    // includes, project

    // #include <>

    // internal unnamed namespace

    namespace
    {

        // types, internal (class, enum, struct, union, typedef)

        // variables, internal

        // functions, internal

    } // namespace {

    namespace math3d {

    // variables, exported

    // functions, exported

    point3d::point3d()
    {
        data_[0] = data_[1] = data_[2] = 0.0; data_[3] = 1.0;
    }

    point3d::point3d(point3d const& a)
    {
        data_[0] = a.data_[0];
        data_[1] = a.data_[1];
        data_[2] = a.data_[2];
        data_[3] = a.data_[3];
    }

    point3d::point3d(double a, double b, double c, double d)
    {
        data_[0] = a;
        data_[1] = b;
        data_[2] = c;
        data_[3] = d;
    }

    point3d::~point3d()
    {

    }


    void
    point3d::swap(point3d& rhs)
    {
        std::swap_ranges(data_, data_+4, rhs.data_);
    }


    point3d&
    point3d::operator=(point3d const& rhs)
    {
        point3d tmp(rhs);

        swap(tmp);

        return *this;
    }

    double const&
    point3d::operator[](unsigned idx) const
    {
        return data_[idx];
    }

    double&
    point3d::operator[](unsigned idx)
    {
        return data_[idx];
    }

    point3d&
    point3d::operator+=(point3d const& rhs)
    {
        data_[0] += rhs[0];
        data_[1] += rhs[1];
        data_[2] += rhs[2];
        // data_[3] += rhs[3];

        return *this;
    }

    point3d&
    point3d::operator-=(point3d const& rhs)
    {
        data_[0] -= rhs[0];
        data_[1] -= rhs[1];
        data_[2] -= rhs[2];
        // data_[3] -= rhs[3];

        return *this;
    }


    /* static */point3d const&
    point3d::origin()
    {
        static point3d origin_(0.0, 0.0, 0.0);
        return origin_;
    }


    std::ostream&
    operator<<(std::ostream& os, point3d const& a)
    {
        std::ostream::sentry const cerberus(os);

        if (cerberus)
        {
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
	operator==(point3d const& lhs, point3d const& rhs)
	{
		return (lhs[0]==rhs[0] && lhs[1]==rhs[1] && lhs[2]==rhs[2]);
	}


	void point3d::translate (double x, double y, double z)
	{
		data_[0]+=x;
		data_[1]+=y;
		data_[2]+=z;
	}


	void
	point3d::teleport (point3d const& destination)
	{
		data_[0]=destination[0];
		data_[1]=destination[1];
		data_[2]=destination[2];
	}

/*	void point3d::rotate_y (double bog_y)
	{
		double radius=std::sqrt(x_*x_+y_*y_);
		double phi=asin(y_/ radius);
		x_=radius*cos(phi+bog_y);
		y_=radius*sin(phi+bog_y);
	}*/

	point3d
	operator *(point3d const& p1, point3d const& p2)
	{

		double x=p1[0]*p2[0];
		double y=p1[1]*p2[1];
		double z=p1[2]*p2[2];
		point3d p(x,y,z);
		return p;
	}
	point3d
	operator *(double d, point3d const& p)
	{
		double x=d*p[0];
		double y=d*p[1];
		double z=d*p[2];
		point3d point(x,y,z);
		return point;
	}
	double
	scaleproduct(point3d const& p1, point3d const& p2)
	{
		double x=p1[0]*p2[0];
		double y=p1[1]*p2[1];
		double z=p1[2]*p2[2];
		double p=x+y+z;
		return p;
	}

	double
	length(point3d const& p)
	{
		double d=sqrt((p[0]*p[0]+p[1]*p[1]+p[2]*p[2]));
		return d;
	}


	double
	length_two_points(point3d const& p, point3d const& q)
	{
		double d=sqrt((p[0]-q[0])*(p[0]-q[0])+(p[1]-q[1])*(p[1]-q[1])+(p[2]-q[2])*(p[2]-q[2]));
		return d;
	}

	point3d
	normalize(point3d const& p)
	{
		double d=length(p);
		double a=p[0]/d;
		double b=p[1]/d;
		double c=p[2]/d;
		point3d normal(a,b,c);
		return normal;
	}

	point3d
	normalenvektor(point3d p1,point3d p2)
	{
		double a=p1[1]*p2[2]-p1[2]*p2[1];
		double b=p1[2]*p2[0]-p1[0]*p2[2];
		double c=p1[0]*p2[1]-p1[1]*p2[0];
		point3d normalenvektor(a,b,c);
		return normalenvektor;
	}

	point3d
	operator -(point3d const& p1, point3d const& p2)
	{

		double x=p1[0]-p2[0];
		double y=p1[1]-p2[1];
		double z=p1[2]-p2[2];
		point3d p(x,y,z);
		return p;
	}
	point3d
	operator -(point3d const& p)
	{
		double x=p[0]*-1;
		double y=p[1]*-1;
		double z=p[2]*-1;
		point3d point(x,y,z);
		return point;
	}
	point3d
	operator +(point3d const& p1, point3d const& p2)
	{
		double x=p1[0]+p2[0];
		double y=p1[1]+p2[1];
		double z=p1[2]+p2[2];
		point3d p(x,y,z);
		return p;
	}

	point3d
	crossproduct(point3d const& p1, point3d const& p2)
	{
		double a=p1[1]*p2[2]-p1[2]*p2[1];
		double b=p1[2]*p2[0]-p1[0]*p2[2];
		double c=p1[0]*p2[1]-p1[1]*p2[0];
		point3d normalenvektor(a,b,c);
		return normalenvektor;
	}


} // namespace math3d {
