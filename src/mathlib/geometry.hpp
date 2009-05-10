// -----------------------------------------------------------------------------
// geometry.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __MATHLIB_GEOMETRY_HPP_INCLUDED__
#define __MATHLIB_GEOMETRY_HPP_INCLUDED__

#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix3x3.hpp"
#include "quaternion.hpp"

//! 2-D vector of floats.
typedef Vector2<float>   vec2f_t;

//! 2-D vector of doubles.
typedef Vector2<double>  vec2d_t;

//! 2-D vector of integers.
typedef Vector2<int>     vec2i_t;

//! 3-D vector of floats.
typedef Vector3<float>   vec3f_t;

//! 3-D vector of doubles.
typedef Vector3<double>  vec3d_t;

//! 3-D vector of integers.
typedef Vector3<int>     vec3i_t;

//! 4-D vector of floats.
typedef Vector4<float>   vec4f_t;

//! 4-D vector of doubles.
typedef Vector4<double>  vec4d_t;

//! 4-D vector of integers.
typedef Vector4<int>     vec4i_t;

//! Quaternion of floats.
typedef Quaternion<float> quatf_t;

//! Quaternion of doubles.
typedef Quaternion<double> quatd_t;

//! Quaternion of intergers.
typedef Quaternion<int> quati_t;

//! Matrix 3x3 of floats.
typedef Matrix3x3<float> mat3f_t;

//! Matrix 3x3 of doubles.
typedef Matrix3x3<double> mat3d_t;

//! Matrix 3x3 of integers.
typedef Matrix3x3<int> mat3i_t;

#endif // !__MATHLIB_GEOMETRY_HPP_INCLUDED__

/* End of File */
