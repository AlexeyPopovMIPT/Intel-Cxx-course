#ifndef __POINT_HPP__
#define __POINT_HPP__


#include <math.h> // for NAN
#include "float_traits.hpp"


struct Point
{
    float x = NAN, y = NAN, z = NAN;

    inline bool isZeroPoint() const;

    float operator* (const Point& rhs) const;

    Point operator- (const Point& rhs) const;

    Point operator+ (const Point& rhs) const;

    Point operator* (const float  rhs) const;

    Point vectorMul (const Point& rhs) const;
};


#endif // !__POINT_HPP__
