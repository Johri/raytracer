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



color
renderer::shade(shape const& shap, ray const& r)
{
    light l (scene_.lights_.front());

//    color c (l.get_ambient() * mat.get_ambient());
    //double first=l.get_ambient()[0]*shap.get_material().get_ambient()[0]+l.get_defuse()[0]*(shap.get_material().get_defuse()[0]); //*scaleproduct((normalize(l.get_location()), shap.make_normal(r.getSchnitt(shap.intersect(r)))));
    //double second=l.get_ambient()[1]*shap.get_material().get_ambient()[1]+l.get_defuse()[1]*(shap.get_material().get_defuse()[1]); // *scaleproduct((normalize(l.location()), normalize(shap.get_normal("schnittpunkt mit dem shape"))));
    //double third=l.get_ambient()[2]*shap.get_material().get_ambient()[2]+l.get_defuse()[2]*(shap.get_material().get_defuse()[2]); // *scaleproduct((normalize(l.location()), normalize(shap.get_normal("schnittpunkt mit dem shape"))));
    //if(normalize(l.get_location()-shap.())<=0&&normalize(l.get_location-shap.intersect())>1000)

    color c (l.get_ambient()[0]*shap.get_material().get_ambient()[0]+l.get_defuse()[0]*(shap.get_material().get_defuse()[0]), l.get_ambient()[1]*shap.get_material().get_ambient()[1]+l.get_defuse()[1]*(shap.get_material().get_defuse()[1]), l.get_ambient()[2]*shap.get_material().get_ambient()[2]+l.get_defuse()[2]*(shap.get_material().get_defuse()[2]));
    //color clr (first, second, third);
    //std::cout<<c<<std::endl;
    //std::cout<<clr<<std::endl;
    return c;
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
