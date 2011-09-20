#ifndef LIGHT_H
#define LIGHT_H

#include <string>

#include "point3d.hpp"
#include "color.hpp"
#include <iosfwd>

using namespace math3d;

class light //Punktlichtquelle
{
    public:
        light();
        light(std::string const& name, point3d const& loc, color const& amb, color const& diff);
        ~light();

        point3d const& get_location()const;
        color const& get_ambient()const;
        color const& get_diffuse()const;
        void translate (double x, double y, double z);
        void rotate ();

    void print_on(std::ostream& str) const;

    private:
    std::string name_;
	point3d location_; //Position
	color ambient_;  //ambiente Lichtstärke
	color diffuse_;  //diffuse Lichtstärke
};

    std::ostream& operator <<(std::ostream& str, light const& l);

#endif // LIGHT_H
