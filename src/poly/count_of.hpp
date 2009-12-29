// -----------------------------------------------------------------------------
// count_of.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __POLY_COUNT_OF_HPP_INCLUDED__
#define __POLY_COUNT_OF_HPP_INCLUDED__

template <typename T, size_t N>
size_t count_of(const T (&)[N])
{
    return N;
}

#endif // !__POLY_COUNT_OF_HPP_INCLUDED__

/* End of File */
