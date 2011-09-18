#include "camera.hpp"
#include "ray.hpp"
#include "point3d.hpp"
#include <cmath>
#include <iostream>

camera::camera()
:name_("stdandart camera"), location_(0,0,0), width_(500), heigth_(500), fov_x_(45), d_(get_d())
{

}

camera::camera(std::string name, point3d const& loc, double w, double h, double fov)
:name_(name), location_(loc), width_(w), heigth_(h), fov_x_(fov), d_(get_d())
{
    //ctor
}

camera::~camera()
{
    //dtor
}



double
camera::get_d()
{
    d_=-1/(tan(fov_x_/2));
    return d_;
}


ray
camera::calc_eye_ray(double x,double y) const
{
    double x_=(x/width_*2)-1;
    double y_=(heigth_/width_)*(y/heigth_*2)-(heigth_/width_);
    point3d p (x_,y_,d_);
    //normalize (p);
    ray r (location_, p);
    return r;
}


void
camera::print_on(std::ostream& str) const
{
	str <<"CAMERA"<<"\n"<<"   Name: "<< name_<<"\n"<<"   Location: "<<location_<<"   Field of View: "<<fov_x_<<"\n"<<"   d: "<<d_<<"\n"<<std::flush;
}


std::ostream& operator <<(std::ostream& str, camera const& c)
{
	c.print_on(str);
	return str;
}
