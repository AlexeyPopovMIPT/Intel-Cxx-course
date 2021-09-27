#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

class Triangle;

#include "Vector3.hpp"
#include "Plane.hpp"
#include "Line.hpp"

class Triangle
{
    Vector3 p1, p2, p3;
    Vector3 side1, side2, side3;

    Plane plane;

    bool intersects (const Triangle &other) const;

public:

    typedef enum TriangleRelativelyToTriangle
    {
        UPPER = 0,
        LOWER = 1,
        INTERSECT = 2,
        NOT_INTERSECT = 3
    } 
        Triangle_rl_Triangle_t;


    Triangle (Vector3 &a, Vector3 &b, Vector3 &c);

    Triangle_rl_Triangle_t determineRelative (const Triangle &other) const;

    void intersectLine (Line &line) const;

    inline const Vector3& getP1 () const;
    inline const Vector3& getP2 () const;
    inline const Vector3& getP3 () const;

    inline const Vector3& getSide1 () const;
    inline const Vector3& getSide2 () const;
    inline const Vector3& getSide3 () const;

};

#endif // !__TRIANGLE_HPP__
