/*
 *  shape.hpp
 *  Vererbung
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "point3d.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "matrix.hpp"
#include <iostream>
#include <string>
#include <ostream>
#include <cmath>

class shape
{
    public:
        shape();
        shape(std::string const& name, material const& mat);
        virtual ~shape();

        std::string const& get_name() const;
        material const& get_material() const;
        virtual double intersect(ray const& r) const=0;
        virtual math3d::point3d make_normal(math3d::point3d const& p) const=0;
        double distance (math3d::point3d origin, math3d::point3d a, math3d::point3d b) const;

        virtual void print_on(std::ostream& str) const;

    private:
        std::string name_;
        material material_;
        math3d::matrix world_transformation_inv;
};

    std::ostream& operator << (std::ostream& str, shape const& s);

#endif

