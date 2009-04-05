// -----------------------------------------------------------------------------
// vector2.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_VECTOR2_HPP_INCLUDED__
#define __MATHLIB_VECTOR2_HPP_INCLUDED__

#include "math_aux.hpp"
#include "common/visibility.hpp"


//#define API_ENTRY
#define INLINE inline
#define EXTENSION __extension__

template <typename T>
struct API_ENTRY Vector2
{
    union
    {
        EXTENSION struct
        {
            T x;
            T y;
        };

        T m[2];
    };

    //! Default constructor; does no initialization.
    Vector2() { }

    //! Construct a 2-D vector from x and y elements.
    Vector2(T tx, T ty) : x(tx), y(ty) { }

    //! Destrcutor.
    ~Vector2() { }

    //! Copy a 2-D vector.
    Vector2(const Vector2<T>& rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }

    //! Assign one 2-D vector to another.
    Vector2<T>& operator=(const Vector2<T>& rhs)
    {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    //! Set all elements of a 2-D vector to the same scalar value.
    explicit Vector2(T scalar)
    {
        x = scalar;
        y = scalar;
    }

    //! Copy elements from a 2-D point into a 2-D vector.
    //explicit Vector3(const Point3<T>& point);

    //! Subscripting operator to set or get an element.
    INLINE T& operator[](unsigned int idx)       { return m[idx]; }

    //! Subscripting operator to get an element.
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
    void normalize()
    {
        T length_sqr = x*x + y*y;
        if (mathaux::is_zero(length_sqr))
            zero();
        else
        {
            T factor = mathaux::inv_sqrt(length_sqr);
            x *= factor;
            y *= factor;
        }
    }

    //! Negate operator, negate all elements of a 2-D vector.
    Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

    //! Addition, add two 2-D vectors.
    Vector2<T> operator+(const Vector2<T>& rhs) const;

    //! Addition, compound assignment and addition.
    Vector2<T>& operator+=(const Vector2<T>& rhs);

    //! Subtraction, subtract a 2-D vector from another 2-D vector.
    Vector2<T> operator-(const Vector2<T>& rhs) const;

    //! Subtraction, compound assignment and subtraction.
    Vector2<T>& operator-=(const Vector2<T>& rhs);

    //! Scalar multiplication, multiply a 2-D vector by a scalar.
    Vector2<T> operator*(T scalar);

    //! Scalar multiplication, compound assignment and multiplication.
    Vector2<T>& operator*=(T scalar);

    //! Scalar division, divide a 2-D vector by a scalar.
    Vector2<T> operator/(T scalar);

    //! Scalar division, compound assignment and division by scalar.
    Vector2<T>& operator/=(T scalar);

    //! Dot product.
    T dot(const Vector2<T>& v) const;

    //! Perpendicular.
    INLINE Vector2<T> perpendicular() const { return Vector2<T>(-y, x); }

    //! 
    T perp_dot(const Vector2<T>& v) const;
};


//
// Free functions form 2-D vectors.
//

template <typename T>
Vector2<T> operator*(T scalar, const Vector2<T>& rhs);

template <typename T>
T dot(const Vector2<T>& v1, const Vector2<T>& v2);

template <typename T>
T perp_dot(const Vector2<T>& v1, const Vector2<T>& v2);

#endif // !__MATHLIB_VECTOR2_HPP_INCLUDED__

/* End of File */
