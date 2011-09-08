

#include "scene.hpp"



scene::scene()
  : materials_()// initializer_list
{
    std::cerr << "Hallo Martin: initializer_list !!!" << std::endl;
    //ctor
}

scene::~scene()
{
    std::cerr << "Error: shapes not deleted" << std::endl;
    //dtor
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
                        ss>>name;
                        std::cout<<def<<" "<<type<<" "<<name<<" ";
                        int kar;
                        ss>>kar;
                        std::cout<<kar<<" ";
                        int kag;
                        ss>>kag;
                        std::cout<<kag<<" ";
                        int kab;
                        ss>>kab;
                        std::cout<<kab<<" ";
                        int kdr;
                        ss>>kdr;
                        std::cout<<kdr<<" ";
                        int kdg;
                        ss>>kdg;
                        std::cout<<kdg<<" ";
                        int kdb;
                        ss>>kdb;
                        std::cout<<kdb<<" ";
                        int ksr;
                        ss>>ksr;
                        std::cout<<ksr<<" ";
                        int ksg;
                        ss>>ksg;
                        std::cout<<ksg<<" ";
                        int ksb;
                        ss>>ksb;
                        std::cout<<ksb<<" ";
                        int m;
                        ss>>m;
                        std::cout<<m<<std::endl;
                        color ka (kar, kag, kab);
                        color kd (kdr, kdg, kdb);
                        color ks (ksr, ksg, ksb);
                        materials_["mtr"] = material(name, ka, kd, ks, m);
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
                                std::string mat_name;
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
                                    std::string clr;
                                    ss>>clr;
                                    std::cout<<clr<<std::endl;
                                    shape* s = new sphere(name, materials_[clr], radius,point3d(x,y,z));
                                    shapes_.push_back(s);
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
                                float Lar;
                                ss>>Lar;
                                std::cout<<Lar<<" ";
                                float Lag;
                                ss>>Lag;
                                std::cout<<Lag<<" ";
                                float Lab;
                                ss>>Lab;
                                std::cout<<Lab<<" ";
                                float Ldr;
                                ss>>Ldr;
                                std::cout<<Ldr<<" ";
                                float Ldg;
                                ss>>Ldg;
                                std::cout<<Ldg<<" ";
                                float Ldb;
                                ss>>Ldb;
                                std::cout<<Ldb<<std::endl;
                            }
                            else
                            {
                                if(type=="camera")
                                {
                                    ss>>name;
                                    std::cout<<def<<" "<<type<<" "<<name<<" ";
                                    float fov;
                                    ss>>fov;
                                    std::cout<<fov<<std::endl;
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
                        int pixels_higth;
                        ss>>pixels_higth;
                        int pixels_width;
                        ss>>pixels_width;
                        std::cout<<pixels_higth<<" "<<pixels_width<<std::endl;
                    }
                }
            }
            ss.clear();
    }
    std::cout<<"\n"<<"\n"<<std::endl;



    }
    fs.close();

}
