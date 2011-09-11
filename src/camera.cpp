#include "camera.hpp"
#include "ray.hpp"

camera::camera()
:name_("stdandart camera"), location_(0,0,0), fov_x_(45)
{
    //ctor
}

camera::camera(std::string name, point3d const& loc, double fov)
:name_(name), location_(0,0,0), fov_x_(45)
{
    //ctor
}

camera::~camera()
{
    //dtor
}



ray const&
calc_eye_ray(unsigned int x, unsigned int y)
{
    ray r;
    return r;
}



void
camera::print_on(std::ostream& str) const
{
	str <<"CAMERA"<<"\n"<<"   Name: "<< name_<<"\n"<<"   Location: "<<location_<<"   Field of View: "<<fov_x_<<"\n"<<std::flush;
}


std::ostream& operator <<(std::ostream& str, camera const& c)
{
	c.print_on(str);
	return str;
}
