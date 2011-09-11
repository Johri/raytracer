#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include <string>

class camera
{
    public:
        camera();
        camera(std::string name, point3d const& loc, double fov);
         ~camera();

         ray const& calc_eye_ray(unsigned int x, unsigned int y);

         void print_on(std::ostream& str) const;

    private:
    std::string name_;
    point3d location_;
    double fov_x_;
    //point3d orientation;
};

    std::ostream& operator <<(std::ostream& str, camera const& c);

#endif // CAMERA_H
