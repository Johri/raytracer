

#include "scene.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "shape.hpp"
#include "tube.hpp"
#include "circle.hpp"



scene::scene()
:materials_(), shapes_(), camera_(), lights_()
{
    //ctor
}


scene::~scene()
{
    for(std::list<shape*>::iterator i=shapes_.begin(); i!=shapes_.end(); ++i)
    {
        delete *i;
    }

    //dtor
}


camera
scene::main_camera() const
{

    return camera_;
}


void
scene::load_sdf(std::string const& sdf)
{
     std::ifstream fs(sdf.c_str());

    if (fs.is_open())
    {

        std::string line;
        while(std::getline (fs, line))
        {
            std::stringstream ss;
            ss<<line;

            std::string sharp;
            std::string door;
        	std::string def;
        	std::string type;
        	std::string geo;
        	std::string name;
        	std::string mat_name;
        	std::string extra1="";
        	std::string extra2="";
        	std::string extra3="";
        	std::string extra4="";

            ss>>sharp;
            if(sharp=="#")
            {
                ss>>door;
                ss>>extra1;
                ss>>extra2;
                ss>>extra3;
                ss>>extra4;
                std::cout<<sharp<<" "<<door;
                if(extra1!="")
                {
                    std::cout<<" "<<extra1;

                    if(extra2!="")
                    {
                        std::cout<<" "<<extra2;

                        if(extra3!="")
                        {
                            std::cout<<" "<<extra3;

                            if(extra4!="")
                            {
                                std::cout<<" "<<extra4;
                            }
                        }
                    }
                }
                std::cout<<std::endl;


            }
            else
            {
                def=sharp;
                if(def=="define")
                {
                    ss>>type;
                    if (type=="material")
                    {
                        ss>>mat_name;
                        std::cout<<def<<" "<<type<<" "<<mat_name<<" ";
                        double kar;
                        ss>>kar;
                        std::cout<<kar<<" ";
                        double kag;
                        ss>>kag;
                        std::cout<<kag<<" ";
                        double kab;
                        ss>>kab;
                        std::cout<<kab<<" ";
                        double kdr;
                        ss>>kdr;
                        std::cout<<kdr<<" ";
                        double kdg;
                        ss>>kdg;
                        std::cout<<kdg<<" ";
                        double kdb;
                        ss>>kdb;
                        std::cout<<kdb<<" ";
                        double ksr;
                        ss>>ksr;
                        std::cout<<ksr<<" ";
                        double ksg;
                        ss>>ksg;
                        std::cout<<ksg<<" ";
                        double ksb;
                        ss>>ksb;
                        std::cout<<ksb<<" ";
                        double m;
                        ss>>m;
                        std::cout<<m<<std::endl;
                        color ka (kar, kag, kab);
                        color kd (kdr, kdg, kdb);
                        color ks (ksr, ksg, ksb);
                        materials_[mat_name.c_str()] = material(mat_name, ka, kd, ks, m);
                    }
                    else
                    {
                        if (type=="shape")
                        {
                            ss>>geo;
                            if(geo=="box")
                            {
                                ss>>name;
                                std::cout<<def<<" "<<type<<" "<<geo<<" "<<name<<" ";
                                double p1x;
                                ss>>p1x;
                                std::cout<<p1x<<" ";
                                double p1y;
                                ss>>p1y;
                                std::cout<<p1y<<" ";
                                double p1z;
                                ss>>p1z;
                                std::cout<<p1z<<" ";
                                double p2x;
                                ss>>p2x;
                                std::cout<<p2x<<" ";
                                double p2y;
                                ss>>p2y;
                                std::cout<<p2y<<" ";
                                double p2z;
                                ss>>p2z;
                                std::cout<<p2z<<" ";

                                ss>>mat_name;
                                std::cout<<mat_name<<std::endl;
                                point3d p1_ (p1x, p1y, p1z);
                                point3d p2_ (p2x, p2y, p2z);
                                shape* b = new box (name, materials_[mat_name], p1_, p2_);
                                shapes_.push_back(b);
                            }
                            else
                            {
                                if(geo=="sphere")
                                {
                                    ss>>name;
                                    std::cout<<def<<" "<<type<<" "<<geo<<" "<<name<<" ";
                                    double x;
                                    ss>>x;
                                    std::cout<<x<<" ";
                                    double y;
                                    ss>>y;
                                    std::cout<<y<<" ";
                                    double z;
                                    ss>>z;
                                    std::cout<<z<<" ";
                                    double radius;
                                    ss>>radius;
                                    std::cout<<radius<<" ";

                                    ss>>mat_name;
                                    std::cout<<mat_name<<std::endl;
                                    shape* s = new sphere(name, materials_[mat_name], radius,point3d(x,y,z));
                                    shapes_.push_back(s);
                                }
                                else
                                {
                                    if(geo=="triangle")
                                    {
                                        ss>>name;
                                        std::cout<<def<<" "<<type<<" "<<geo<<" "<<name<<" ";
                                        double x1;
                                        ss>>x1;
                                        std::cout<<x1<<" ";
                                        double y1;
                                        ss>>y1;
                                        std::cout<<y1<<" ";
                                        double z1;
                                        ss>>z1;
                                        std::cout<<z1<<" ";
                                        double x2;
                                        ss>>x2;
                                        std::cout<<x2<<" ";
                                        double y2;
                                        ss>>y2;
                                        std::cout<<y2<<" ";
                                        double z2;
                                        ss>>z2;
                                        std::cout<<z2<<" ";
                                        double x3;
                                        ss>>x3;
                                        std::cout<<x3<<" ";
                                        double y3;
                                        ss>>y3;
                                        std::cout<<y3<<" ";
                                        double z3;
                                        ss>>z3;
                                        std::cout<<z3<<" ";

                                        ss>>mat_name;
                                        std::cout<<mat_name<<std::endl;
                                        shape* t = new triangle (name, materials_[mat_name], point3d(x1, y1, z1), point3d(x2, y2, z2), point3d(x3, y3, z3));
                                        shapes_.push_back(t);
                                    }
                                    else
                                    {
                                        if(geo=="tube")
                                        {
                                            ss>>name;
                                            std::cout<<def<<" "<<type<<" "<<geo<<" "<<name<<" ";
                                            double x1;
                                            ss>>x1;
                                            std::cout<<x1<<" ";
                                            double y1;
                                            ss>>y1;
                                            std::cout<<y1<<" ";
                                            double z1;
                                            ss>>z1;
                                            std::cout<<z1<<" ";
                                            double x2;
                                            ss>>x2;
                                            std::cout<<x2<<" ";
                                            double y2;
                                            ss>>y2;
                                            std::cout<<y2<<" ";
                                            double z2;
                                            ss>>z2;
                                            std::cout<<z2<<" ";
                                            double r;
                                            ss>>r;
                                            std::cout<<r<<" ";
                                            ss>>mat_name;
                                            std::cout<<mat_name<<std::endl;
                                            shape* tu = new tube (name, materials_[mat_name], point3d(x1, y1, z1), point3d(x2, y2, z2), r);
                                            shapes_.push_back(tu);
                                        }
                                        else
                                        {
                                            if(geo=="circle")
                                            {
                                                ss>>name;
                                                std::cout<<def<<" "<<type<<" "<<geo<<" "<<name<<" ";
                                                double x1;
                                                ss>>x1;
                                                std::cout<<x1<<" ";
                                                double y1;
                                                ss>>y1;
                                                std::cout<<y1<<" ";
                                                double z1;
                                                ss>>z1;
                                                std::cout<<z1<<" ";
                                                double x2;
                                                ss>>x2;
                                                std::cout<<x2<<" ";
                                                double y2;
                                                ss>>y2;
                                                std::cout<<y2<<" ";
                                                double z2;
                                                ss>>z2;
                                                std::cout<<z2<<" ";
                                                double x3;
                                                ss>>x3;
                                                std::cout<<x3<<" ";
                                                double y3;
                                                ss>>y3;
                                                std::cout<<y3<<" ";
                                                double z3;
                                                ss>>z3;
                                                std::cout<<z3<<" ";
                                                ss>>mat_name;
                                                std::cout<<mat_name<<std::endl;
                                                shape* c = new circle (name, materials_[mat_name], point3d(x1, y1, z1), point3d(x2, y2, z2), point3d(x3, y3, z3));
                                                shapes_.push_back(c);
                                            }
                                        }
                                    }
                                }
                            }

                        }
                        else
                        {
                            if(type=="light")
                            {
                                ss>>name;
                                std::cout<<def<<" "<<type<<" "<<name<<" ";
                                double x;
                                ss>>x;
                                std::cout<<x<<" ";
                                double y;
                                ss>>y;
                                std::cout<<y<<" ";
                                double z;
                                ss>>z;
                                std::cout<<z<<" ";
                                double Lar;
                                ss>>Lar;
                                std::cout<<Lar<<" ";
                                double Lag;
                                ss>>Lag;
                                std::cout<<Lag<<" ";
                                double Lab;
                                ss>>Lab;
                                std::cout<<Lab<<" ";
                                double Ldr;
                                ss>>Ldr;
                                std::cout<<Ldr<<" ";
                                double Ldg;
                                ss>>Ldg;
                                std::cout<<Ldg<<" ";
                                double Ldb;
                                ss>>Ldb;
                                std::cout<<Ldb<<std::endl;
                                light l (name, point3d(x,y,z), color(Lar,Lag,Lab), color(Ldr,Ldg,Ldb));
                                lights_.push_back(l);
                            }
                            else
                            {
                                if(type=="camera")
                                {
                                    ss>>name;
                                    std::cout<<def<<" "<<type<<" "<<name<<" ";
                                    double x;
                                    ss>>x;
                                    double y;
                                    ss>>y;
                                    double z;
                                    ss>>z;
                                    int pixel_x;
                                    ss>>pixel_x;
                                    int pixel_y;
                                    ss>>pixel_y;
                                    double fov;
                                    ss>>fov;
                                    std::cout<<x<<" "<<y<<" "<<z<<" "<<pixel_x<<" "<<pixel_y<<" "<<fov<<std::endl;
                                    camera c (name, point3d(x,y,z), pixel_x, pixel_y, fov);
                                    camera_=c;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(def=="render")
                    {
                        std::string wtr;
                        ss>>wtr;
                        std::cout<<def<<" "<<wtr<<" ";
                        std::string img;
                        ss>>img;
                        std::cout<<img<<" ";
                        int res_x;
                        ss>>res_x;
                        int res_y;
                        ss>>res_y;
                        std::cout<<res_x<<" "<<res_y<<std::endl;
                        img_name_=name;
                        img_cam_=wtr;
                        img_res_x_=res_x;
                        img_res_y_=res_y;
                        // camera.set_width(res_x)
                        // camera.set_height(res_y)
                    }
                }
            }
            ss.clear();
    }
    std::cout<<"\n"<<"\n"<<std::endl;

    for(std::map<std::string, material>::iterator i=materials_.begin(); i!=materials_.end(); ++i)
    {
        std::cout<<i->first<<" "<<i->second<<std::endl;
    }

    for(std::list<shape*>::iterator i=shapes_.begin(); i!=shapes_.end(); ++i)
    {
        std::cout<<**i<<std::endl;
    }

    for(std::list<light>::iterator i=lights_.begin(); i!=lights_.end(); ++i)
    {
        std::cout<<*i<<std::endl;
    }

    std::cout<<camera_<<std::endl;


    }
    fs.close();

}
