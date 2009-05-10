// -----------------------------------------------------------------------------
// matrix3x3.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_MATRIX3X3_HPP_INCLUDED__
#define __MATHLIB_MATRIX3X3_HPP_INCLUDED__

#include "math_aux.hpp"
#include "common/visibility.hpp"
#include "common/defs.hpp"
#include "common/assert.hpp"

template <typename T>
struct Quaternion;

template <typename T>
struct Vector3;

template <typename T>
struct API_ENTRY Matrix3x3
{
    union
    {
        EXTENSION struct
        {
            T _11, _12, _13;
            T _21, _22, _23;
            T _31, _32, _33;
        };

        T mv[9];
    };

    //! Default constructor.
    Matrix3x3() { }

    //! Constructor.
    explicit Matrix3x3(const Quaternion<T>& q)
    {
    }

    //! Copy constructor.
    Matrix3x3(const Matrix3x3<T>& rhs)
    {
    }
};


#endif // !__MATHLIB_MATRIX3X3_HPP_INCLUDED__

/* End of File */
