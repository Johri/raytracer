#ifndef LIGHT_H
#define LIGHT_H

#include <string>

#include "point3d.hpp"
#include "color.hpp"

class light //Punktlichtquelle
{
    public:
        light();
        light(std::string const& name, point3d const& loc, color const& amb, color const& def);
        ~light();

        point3d const& get_location()const;
        color const& get_ambient()const;
        color const& get_defuse()const;
        void translate (double x, double y, double z);
        void rotate ();

       void print_on(std::ostream& str) const;

    private:
    std::string name_;
	point3d location_; //Position
	color ambient_;  //ambiente Lichtstärke
	color defuse_;  //diffuse Lichtstärke
};

    std::ostream& operator <<(std::ostream& str, light const& l);

#endif // LIGHT_H
