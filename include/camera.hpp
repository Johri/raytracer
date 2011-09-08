#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"

class camera
{
    public:
        camera();
         ~camera();

         ray calc_eye_ray(unsigned int x, unsigned int y);
    protected:
    private:
};

#endif // CAMERA_H
