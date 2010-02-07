// -----------------------------------------------------------------------------
// check.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2010.
// 

#ifndef __CHECK_HPP_INCLUDED__
#define __CHECK_HPP_INCLUDED__

//! Check for nonnull pointer.
template <typename T>
inline T* check(T* ptr)
{
    if (0 == ptr)
        throw std::logic_error("attempting to dereferece a null pointer");

    return ptr;
}

#endif // !__CHECK_HPP_INCLUDED__
/* End of File */
