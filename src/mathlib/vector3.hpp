// -----------------------------------------------------------------------------
// vector3.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_VECTOR3_HPP_INCLUDED__
#define __MATHLIB_VECTOR3_HPP_INCLUDED__

#include "math_aux.hpp"
#include "common/visibility.hpp"

template <typename T>
struct API_ENTRY Vector3
{
    union
    {
        EXTENSION struct
        {
            T x;
            T y;
            T z;
        };
   
        T m[3];
    };

    //! Default constructor, does no initialization.
    Vector3() { }

    //! Construct a 3-D vector from x, y and z elements.
    Vector3(T tx, T ty, T tz)
        : x(tx), y(ty), z(tz)
    {
    }

    //! Destructor.
    ~Vector3() { }

    //! Copy a 3-D vector.
    Vector3(const Vector3<T>& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }

    //! Assignment
    Vector3<T>& operator=(const Vector3<T>& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;

        return *this;
    }

    //! Set all elements of a 2-D vector to the same scalar value.
    explicit Vector3(T scalar)
    {
        x = scalar;
        y = scalar;
        z = scalar;
    }

    //! Subscripting operator to set or get an element.
    INLINE T& operator[](unsigned int idx)       { return m[idx]; }

    //! Subscripting operator to get an element.
    INLINE T  operator[](unsigned int idx) const { return m[idx]; }

    //! Vector length.
    T length() const
    {
        return mathaux::sqrt(x*x + y*y + z*z);
    }

    //! Vector length squared.
    T length_squared() const
    {
        return (x*x + y*y + z*z);
    }

    //! Equality operator.
    bool operator==(const Vector3<T>& rhs) const
    {
        if (mathaux::are_equal(rhs.x, x) &&
            mathaux::are_equal(rhs.y, y) &&
            mathaux::are_equal(rhs.z, z))
            return true;

        return false;
    }

    //! Not equal operator.
    bool operator!=(const Vector3<T>& rhs) const
    {
        if (mathaux::are_equal(rhs.x, x) &&
            mathaux::are_equal(rhs.y, y) &&
            mathaux::are_equal(rhs.z, z))
            return false;

        return true;
    }

    //! Test for 'near-zero' values.
    bool is_zero() const
    {
        return mathaux::is_zero(x*x + y*y + z*z);
    }

    //! Check for unit vector.
    bool is_unit() const
    {
        return mathaux::is_zero(1.0f - x*x - y*y - z*z);
    }

    //! Set elements.
    INLINE void set(T tx, T ty, T tz) { x = tx; y = ty; z = tz; }

    //! Set elements close to zero equal to zero.
    void clean()
    {
        if (mathaux::is_zero(x))
            x = 0;
        if (mathaux::is_zero(y))
            y = 0;
        if (mathaux::is_zero(z))
            z = 0;
    }
        

    //! Set all elements to zero.
    INLINE void zero() { x = y = z = 0; }

    //! Create a unit vector.
    void normalize()
    {
        T length_sq = x*x + Y*y + z*z;
        AC_ASSERT(length_sq != 0);

        if (mathaux::is_zero(length_sq))
            zero();
        else
        {
            T factor = mathaux::inv_sqrt(length_sq);
            x *= factor;
            y *= factor;
            z *= factor;
        }
    }

    //! Add vector to self.
    Vector3<T> operator+(const Vector3<T>& rhs) const
    {
        return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    //! Subtract vector from self.
    Vector3<T>& operator-(const Vector3<T>& rhs) const
    {
        return Vector3<T>(x-rhs.x, y-rhs.y, z-rhs.z);
    }

    //! Negate vector.
    Vector3<T> operator-() const
    {
        return Vector3<T>(-x, -y, -z);
    }

    
    
};

//! Point distance.
template <typename T>
T distance(const Vector3<T>& v1, const Vector3<T>& v2)
{
    T x = v1.x - v2.x;
    T y = v1.y - v2.y;
    T z = v1.z - v2.z;

    return mathaux::sqrt(x*x + y*y + z*z);
}

//! Point distance squared.
template <typename T>
T distance_squared(const Vector3<T>& v1, const Vector3<T>& v2)
{
    T x = v1.x - v2.x;
    T y = v1.y - v2.y;
    T z = v1.z - v2.z;

    return (x*x + y*y + z*z);
}

//!
template <typename T>
Vector3<T>& operator+=(Vector3<T>& self, const Vector3<T>& other);

//!
template <typename T>
Vector3<T>& operator-=(Vector3<T>& self, const Vector3<T>& other);


#endif // !__MATHLIB_VECTOR3_HPP_INCLUDED__

/* End of File */
