#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "scene.hpp"
#include "point3d.hpp"
#include "color.hpp"
#include "material.hpp"

class renderer
{
    public:
        renderer();
        renderer(scene const& s);
        ~renderer();

        point3d reflector(shape const& mat, ray const& ray, light const& l);
        color shade(shape const& mat, ray const& r);
        void set_scene(scene const& s);
        color raytrace(ray const& r);


    private:
        scene scene_;

};

#endif // RENDERER_H
