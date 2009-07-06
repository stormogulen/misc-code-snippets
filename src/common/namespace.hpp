// -----------------------------------------------------------------------------
// namespace.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __COMMON_NAMESPACE_HPP_INCLUDED__
#define __COMMON_NAMESPACE_HPP_INCLUDED__

#ifndef PROJECT_NAMESPACE_NAME
#  define PROJECT_NAMESPACE_NAME mathaux
#endif

#define NAMESPACE_BEGIN namespace PROJECT_NAMESPACE_NAME {
#define NAMESPACE_END }

#define NAMESPACE_NAME(name) ::PROJECT_NAMESPACE_NAME::(name)

#endif // !__COMMON_NAMESPACE_HPP_INCLUDED__

/* End of File */
