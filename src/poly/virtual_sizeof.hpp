// -----------------------------------------------------------------------------
// virtual_sizeof.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#pragma once
#ifndef __VIRTUAL_SIZEOF_HPP_INCLUDED__
#define __VIRTUAL_SIZEOF_HPP_INCLUDED__

#include <cstdlib>

template <typename T>
struct Wrapper : public T
{
    virtual size_t size() const
    {
        return sizeof(T);
    }

 protected:
    Wrapper() { }
};

template <typename T>
T* create()
{
    return new Wrapper<T>;
}



#endif // !__VIRTUAL_SIZEOF_HPP_INCLUDED__

/* End of File */
