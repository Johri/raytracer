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
#include "material_map.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "shape.hpp"



class scene
{
    public:
        scene();
        scene(scene const& first_scene);
        ~scene();

        void load_sdf (std::string const& sdf);

    private:
    std::map<std::string, material> materials_;
    std::list <shape*> shapes_;
    std::list <camera> cameras_;
    std::list <light> lights_;

};

#endif // SCENE_H
