// -----------------------------------------------------------------------------
// vector4.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_VECTOR4_HPP_INCLUDED__
#define __MATHLIB_VECTOR4_HPP_INCLUDED__

#include "math_aux.hpp"
#include "common/visibility.hpp"
#include "common/defs.hpp"
#include "common/assert.hpp"

template <typename T>
struct API_ENTRY Vector4
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

    //! Default constructor, does no initialization.
    Vector4() { }

    //! Construct
    Vector4(T tx, T ty, T tz, T tw);

    //! Destructor.
    ~Vector4();

    //! Copy
    Vector4(const Vector4<T>& rhs);

    //! Assignment
    Vector4<T>& operator=(const Vector4<T>& rhs);
    

};

#endif // !__MATHLIB_VECTOR4_HPP_INCLUDED__

/* End of File */
