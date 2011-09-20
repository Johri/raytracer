#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.hpp"
#include <iostream>
#include <string>


class material
{
    public:
        material();
        material(std::string const& name, color const& ambient, color const& diffuse, color const& specular, float reflectivity, float opacity, float dansity);
        material(material const& copy);
        ~material();
        std::string const& getName() const;
        color const& get_ambient() const;
        color const& get_diffuse() const;
        color const& get_specular() const;
        float get_reflectivity() const;
        float get_opacity() const;
        float get_dansity() const;
        void print_on(std::ostream& str) const;

    private:
    std::string name_;
    color ambient_;
    color diffuse_;
    color specular_;
    float reflectivity_;
    float opacity_;
    float dansity_;

};

std::ostream& operator<<(std::ostream& str, material const& mtr);


#endif // MATERIAL_H
