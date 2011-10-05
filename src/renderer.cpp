#include "renderer.hpp"
#include "scene.hpp"
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



bool
renderer::delta(shape const& shap, ray const& r, light const& l)
{

    point3d ra (r.getSchnitt(shap.intersect(r)));
    ray rl(l.get_location(), ra);

    for(std::list<shape*>::iterator i=scene_.shapes_.begin(); i!=scene_.shapes_.end(); ++i)
    {
        if (shap.get_name() == (*i)->get_name()) {
          continue;
        }

        if( ((**i).intersect(rl)>0)&&((**i).intersect(rl)<=length_two_points(ra, l.get_location())) )
        {
            return false;
        }
    }
    return true;
}



point3d
renderer::reflector(shape const& shap, ray const& ray, light const& l)
{
    point3d r=normalize(ray.getSchnitt(shap.intersect(ray))-l.get_location())-2*scaleproduct(shap.make_normal(ray.getSchnitt(shap.intersect(ray))), normalize(ray.getSchnitt(shap.intersect(ray))-l.get_location()))*shap.make_normal(ray.getSchnitt(shap.intersect(ray)));
    return r;
}



color
renderer::refrection(shape const& shap, ray const& ra)
{/*
    color mc;
    double n1=1.0;
    double n2=shap.get_material().get_dansity();

    math3d::point3d i=normalize(ra.getSchnitt(shap.intersect(ra))-ra.getOrigin());
    math3d::point3d n=shap.make_normal(ra.getSchnitt(shap.intersect(ra)));

    math3d::point3d t=((n1/n2)*(i-n*scaleproduct(n,i)))-n * sqrt(1-((pow(n1,2)*(1-pow(scaleproduct(n,i),2))))/pow(n2,2));

    double d;

    ray mr(ra.getSchnitt(shap.intersect(ra)), ra.getSchnitt(shap.intersect(ra))+t);

for (std::list<light>::iterator il=scene_.lights_.begin(); il!=scene_.lights_.end(); ++il)
{

    for(std::list<shape*>::iterator i=scene_.shapes_.begin(); i!=scene_.shapes_.end(); ++i)
    {

        if( ((**i).intersect(mr)>0)&&((**i).intersect(mr)<=10000) )
        {



            d = delta((**i), mr, (*il));
            mc= (*i)->get_material().get_ambient() + ((*i)->get_material().get_diffuse() + (*i)->get_material().get_specular())  * d;
            mc= mc*pow(std::max(0.0,scaleproduct(t, normalize(ra.getDir()))),(**i).get_material().get_reflectivity());
            return mc;

        }
        else
        {

        }
    }

    }
    return mc;
    */
}



color
renderer::mirror(shape const& shap, ray const& ra)
{
    color mc;

    double d;

    math3d::point3d i=normalize(ra.getSchnitt(shap.intersect(ra))-ra.getOrigin());
    math3d::point3d n=shap.make_normal(ra.getSchnitt(shap.intersect(ra)));
    math3d::point3d r=i-2*scaleproduct(n, i)*n;

    ray mr(ra.getSchnitt(shap.intersect(ra)), ra.getSchnitt(shap.intersect(ra))+r);

/*
    for(int timer=0;timer!=10;++timer)
    {

        for(std::list<shape*>::iterator i=scene_.shapes_.begin(); i!=scene_.shapes_.end(); ++i)
        {

            if( ((**i).intersect(mr)>0)&&((**i).intersect(mr)<=10000) )
            {

                mc=shade((**i), mr);
                return mc;

            }
            else
            {
                return mc;
            }
        }
    }
*/



/*
    for (std::list<light>::iterator il=scene_.lights_.begin(); il!=scene_.lights_.end(); ++il)
    {

        for(std::list<shape*>::iterator i=scene_.shapes_.begin(); i!=scene_.shapes_.end(); ++i)
        {

            if( ((**i).intersect(mr)>0)&&((**i).intersect(mr)<=10000) )
            {



                d = delta((**i), mr, (*il));
                mc= (*i)->get_material().get_ambient() + ((*i)->get_material().get_diffuse() + (*i)->get_material().get_specular()) *d;
                mc= mc*pow(std::max(0.0,scaleproduct(r, normalize(ra.getDir()))),(**i).get_material().get_reflectivity());
                return mc;


            }
            else
            {
                //return mc;
            }
        }

    }

    //return mc;
*/
}




color
renderer::shade(shape const& shap, ray const& r)
{
    color ambient;
    color diffuse;
    color specular;
    double opacity=shap.get_material().get_opacity();
    double d;

    for (std::list<light>::iterator i=scene_.lights_.begin(); i!=scene_.lights_.end(); ++i)
    {




    d = delta(shap, r,(*i));

    math3d::point3d Schnittpunkt=r.getSchnitt(shap.intersect(r));

    ambient+= i->get_ambient() * shap.get_material().get_ambient();
    diffuse+= (i->get_diffuse()  * shap.get_material().get_diffuse() * std::max(0.0,(scaleproduct(normalize(i->get_location()-Schnittpunkt),shap.make_normal(Schnittpunkt)))))*d;
    specular+= (shap.get_material().get_specular() * pow(std::max(0.0,scaleproduct(reflector(shap, r, (*i)), normalize(-r.getDir()))),shap.get_material().get_reflectivity()))*d;




    }

    color mirror_= mirror(shap, r);//*delta(shap,r,);

    color refrection_= refrection(shap, r);


    color clr = ambient + (diffuse*0.8 + specular*0.2);// + mirror_*0.1);// + refrection_*opacity);

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
    shape* nearest_shape=0;
        for(std::list<shape*>::iterator i=scene_.shapes_.begin(); i!=scene_.shapes_.end(); ++i)
        {
            if(((*i)->intersect(r)<border)&&((*i)->intersect(r)>0)&&((*i)->intersect(r)<d))
            {
                d=(*i)->intersect(r);
                //c=color((*i)->get_material().get_ambient());
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
