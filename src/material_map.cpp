#include "material_map.hpp"

material_map::material_map()
{
    //ctor
}

material_map::material_map(std::map<std::string, material*> const& material_map)
:material_map_(material_map)
{

}


material_map::~material_map()
{
    //dtor
}


int
material_map::size() const
{
    return material_map_.size();
}


void
material_map::add (std::string const& str, material* mat)
{
    material_map_.insert(std::pair <std::string, material*> (str, mat));
}


void
material_map::remove (std::string const& str)
{
    material_map_.erase(material_map_.find(str));
}


material*
material_map::get (std::string const& str) const
{
    std::map<std::string, material*>::const_iterator i=material_map_.find(str);

    if(i!=material_map_.end())
    return i->second;

    else
    return 0;
}


void
material_map::get_all() const
{
    std::cout<<std::endl;
    int counter=1;
    for(std::map<std::string, material*>::const_iterator i=material_map_.begin(); i!=material_map_.end();++i)
    {
        std::cout<<counter<<") "<<i->first<<": ("<<i->second->get_ambient()[0]<<", "<<i->second->get_ambient()[1]<<", "<<i->second->get_ambient()[2]<<", "<<i->second->get_defuse()[0]<<", "<<i->second->get_defuse()[1]<<", "<<i->second->get_defuse()[2]<<", "<<i->second->get_specular()[0]<<", "<<i->second->get_specular()[1]<<", "<<i->second->get_specular()[2]<<", "<<i->second->get_reflectivity()<<")"<<std::endl;
        counter++;
    }
}
