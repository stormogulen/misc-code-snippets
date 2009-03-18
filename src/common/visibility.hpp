// -----------------------------------------------------------------------------
// visibility.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __COMMON_VISIBILITY_HPP_INCLUDED__
#define __COMMON_VISIBILITY_HPP_INCLUDED__

#ifdef WIN32
#  define DLL_IMPORT __declspec(dllimport)
#  define DLL_EXPORT __declspec(dllexport)
#  define DLL_LOCAL
#  define DLL_PUBLIC
#else 
#  define DLL_IMPORT
#  ifdef GCC_HASCLASSVISIBILITY
#    define DLL_EXPORT __attribute__ ((visibility("default")))
//#    define DLL_EXPORT __attribute__ ((externally_visible))
#    define DLL_LOCAL  __attribute__ ((visibility("hidden")))
#    define DLL_PUBLIC __attribute__ ((visibility("default")))
#  else
#    define DLL_EXPORT
#    define DLL_LOCAL
#    define DLL_PUBLIC
#  endif
#endif


//! Define API for DLL builds.
#ifdef DLL
  #ifdef DLL_EXPORTS
    #define API_ENTRY DLL_EXPORT
  #else
    #define API_ENTRY  DLL_IMPORT
  #endif // DLL_EXPORTS
#else
  #define API_ENTRY
#endif // DLL

//! Throwable classes must always be visible on GCC in all binaries.
#ifdef WIN32
#  define EXCEPTION_API(api) api
#elif defined(GCC_HASCLASSVISIBILITY)
#  define EXCEPTION_API(api) DLL_EXPORT
#else
#  define EXCEPTION_API(api)
#endif


#endif // !__COMMON_VISIBILITY_HPP_INCLUDED__

/* End of File */
