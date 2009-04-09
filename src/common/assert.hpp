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

#endif // !__COMMON_ASSERT_HPP_INCLUDED__

/* End of File */
