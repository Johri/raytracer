#ifndef BUW_PIXEL_HPP
#define BUW_PIXEL_HPP

// header, system
#include <iosfwd>

// header, project
#include <color.hpp>


class pixel {
public : // c'tor

  pixel(std::size_t = 0, std::size_t = 0);
  ~pixel();

public : // methods

  void print(std::ostream&) const;

public : // member

  std::size_t x;
  std::size_t y;
  color       rgb;
};

std::ostream& operator<<(std::ostream&, const pixel&);

#endif // BUW_PIXEL_HPP
