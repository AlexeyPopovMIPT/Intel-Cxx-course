#ifndef __FLOAT_TRAITS_HPP__
#define __FLOAT_TRAITS_HPP__


const float ACCURACY = 1e-6;
inline bool isZero (float f)
{
    return (-ACCURACY < f && f < ACCURACY);
}

inline bool isPos (float f)
{
    return f >= ACCURACY;
}

inline bool isNeg (float f)
{
    return isPos(-f);
}


#endif // !__FLOAT_TRAITS_HPP__