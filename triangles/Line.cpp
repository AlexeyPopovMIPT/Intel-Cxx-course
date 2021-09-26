#include "Line.hpp"

Line::Line (Point &r_0, Point &l, float t1 /* = -INFINITY */, float t2 /* = INFINITY */):
    r_0(r_0),
    l(l),
    t1(t1),
    t2(t2)
{}

Line::Line () {}

