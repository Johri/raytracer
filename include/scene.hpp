#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

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

        void load_sdf (std::string const& sdf) const;

    private:
    //std::list <shape> shape_list_;
    std::list <camera> camera_list_;
    std::list <light> light_list_;

};

#endif // SCENE_H
