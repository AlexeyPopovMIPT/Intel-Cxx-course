#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

class Triangle;

#include "Point.hpp"
#include "Plane.hpp"

class Triangle
{
    Point p1, p2, p3;

    Plane plane;

    bool intersect (const Triangle &other) const;

public:

    typedef enum TriangleRelativelyToTriangle
    {
        UPPER = 0,
        LOWER = 1,
        INTERSECT = 2,
        NOT_INTERSECT = 3
    } 
        Triangle_rl_Triangle_t;


    Triangle (Point &a, Point &b, Point &c);

    Triangle_rl_Triangle_t determineRelative (const Triangle &other) const;

};

#endif // !__TRIANGLE_HPP__
