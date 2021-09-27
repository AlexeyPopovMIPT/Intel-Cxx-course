#include "Line.hpp"
#include <math.h>

Line::Line (Vector3 &r_0, Vector3 &l, float t1, float t2):
    r_0(r_0),
    l(l),
    t1_(t1),
    t2_(t2)
{}

Line::Line (Vector3 &r_0, Vector3 &l):
    r_0(r_0),
    l(l)
{}


Line::Line () {}

// Возвращает параметр t, который нужно подставить в this, чтобы получить точку пересечения.
// Если нет точки пересечения - +-inf, если точек бесконечно много - nan
float Line::getLineLineIntersection (const Vector3 &r, const Vector3 &vec) const
{

    // решаем уравнение t1 * l + q * triangle.side1 = r относительно t1
    float det = l.x*vec.y - l.y * vec.x;
    if (!isZero(det))
        return (r.x*vec.y - r.y * vec.x) / det;
    else
    {
        det = l.x*vec.z - l.z * vec.x;
        if (!isZero(det))
            return (r.x*vec.z - r.z * vec.x) / det;
        else
        {
            det = l.y*vec.z - l.z * vec.y;
            return (r.y*vec.z - r.z * vec.y) / det;
        }
    }

}




#if 0
void Line::intersectBy (const Triangle &triangle)
{
    float t1,t2,t3;

    // решаем уравнение t1 * l + q * triangle.side1 = r относительно t1
    t1 = getLineLineIntersection (this, triangle.getP1() - r_0, triangle.getSide1());
    t2 = getLineLineIntersection (this, triangle.getP2() - r_0, triangle.getSide2());
    t3 = getLineLineIntersection (this, triangle.getP3() - r_0, triangle.getSide3());

    // находим радиусы-векторы точек пересечения

    Vector3 int1 = l * t1 + r_0,
            int2 = l * t2 + r_0,
            int3 = l * t3 + r_0;

    

    // Линия пересекает сторону side1 внутри треугольника, если и только если (p1 - int1) сонаправлена (int1 - p2)

    if (isZero(t1-t2))
        t1_ = (t2_ = t1);
    
    else if (isZero(t2-t3))
        t1_ = (t2_ = t2);

    else if (isZero(t1-t3))
        t1_ = (t2_ = t3);

    else
    {

    }


}
#endif // 0
