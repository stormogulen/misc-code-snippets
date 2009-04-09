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
    Vector4(T tx, T ty, T tz, T tw)
        : x(tx), y(ty), z(tz), w(tw)
    {
    }    

    //! Destructor.
    ~Vector4() { }

    //! Copy
    Vector4(const Vector4<T>& rhs)
        : x(rhs.x),
          y(rhs.y),
          z(rhs.z),
          w(rhs.w)
    {
    }

    //! Assignment
    Vector4<T>& operator=(const Vector4<T>& rhs)
    {
        if (this == &rhs)
            return *this;

        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;

        return *this;
    }

    //!
    INLINE T& operator[](unsigned int idx)       { return m[idx]; }

    //!
    INLINE T  operator[](unsigned int idx) const { return m[idx]; }

    //! Vector length.
    T length() const
    {
        return mathaux::sqrt(x*x + y*y + z*z + w*w);
    }

    //! Vector length squared.
    /** Avoids square root. */
    T length_squared() const
    {
        return (x*x + y*y + z*z + w*w);
    }

    //! Comparison operator.
    bool operator==(const Vector4<T>& other) const
    {
        if (mathaux::are_equal(other.x, x) &&
            mathaux::are_equal(other.y, y) &&
            mathaux::are_equal(other.z, z) &&
            mathaux::are_equal(other.w, w))
            return true;

        return false;
    }

    //! Comparison
    bool operator!=(const Vector4<T>& other) const
    {
        if (mathaux::are_equal(other.x, x) &&
            mathaux::are_equal(other.y, y) &&
            mathaux::are_equal(other.z, z) &&
            mathaux::are_equal(other.w, w))
            return false;

        return true;
    }
    
    //! Check for zero vector.
    bool is_zero() const
    {
        return mathaux::is_zero(x*x + y*y + z*z + w*w);
    }

    //! Check for unit vector.
    bool is_unit() const
    {
        return mathaux::is_zero(1.0f - x*x - - y*y - z*z - w*w);
    }

    //! Set elements.
    INLINE void set(T tx, T ty, T tz, T tw)
    {
        x = tx;
        y = ty;
        z = tz;
        w = tw;
    }
    

};

#endif // !__MATHLIB_VECTOR4_HPP_INCLUDED__

/* End of File */
