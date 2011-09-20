#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "scene.hpp"
#include "point3d.hpp"
#include "color.hpp"
#include "material.hpp"

class shape;

class renderer
{
    public:
        renderer();
        renderer(scene const& s);
        ~renderer();

        bool delta(shape const& mat, ray const& ray, light const& l);
        color mirror(shape const& shap, ray const& ray);
        color refrection(shape const& shap, ray const& ray);
        math3d::point3d reflector(shape const& mat, ray const& ray, light const& l);
        color shade(shape const& mat, ray const& r);
        void set_scene(scene const& s);
        color raytrace(ray const& r);


    private:
        scene scene_;

};

#endif // RENDERER_H
