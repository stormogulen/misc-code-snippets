// -----------------------------------------------------------------------------
// vector2.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_VECTOR2_HPP_INCLUDED__
#define __MATHLIB_VECTOR2_HPP_INCLUDED__

#include "math_aux.hpp"
#include "visibility.hpp"

template <typename T>
struct API_ENTRY Vector2
{
    union
    {
        struct
        {
            T x;
            T y;
        };

        T m[2];
    };

    //! Default constructor.
    Vector2() { }

    //! Constructor.
    Vector2(T tx, T ty) : x(tx), y(ty) { }

    //! Destrcutor.
    ~Vector2() { }

    INLINE T& operator[](unsigned int idx)       { return m[idx]; }
    INLINE T  operator[](unsigned int idx) const { return m[idx]; }

    //! Vector length.
    T length() const { return mathaux::sqrt(x*x + y*y); }

    //! Length of vector squared.
    T length_squared() const { return (x*x + y*y); }

    //! Equality operator.
    bool operator==(const Vector2<T>& rhs) const
    {
        if (mathaux::are_equal(rhs.x, x) &&
            mathaux::are_equal(rhs.y, y))
            return true;

        return false;
    }

    //! Not equal operator.
    bool operator!=(const Vector2<T>& rhs) const
    {
        if (mathaux::are_equal(rhs.x, x) &&
            mathaux::are_equal(rhs.y, y))
            return false;

        return true;
    }

    //! Test for 'near-zero' values.
    bool is_zero() const
    {
        return mathaux::is_zero(x*x + y*y);
    }

    //! Sets 'near-zero' values to 0.
    void clean()
    {
        if (mathaux::is_zero(x))
            x = 0.0;

        if (mathaux::is_zero(y))
            y = 0.0;
    }
};
    

#endif // !__MATHLIB_VECTOR2_HPP_INCLUDED__

/* End of File */