// -----------------------------------------------------------------------------
// namespace.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __COMMON_NAMESPACE_HPP_INCLUDED__
#define __COMMON_NAMESPACE_HPP_INCLUDED__

#ifndef PROJECT_NAMESPACE_NAME
#  define PROJECT_NAMESPACE_NAME mathaux_1_0
#endif

#define NAMESPACE_BEGIN namespace PROJECT_NAMESPACE_NAME {
#define NAMESPACE_END }
#define NAMESPACE_USE using namespace PROJECT_NAMESPACE_NAME
#define NAMESPACE_QUALIFIER PROJECT_NAMESPACE_NAME::

namespace mathaux = PROJECT_NAMESPACE_NAME

#define NAMESPACE_NAME(name) ::PROJECT_NAMESPACE_NAME::(name)

#define NAMESPACE_BEGIN(ns) namespace ns {
#define NAMESPACE_END(ns) }
#define NAMESPACE_USE(ns) using namespace ns;
#define DLL_UNMANGLED_EXPORT extern "C"

    
#endif // !__COMMON_NAMESPACE_HPP_INCLUDED__

/* End of File */
