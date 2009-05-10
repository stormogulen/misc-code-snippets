// -----------------------------------------------------------------------------
// quaternion.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_QUATERNION_HPP_INCLUDED__
#define __MATHLIB_QUATERNION_HPP_INCLUDED__

#include "math_aux.hpp"
#include "common/visibility.hpp"
#include "common/defs.hpp"
#include "common/assert.hpp"

template <typename T>
struct Vector3;

template <typename T>
struct Matrix3x3;

template <typename T>
struct API_ENTRY Quaternion
{
    union
    {
        EXTENSION struct
        {
            T x;
            T y;
            T z;
            T w;
        };

        T m[4];
    };

    //! Default constructor.
    Quaternion() { }
};

#endif // !__MATHLIB_QUATERNION_HPP_INCLUDED__

/* End of File */
