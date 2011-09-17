#include "renderer.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "color.hpp"
#include "material.hpp"

renderer::renderer()
:scene_()
{
    //ctor
}


renderer::renderer(scene const& s)
:scene_(s)
{

}


renderer::~renderer()
{
    //dtor
}



point3d
renderer::reflector(shape const& shap, ray const& ray, light const& l)
{
    point3d r=normalize(ray.getSchnitt(shap.intersect(ray))-l.get_location())-2*scaleproduct(shap.make_normal(ray.getSchnitt(shap.intersect(ray))), normalize(ray.getSchnitt(shap.intersect(ray))-l.get_location()))*shap.make_normal(ray.getSchnitt(shap.intersect(ray)));
    return r;
}



color
renderer::shade(shape const& shap, ray const& r)
{
    light l (scene_.lights_.front());

//    color c (l.get_ambient() * mat.get_ambient());

    //die alte version
/*
    double ambient0=l.get_ambient()[0]*shap.get_material().get_ambient()[0]+l.get_defuse()[0]*(shap.get_material().get_defuse()[0] *scaleproduct(normalize(l.get_location()-r.getSchnitt(shap.intersect(r))), shap.make_normal(r.getSchnitt(shap.intersect(r))))+shap.get_material().get_specular()[0]*pow(scaleproduct(reflector(shap, r), normalize(-r.getDir())),shap.get_material().get_reflectivity()));
    double ambient1=l.get_ambient()[1]*shap.get_material().get_ambient()[1]+l.get_defuse()[1]*(shap.get_material().get_defuse()[1] *scaleproduct(normalize(l.get_location()-r.getSchnitt(shap.intersect(r))), shap.make_normal(r.getSchnitt(shap.intersect(r))))+shap.get_material().get_specular()[1]*pow(scaleproduct(reflector(shap, r), normalize(-r.getDir())),shap.get_material().get_reflectivity()));
    double ambient2=l.get_ambient()[2]*shap.get_material().get_ambient()[2]+l.get_defuse()[2]*(shap.get_material().get_defuse()[2] *scaleproduct(normalize(l.get_location()-r.getSchnitt(shap.intersect(r))), shap.make_normal(r.getSchnitt(shap.intersect(r))))+shap.get_material().get_specular()[2]*pow(scaleproduct(reflector(shap, r), normalize(-r.getDir())),shap.get_material().get_reflectivity()));
*/



    double ambient0=l.get_ambient()[0]*shap.get_material().get_ambient()[0];
    double defuse0=l.get_defuse()[0]*(shap.get_material().get_defuse()[0] *scaleproduct(normalize(l.get_location()-r.getSchnitt(shap.intersect(r))), shap.make_normal(r.getSchnitt(shap.intersect(r))))+shap.get_material().get_specular()[0]*pow(scaleproduct(reflector(shap, r, l), normalize(-r.getDir())),shap.get_material().get_reflectivity()));
    if(defuse0<0)
    {
        defuse0=0;
    }

    double ambient1=l.get_ambient()[1]*shap.get_material().get_ambient()[1];
    double defuse1=l.get_defuse()[1]*(shap.get_material().get_defuse()[1] *scaleproduct(normalize(l.get_location()-r.getSchnitt(shap.intersect(r))), shap.make_normal(r.getSchnitt(shap.intersect(r))))+shap.get_material().get_specular()[1]*pow(scaleproduct(reflector(shap, r, l), normalize(-r.getDir())),shap.get_material().get_reflectivity()));
    if(defuse1<0)
    {
        defuse1=0;
    }

    double ambient2=l.get_ambient()[2]*shap.get_material().get_ambient()[2];
    double defuse2=l.get_defuse()[2]*(shap.get_material().get_defuse()[2] *scaleproduct(normalize(l.get_location()-r.getSchnitt(shap.intersect(r))), shap.make_normal(r.getSchnitt(shap.intersect(r))))+shap.get_material().get_specular()[2]*pow(scaleproduct(reflector(shap, r, l), normalize(-r.getDir())),shap.get_material().get_reflectivity()));
    if(defuse2<0)
    {
        defuse2=0;
    }

    //if(normalize(l.get_location()-shap.())<=0&&normalize(l.get_location-shap.intersect())>1000)

    //color c (l.get_ambient()[0]*shap.get_material().get_ambient()[0]+l.get_defuse()[0]*shap.get_material().get_defuse()[0], l.get_ambient()[1]*shap.get_material().get_ambient()[1]+l.get_defuse()[1]*(shap.get_material().get_defuse()[1]), l.get_ambient()[2]*shap.get_material().get_ambient()[2]+l.get_defuse()[2]*(shap.get_material().get_defuse()[2]));
    color clr (ambient0+defuse0, ambient1+defuse1, ambient2+defuse2);
    //color clr (ambient0, ambient1, ambient2);
    //std::cout<<c<<std::endl;
    //std::cout<<clr<<std::endl;
    return clr;
}


void
renderer::set_scene(scene const& s)
{
    scene_=s;
}


color
renderer::raytrace(ray const& r)
{
    color c (0,0,0);
    double border=10000;
    double d=border;
        for(std::list<shape*>::iterator i=scene_.shapes_.begin(); i!=scene_.shapes_.end(); ++i)
        {
            if(((*i)->intersect(r)<border)&&((*i)->intersect(r)>0)&&((*i)->intersect(r)<d))
            {
                d=(*i)->intersect(r);
                c=color((*i)->get_material().get_ambient());
                //c=shade((*i)->get_material());
                c=shade(**i, r);
            }
        }
        if((d<border)&&(d>-1))
        {
            return c;
        }
        else
        {
            return color(0,0,0);
        }


}
