/*
 *  box.h
 *  Vererbung
 */
#ifndef BOX_H
#define BOX_H

#include <iostream>
#include "shape.hpp"

class box: public shape
{

    public:
        box();
        box(std::string const& name, material const& mat, point3d const& x, point3d const& y);
        ~box();

        point3d const& getX() const;
        point3d const& getY() const;
        bool is_inside(point3d const& p) const;
        double intersect(ray const& r) const;
        void rotate (double bog);
        point3d make_normal(point3d const& p) const;

        void print_on(std::ostream& str) const;

    private:
        point3d p1_; // muss in der x und z Achse kleiner sein als in p2_
        point3d p2_;
};

#endif

