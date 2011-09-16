#ifndef BUW_RGB_HPP
#define BUW_RGB_HPP

// header, system
#include <iosfwd>


class color {
public : // enums, typedefs

  typedef float value_t;

public : // c'tor
  color   ();
  color   ( color const& );
  color   ( value_t r, value_t g, value_t b );

  ~color  ();

public : // methods
  void            swap        ( color& );
  void            print       ( std::ostream& os ) const;

  value_t&        operator[]  ( unsigned component );
  const value_t&  operator[]  ( unsigned component ) const;

  color&          operator=   ( const color& );
  void            operator+=  ( const color& );

  color           operator*=   ( const color& );


private: // members
  value_t data_[3]; // rgb
};

color operator*(const color& a, const color& b);
color operator+(const color& a, const color& b);
std::ostream& operator<<(std::ostream& os, color const&);

#endif // BUW_RGB_HPP
