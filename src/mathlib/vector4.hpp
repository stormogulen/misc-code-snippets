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

    //! Subscripting operator to set or get an element.
    INLINE T& operator[](unsigned int idx)       { return m[idx]; }

    //! Subscripting operator to get an element.
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

    //! Set elements close to zero equal to zero.
    void clean()
    {
        if (mathaux::is_zero(x))
            x = 0;

        if (mathaux::is_zero(y))
            y = 0;

        if (mathaux::is_zero(z))
            z = 0;

        if (mathaux::is_zero(w))
            w = 0;
    }

    //! Set all elements to zero.
    INLINE void zero()
    {
        x = y = z = w = 0;
    }

    //! Normalize 4-D vector.
    void normalize()
    {
        T length_sq = x*x + y*y + z*z + w*w;

        if (mathaux::is_zero(length_sq))
            zero();
        else
        {
            T factor = mathaux::inv_sqrt(length_sq);
            x *= factor;
            y *= factor;
            z *= factor;
            w *= factor;
        }
    }

    //! Addition, add vector to self.
    Vector4<T> operator+(const Vector4<T>& other) const
    {
        return Vector4<T>(x+other.x,
                          y+other.y,
                          z+other.z,
                          w+other.w);
    }

    //! Add vector to self.
    Vector4<T>& operator+=(const Vector4<T>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }

    //! Subtraction.
    Vector4<T> operator-(const Vector4<T>& other) const
    {
        return Vector4<T>(x-other.x,
                          y-other.y,
                          z-other.z,
                          w-other.w);
    }

    //! Subtraction.
    Vector4<T>& operator-=(const Vector4<T>& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;

        return *this;
    }

    //! Scalar multiplication.
    Vector4<T> operator*(T scalar)
    {
        return Vector4<T>(scalar*x,
                          scalar*y,
                          scalar*z,
                          scalar*w);
    }

    //! Scalar multiplication, compound assignment and multiplication.
    Vector4<T>& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;

        return *this;
    }

    //! Scalar division, divide a 4-D vector by a scalar.
    Vector4<T> operator/(T scalar)
    {
        return Vector4<T>(x/scalar,
                          y/scalar,
                          z/scalar,
                          w/scalar);
    }

    //! Scalar division, compound assignment and division by scalar.
    Vector4<T>& operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;

        return *this;
    }

    //! Dot product.
    T dot(const Vector4<T>& other) const
    {
        return (x*other.x +
                y*other.y +
                z*other.z +
                w*other.w);
    }
    

};

//! Scalar multiplication.
template <typename T>
Vector4<T> operator*(T scalar, const Vector4<T>& other)
{
    return Vector4<T>(scalar * other.x,
                      scalar * other.y,
                      scalar * other.z,
                      scalar * other.w);
}

//! Dot product.
template <typename T>
T dot(const Vector4<T>& v1, const Vector4<T>& v2)
{
    return (v1.x * v2.x +
            v1.y * v2.y +
            v1.z * v2.z +
            v1.w * v2.w);
}

#endif // !__MATHLIB_VECTOR4_HPP_INCLUDED__

/* End of File */
