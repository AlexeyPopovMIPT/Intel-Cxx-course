#ifndef __VECTOR3_HPP__
#define __VECTOR3_HPP__

struct Vector3;

#include <math.h> // for NAN
#include "float_traits.hpp"


struct Vector3
{
    float x = NAN, y = NAN, z = NAN;

    bool isZeroPoint() const;

    bool operator== (const Vector3& rhs) const;

    float operator* (const Vector3& rhs) const;

    Vector3 operator- (const Vector3& rhs) const;

    Vector3 operator+ (const Vector3& rhs) const;

    Vector3 operator* (const float  rhs) const;

    Vector3 vectorMul (const Vector3& rhs) const;

};


#endif // !__VECTOR3_HPP__
