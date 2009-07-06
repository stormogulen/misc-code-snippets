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

#ifdef __GNUC__
#include <cxxabi.h>
std::string demangle(const char* name)
{
    const char* start = strchr(name, '(');
    if (start != 0)
        ++start;
    else start = name;
    const char* end = strchr(start, '+');

    std::string in;
    if (end == 0)
        in.assign(start);
    else in.assing(start, end);

    size_t len;
    int status;
    char* unmangled = ::abi::__cxa_demangle(in.c_str(), 0, &len, &status);
    if (0 == unmangled)
        return in;

    std::string ret(unmangled);
    free(unmangled);

    return ret;
}
#endif

#if (defined __linux__ || defined __MACH__)
#include <cxxabi.h>
void assert_fail(const char* expr, int line, const char* file, const char* function)
{
    fprintf(stderr, "Assertion failed!"
            "file: '%s' \n"
            "line: %d \n"
            "function: %s \n"
            "expression: %s \n"
            "stack:\n", file, line, function, expr);

    raise(SIGINT);
    abort();
}


#define ACC_ASSERT(x) \
    do { if (x) {} else assert_fail(#x, __LINE__, __FILE__, __PRETTY_FUNCTION__); \
    } while (false)
#else
#define ACC_ASSERT(x) assert(x)
#endif


//! Report a runtime warning.
void runtime_warning(const char* format, ...);


#endif // !__COMMON_ASSERT_HPP_INCLUDED__

/* End of File */
