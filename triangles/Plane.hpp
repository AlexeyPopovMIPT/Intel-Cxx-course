#ifndef __PLANE_HPP__
#define __PLANE_HPP__

struct Plane;

#include "Point.hpp"
#include "Triangle.hpp"
#include "Line.hpp"

struct Plane
{
    typedef enum PointRelativelyToPlane
    {
        UPPER = 0,
        LOWER = 1,
        ON_PLANE = 2
    } 
        Point_rl_Plane_t;


    Point r_0;
    Point normal;

    void constructFrom (const Point a, const Point b, const Point c);

    Point_rl_Plane_t determineRelative (const Point &other) const;

    Line operator* (const Plane &other) const;

};


#endif // !__PLANE_HPP__