#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include "point3d.hpp"
#include <string>

using namespace math3d;

class camera
{
    public:
        camera();
        camera(std::string name, point3d const& loc, double w, double h, double fov);
        ~camera();

        double get_d();
        ray calc_eye_ray(double x,double y) const;

         void print_on(std::ostream& str) const;

    private:
    std::string name_;
    point3d location_;
    double width_;
    double heigth_;
    double fov_x_;
    double d_;
};

    std::ostream& operator <<(std::ostream& str, camera const& c);

#endif // CAMERA_H
