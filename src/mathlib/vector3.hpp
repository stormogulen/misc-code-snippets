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

    INLINE T& operator[](unsigned int idx)       { return m[i]; }
    INLINE T  operator[](unsigned int idx) const { return m[i]; }

    //! Vector length.
    T length() const;

    //! Vector length squared.
    T length_squared() const;

    //!
    bool operator==(const Vector3<T>& rhs) const;
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

    
    
};

//! Point distance.
template <typename T>
T distance(const Vector3<T>& v1, const Vector3<T>& v2);

//! Point distance squared.
template <typename T>
T distance_squared(const Vector3<T>& v1, const Vector3<T>& v2);

#endif // !__MATHLIB_VECTOR3_HPP_INCLUDED__

/* End of File */
