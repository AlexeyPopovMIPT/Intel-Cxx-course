#include "Triangle.hpp"

Triangle::Triangle (Point &a, Point &b, Point &c):
    p1(a),
    p2(b),
    p3(c)
{
    plane.constructFrom(a,b,c);
}

Triangle::Triangle_rl_Triangle_t Triangle::determineRelative (const Triangle &other) const
{
    Plane::Point_rl_Plane_t p1_rl = plane.determineRelative (other.p1),
                            p2_rl = plane.determineRelative (other.p2),
                            p3_rl = plane.determineRelative (other.p3);

    switch (p1_rl & p2_rl & p3_rl)
    {
        case Plane::Point_rl_Plane_t::UPPER: return UPPER;
        case Plane::Point_rl_Plane_t::LOWER: return LOWER;
    }


    // могут пересечься

    if (intersect(other))
        return INTERSECT;
    else
        return NOT_INTERSECT;
}

bool Triangle::intersect (const Triangle &other) const
{
    Line intersectLine = other.plane * plane;
    // получить отрезок внутри одного треугольника и внутри другого.
    // return отрезки пересекаются
}