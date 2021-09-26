#include "Plane.hpp"
#include "float_traits.hpp"


void Plane::constructFrom (const Point a, const Point b, const Point c)
{
    float A[3][3] = {{ +(b.y*c.z-b.z*c.y), -(b.x*c.z-b.z*c.x), +(b.x*c.y-b.y*c.x) }, 
                     { -(a.y*c.z-a.z*c.y), +(a.x*c.z-a.z*c.x), -(a.x*c.y-a.y*c.x) },
                     { +(a.y*b.z-a.z*b.y), -(a.x*b.z-a.z*b.x), +(a.x*b.y-a.y*b.x) }};

    float det = a.x*A[0][0] + a.y*A[0][1] + a.z*A[0][2];
    if (!isZero(det))
    {
        float rdet = 1.f / det;

        normal = 
        {
            rdet * (A[0][0] + A[1][0] + A[2][0]),
            rdet * (A[0][1] + A[1][1] + A[2][1]),
            rdet * (A[0][2] + A[1][2] + A[2][2])
        };

        if (!isZero(normal.z)) 
            r_0 = { 0.f, 0.f, 1.f/normal.z };
        else if (!isZero(normal.y)) 
            r_0 = { 0.f, 1.f/normal.y, 0.f };
        else 
            r_0 = { 1.f/normal.x, 0.f, 0.f }; 
    }

    else
    {
        r_0 = { 0.f, 0.f, 0.f };
        
        /* normal = [b * c] vectorly */
        if (a.isZeroPoint()) 
            normal = { A[0][0], A[0][1], A[0][2] };
        else if (b.isZeroPoint())
            normal = { A[1][0], A[1][1], A[1][2] };
        else
            normal = { A[2][0], A[2][1], A[2][2] };


    }
}


Plane::Point_rl_Plane_t Plane::determineRelative (const Point &other) const
{
    Point vec0 = other - r_0;
    float mul = vec0 * normal;

    if (isPos(mul)) return UPPER;
    if (isNeg(mul)) return LOWER;
    return ON_PLANE;
}


Line Plane::operator* (const Plane &other) const
{
    Line result;
    result.l = normal.vectorMul(other.normal);
    result.t1 = -INFINITY;
    result.t2 = INFINITY;

    // result.r_0 = a*this.normal + b*other.normal

    float det = result.l * result.l;
    float a = 1.f / det * 
                    (
                           (      r_0 *       normal) * (other.normal*other.normal) 
                        -  (other.r_0 * other.normal) * (other.normal*      normal)
                    );
    float b = 1.f / det *
                    (
                           (other.r_0 * other.normal) * (      normal*      normal) 
                        -  (      r_0 *       normal) * (other.normal*      normal)
                    );

    result.r_0 = normal*a + other.normal*b;

    return result;


}
