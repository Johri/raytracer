#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.hpp"
#include <iostream>
#include <string>


class material
{
    public:
        material();
        material(std::string const& name, color const& ambient, color const& defuse, color const& specular, float reflectivity);
        material(material const& copy);
        ~material();
        std::string const& getName() const;
        color const& get_ambient() const;
        color const& get_defuse() const;
        color const& get_specular() const;
        float get_reflectivity() const;
        void print_on(std::ostream& str) const;

    private:
    std::string name_;
    color ambient_;
    color defuse_;
    color specular_;
    float reflectivity_;

};

std::ostream& operator<<(std::ostream& str, material const& mtr);


#endif // MATERIAL_H
