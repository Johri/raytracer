#ifndef MATERIAL_MAP_H
#define MATERIAL_MAP_H

#include <map>
#include "material.hpp"


class material_map
{
    public:
        material_map();
        material_map(std::map<std::string, material*> const& material_map);
        ~material_map();
        int size() const;
        void add(std::string const&, material*);
        void remove(std::string const&);
        material* get(std::string const&) const;
        void get_all() const;

    private:
    std::map<std::string, material*> material_map_;
};

#endif // MATERIAL_MAP_H
