#ifndef CIRCLE_H
#define CIRCLE_H

#include "point3d.hpp"
#include "shape.hpp"

class circle:public shape
{
    public:
        circle();
        circle(std::string const& name, material const& mat, point3d const& center, point3d const& p1, point3d const& p2);
        ~circle();

        point3d const& get_center() const;
        double get_radius() const;

        void teleport(point3d const& p);

        bool is_inside(point3d const& point) const;
        double intersect(ray const& r) const;
        point3d make_normal(point3d const& p) const;

        void print_on(std::ostream& str) const;

    private:
        point3d center_;
        point3d p1_;
        point3d p2_;
        double radius_;
};

#endif // CIRCLE_H
