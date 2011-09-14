#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "camera.hpp"
#include "light.hpp"
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "shape.hpp"
#include "tube.hpp"



class scene
{
    public:
        scene();
        ~scene();

        camera main_camera() const;
        void load_sdf (std::string const& sdf);

    std::map<std::string, material> materials_;
    std::list <shape*> shapes_;
    //std::list <camera> cameras_;
    camera camera_;
    std::list <light> lights_;
    //renderbefehl... render_ anlegen?
    std::string img_name_;
    std::string img_cam_;
    unsigned int img_res_x_;
    unsigned int img_res_y_;

};

#endif // SCENE_H
