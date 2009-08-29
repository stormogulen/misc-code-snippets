// -----------------------------------------------------------------------------
// math_aux.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_MATH_AUX_HPP_INCLUDED__
#define __MATHLIB_MATH_AUX_HPP_INCLUDED__

#include "common/visibility.hpp"
#include <cmath>
#include <boost/cstdint.hpp>

namespace mathaux {

//! Epsilon.
#define EPSILON        1.0e-6f
#define EQUAL_EPSILON  0.001f
#define ZERO_EPSILON   1.0E-6

//! Pi.
//#define PI          3.1415926535897932384626433832795f
#define PI          3.14159265359f

//! Half pi.
//#define HALF_PI     1.5707963267948966192313216916398f
#define HALF_PI     1.57079632679f

//! Two pi.
#define TWO_PI      2.0f*PI                      
//#define TWOPI       6.28318530718f

//! Inverted square root.
float inv_sqrt(float value)
{
    return 1.0f / sqrtf(value);
}


//! Calculates a raised to the power of n.
/** NOTE: n must be an integer. */
inline float int_power(float base, unsigned int n)
{
    float t = base;
    float s = 1.0f;

    while (n)
    {
        if (n & 1)
            s *= t;
        n >>= 1;
        t *= t;
    }
    
    return s;
}

//! Degrees per radians constant.
#define DEGREES_PER_RADIAN  57.29577951f

//! To degrees.
inline float to_degrees(float radians)
{
    return (radians * DEGREES_PER_RADIAN);
}

//! Radians per degree constant.
#define RADIANS_PER_DEGREE  0.017453292f

//! To radians.
inline float to_radians(float degrees)
{
    return (degrees * RADIANS_PER_DEGREE);
}

//! Check if n is close to zero.
inline bool is_zero(float n)
{
    return (fabs(n) < EPSILON);
}

//! Square root.
inline float sqrt(float f)
{
    return sqrtf(f);
}

//! Absolute value.
inline float abs(float f)
{
    return fabsf(f);
}

//! Check if equal.
inline bool are_equal(float a, float b)
{
    return is_zero(a-b);
}

//! Cosine.
inline float cos(float f)
{
    return cosf(f);
}

//! Sine.
inline float sin(float f)
{
    return sinf(f);
}

//! Tangent.
inline float tan(float f)
{
    return tanf(f);
}

//! Sine cosine.
inline void sin_cos(float a, float& sina, float& cosa)
{
    sina = sinf(a);
    cosa = cosf(a);
}

//! Closest power of two.
inline unsigned int closest_power_of_two(const unsigned int n)
{
    unsigned int i = 1;
    while (i < n)
        i += i;

    if (4 * n < 3 * i)
        i >>= 1;

    return i;
}

//! Upper power of two.
inline unsigned int upper_power_of_two(const unsigned int n)
{
    unsigned int i = 1;
    while (i < n)
        i += i;

    return i;
}

//! Lower power of two.
inline unsigned int lower_power_of_two(const unsigned int n)
{
    unsigned int i = 1;
    while (i <= n)
        i += i;

    return i >> 1;
}

//! To radian.
inline float to_radian(float degree)
{
    return degree * (PI / 180.0f);
}

//! To Degree.
inline float to_degree(float radian)
{
    return radian * (180.0f / PI);
}

//! Equal.
inline bool equal(const float f0, const float f1, const float epsilon=EPSILON)
{
    return fabs(f0-f1) <= epsilon;
}

/*
#include <cmath>
#include <cstdlib>
//!
static float randf(float min, float max)
{
    return min + (max-min) * (rand() * (1.0f / RAND_MAX));
}
*/
//!
static float ensure_bounds(float value, float min, float max)
{
    value = (value >= min) ? value : min;
    value = (value <= max) ? value : max;

    return value;
}

#define CLAMP(a) \
    if (a > 1.0) a = 1.0; \
    if (a < 0.0) a = 0.0;
    

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

//! Round to integer.
#define INT_ROUND(x) floor((x)+0.5)

//! Round number n to d decimal points. 
#define FLOAT_ROUND(n,d) (floor((n)/pow(.1,(d))+.5)*pow(.1,(d))) 


#define F_COS_1_16     cos(1.0*PI/16.0)
#define F_COS_2_16     cos(2.0*PI/16.0)
//...

inline clamp_byte(int x)
{
    return (x < 0) ? 0 : ( (x > 255) ? 255 : x );
}


} // mathaux

#endif // !__MATHLIB_MATH_AUX_HPP_INCLUDED__

/* End of File */
