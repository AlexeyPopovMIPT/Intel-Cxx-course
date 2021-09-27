#include "Triangle.hpp"

Triangle::Triangle (Vector3 &a, Vector3 &b, Vector3 &c):
    p1(a),
    p2(b),
    p3(c),
    side1(b-a),
    side2(c-b),
    side3(a-c)
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

    if (intersects(other))
        return INTERSECT;
    else
        return NOT_INTERSECT;
}

bool Triangle::intersects (const Triangle &other) const
{
    Line intersectLine = other.plane * plane;


    // получить отрезок внутри одного треугольника и внутри другого.
    // return отрезки пересекаются
}

void Triangle::intersectLine (Line &line) const
{
    float t1,t2,t3;

    // решаем уравнение t1 * l + q * triangle.side1 = r относительно t1
    t1 = line.getLineLineIntersection (p1 - line.r_0, side1);
    t2 = line.getLineLineIntersection (p2 - line.r_0, side2);
    t3 = line.getLineLineIntersection (p3 - line.r_0, side3);

    // находим радиусы-векторы точек пересечения

    Vector3 int1 = line.l * t1 + line.r_0,
            int2 = line.l * t2 + line.r_0,
            int3 = line.l * t3 + line.r_0;

    

    // Линия пересекает сторону side1 внутри треугольника, если и только если (p1 - int1) сонаправлена (int1 - p2)

    if (isZero(t1-t2))
        line.t1_ = (line.t2_ = t1);
    
    else if (isZero(t2-t3))
        line.t1_ = (line.t2_ = t2);

    else if (isZero(t1-t3))
        line.t1_ = (line.t2_ = t3);

    else
    {

    }



}



inline const Vector3& Triangle::getP1 () const { return p1; }
inline const Vector3& Triangle::getP2 () const { return p2; }
inline const Vector3& Triangle::getP3 () const { return p3; }
inline const Vector3& Triangle::getSide1 () const { return side1; }
inline const Vector3& Triangle::getSide2 () const { return side2; }
inline const Vector3& Triangle::getSide3 () const { return side3; }
