// -----------------------------------------------------------------------------
// assert.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __COMMON_ASSERT_HPP_INCLUDED__
#define __COMMON_ASSERT_HPP_INCLUDED__

#include <cassert>

#if !defined(DEBUG)
#  define AC_ASSERT(x) { static_cast<void>(sizeof(x)); } while(0)
#else
#  define AC_ASSERT(x) assert(x)
#endif

#if DO_AC_ASSERT
//! Set ptr to invalid pointer value.
template <typename T>
INLINE void poison_pointer(T* &ptr)
{
    ptr = reinterpret_cast<T*>(-1);
}
#else
template <typename T>
INLINE void poison_pointer(T*)
{
    /* Do nothing */
}
#endif // DO_AC_ASSERT

//! Report a runtime warning.
void runtime_warning(const char* format, ...);


#endif // !__COMMON_ASSERT_HPP_INCLUDED__

/* End of File */
