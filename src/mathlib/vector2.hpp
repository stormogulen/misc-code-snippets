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

    //! Set.
    INLINE void set(T tx, T ty) { x = tx; y = ty; }

    //! Set to zero.
    INLINE void zero() { x = y = 0.0; }

    //! Normalize.
    void normalize();

    //! Negate operator.
    Vector2<T> operator-() const;

    //! Addition.
    Vector2<T> operator+(const Vector2<T>& rhs) const;

    //! Addition.
    Vector2<T>& operator+=(const Vector2<T>& rhs);

    //! Subtraction.
    Vector2<T> operator-(const Vector2<T>& rhs) const;

    //! Subtraction.
    Vector2<T>& operator-=(const Vector2<T>& rhs);

    //! Scalar multiplication.
    Vector2<T> operator*(T scalar);

    //! Scalar multiplication.
    Vector2<T>& operator*=(T scalar);

    //! Scalar division.
    Vector2<T> operator/(T scalar);

    //! Scalar division.
    Vector2<T>& operator/=(T scalar);

    //! Dot product.
    T dot(const Vector2<T>& v) const;

    //! Perpendicular.
    INLINE Vector2<T> perpendicular() const { return Vector2<T>(-y, x); }

    //!
    T perp_dot(const Vector2<T>& v) const;
};


template <typename T>
Vector2<T> operator*(T scalar, const Vector2<T>& rhs);

template <typename T>
T dot(const Vector2<T>& v1, const Vector2<T>& v2);

template <typename T>
T perp_dot(const Vector2<T>& v1, const Vector2<T>& v2);

#endif // !__MATHLIB_VECTOR2_HPP_INCLUDED__

/* End of File */
