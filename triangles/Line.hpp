#ifndef __LINE_HPP__
#define __LINE_HPP__

struct Line;

#include "Vector3.hpp"

// Представляет отрезок (луч. прямую) в виде r = r_0 + tl, inf <= t1 < t < t2 <= inf
struct Line
{
    Vector3 r_0;
    Vector3 l;
    float t1_ = -INFINITY;
    float t2_ = INFINITY;

    Line ();
    Line (Vector3 &r_0, Vector3 &l, float t1, float t2);
    Line (Vector3 &r_0, Vector3 &l);

    #if 0
    void intersectBy (const Triangle &triangle);
    #endif

    float getLineLineIntersection (const Vector3 &r, const Vector3 &vec) const;

};

#endif // !__LINE_HPP__