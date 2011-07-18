// header i/f
#include "ppmwriter.hpp"

// header, system
#include <iostream>
#include <fstream>
#include <cmath>


////////////////////////////////////////////////////////////////////////////////
ppmwriter::ppmwriter(std::size_t w, std::size_t h, std::string const& file)
  : file_(file),
    width_(w),
    height_(h) {
  data_.resize(w * h * (sizeof(color)/sizeof(color::value_t)));
}


////////////////////////////////////////////////////////////////////////////////
ppmwriter::ppmwriter(std::size_t w, std::size_t h)
  : file_("untitled.ppm"),
    width_(w),
    height_(h) {
  data_.resize(w*h*(sizeof(color)/sizeof(color::value_t)));
}


////////////////////////////////////////////////////////////////////////////////
ppmwriter::~ppmwriter()
{}


////////////////////////////////////////////////////////////////////////////////
void ppmwriter::write(pixel const& p)
{
  size_t buf_pos = width_* (width_-1-p.y) + p.x;
  std::size_t pos = (sizeof(color)/sizeof(color::value_t)) * buf_pos;
  if (pos + ((sizeof(color)/sizeof(color::value_t)) - 1) > data_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error ppmwriter::write(pixel p) : Critical write position\n";
  } else {
    data_[pos] = (unsigned int)std::max(0.0, std::min(255.0 * p.rgb[0], 255.0));
    data_[pos+1] = (unsigned int)std::max(0.0, std::min(255.0 * p.rgb[1], 255.0));
    data_[pos+2] = (unsigned int)std::max(0.0, std::min(255.0 * p.rgb[2], 255.0));
  }
}


////////////////////////////////////////////////////////////////////////////////
void ppmwriter::save(std::string const& file)
{
  file_ = file;
  save();
}


////////////////////////////////////////////////////////////////////////////////
void ppmwriter::save()
{
  const std::size_t line_length = 18;

  std::fstream file(file_.c_str(), std::ios::out);
  file.clear();
  file << "P3 "
       << (unsigned int)width_ << " "
       << (unsigned int)height_ << " "
       << 255 << " \n";

  std::size_t pos = 1;
  for (std::vector<unsigned int>::iterator i = data_.begin();
       i < data_.end();
       ++i, ++pos)
    {
      file << (int)*i << " ";
      if (pos > line_length) {
	file << "\n";
	pos=0;
      }
    }

  file.close();
}
