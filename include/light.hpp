#ifndef LIGHT_H
#define LIGHT_H

#include "point3d.hpp"
#include "color.hpp"

class light //Punktlichtquelle
{
    public:
        light();
         ~light();
    protected:
    private:
	point3d location_; //Position
	color intensity_;  //Lichtstärke
};

#endif // LIGHT_H
