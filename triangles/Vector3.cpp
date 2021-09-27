#include "Vector3.hpp"

bool Vector3::isZeroPoint() const 
{ 
    return isZero(x) && isZero(y) && isZero(z);
}

bool Vector3::operator== (const Vector3& rhs) const
{
    return isZero(x-rhs.x) && isZero(y-rhs.y) && isZero(z-rhs.z);
}

float Vector3::operator* (const Vector3& rhs) const 
{
    return x*rhs.x + y*rhs.y + z*rhs.z; 
}

Vector3 Vector3::operator- (const Vector3& rhs) const
{
    return Vector3 {x-rhs.x, y-rhs.y, z-rhs.z};
}

Vector3 Vector3::operator+ (const Vector3& rhs) const
{
    return Vector3 {x+rhs.x, y+rhs.y, z+rhs.z};
}

Vector3 Vector3::operator* (const float  rhs) const 
{
    return Vector3 {x*rhs, y*rhs, z*rhs}; 
}

Vector3 Vector3::vectorMul (const Vector3& rhs) const
{
    return Vector3
    {
        y*rhs.z - z*rhs.y,
        z*rhs.x - x*rhs.z,
        x*rhs.y - y*rhs.x
    };
}
