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
    INLINE T& operator[](unsigned int idx)       { return m[i]; }

    //! Subscripting operator to get an element.
    INLINE T  operator[](unsigned int idx) const { return m[i]; }

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
    bool operator==(const Vector3<T>& rhs) const;

    //! Not equal operator.
    bool operator!=(const Vector3<T>& rhs) const;

    //!
    bool is_zero() const;

    //!
    bool is_unit() const;

    //!
    INLINE void set(T tx, T ty, T tz) { x = tx; y = ty; z = tz; }

    //!
    void clean();

    //!
    INLINE void zero() { x = y = z = 0; }

    //!
    void normalize();

    //!
    Vector3<T> operator+(const Vector3<T>& rhs) const;

    //!
    Vector3<T>& operator-(const Vector3<T>& rhs) const;

    //!
    Vector3<T> operator-() const;

    
    
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
Vector3<T>& operator-=(Vector3<T>& self, const Vector3<T>& other);


#endif // !__MATHLIB_VECTOR3_HPP_INCLUDED__

/* End of File */
