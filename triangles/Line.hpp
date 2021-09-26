#ifndef __LINE_HPP__
#define __LINE_HPP__

struct Line;

#include "Point.hpp"

// Представляет отрезок (луч. прямую) в виде r = r_0 + tl, inf <= t1 < t < t2 <= inf
struct Line
{
    Point r_0;
    Point l;
    float t1 = -INFINITY;
    float t2 = INFINITY;

    Line ();
    Line (Point &r_0, Point &l, float t1 = -INFINITY, float t2 = INFINITY);

};

#endif // !__LINE_HPP__