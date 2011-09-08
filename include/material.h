#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "color.h"

class material {

private: 
	std::string name_;
	color ka_;
	color ks_;
	color kd_;
	float m_;
	
public:
	material();
	material(std::string const& name, color const& ka, color const& ks, color const& kd, float m);
	material(material const& rhs);
	~material();
	std::string const& getName() const;
	color const& getKa() const;
	color const& getKs() const;
	color const& getKd() const;
	float getM() const;
	void print_on(std::ostream& str) const;
};
std::ostream& operator <<(std::ostream& str, material const& mat);

#endif

