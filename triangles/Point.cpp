#include "Point.hpp"

inline bool Point::isZeroPoint() const { return isZero(x) && isZero(y) && isZero(z); }

float Point::operator* (const Point& rhs) const 
{
    return x*rhs.x + y*rhs.y + z*rhs.z; 
}

Point Point::operator- (const Point& rhs) const
{
    return Point {x-rhs.x, y-rhs.y, z-rhs.z};
}

Point Point::operator+ (const Point& rhs) const
{
    return Point {x+rhs.x, y+rhs.y, z+rhs.z};
}

Point Point::operator* (const float  rhs) const 
{
    return Point {x*rhs, y*rhs, z*rhs}; 
}

Point Point::vectorMul (const Point& rhs) const
{
    return Point
    {
        y*rhs.z - z*rhs.y,
        z*rhs.x - x*rhs.z,
        x*rhs.y - y*rhs.x
    };
}
