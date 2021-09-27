#ifndef __PLANE_HPP__
#define __PLANE_HPP__

struct Plane;

#include "Vector3.hpp"
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


    Vector3 r_0;
    Vector3 normal;

    void constructFrom (const Vector3 a, const Vector3 b, const Vector3 c);

    Point_rl_Plane_t determineRelative (const Vector3 &other) const;

    Line operator* (const Plane &other) const;

};


#endif // !__PLANE_HPP__