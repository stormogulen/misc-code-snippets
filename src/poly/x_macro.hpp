// -----------------------------------------------------------------------------
// x_macro.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2010.
// 

#ifndef __X_MACRO_HPP_INCLUDED__
#define __X_MACRO_HPP_INCLUDED__


#define COLORS \
    X(red) \
    X(blue) \
    X(green)

#define X(a) C##a,
enum Color { COLORS };
#undef X

#define FOR_ALL_COLORS(apply) \
    apply(red) \
    apply(blue) \
    apply(green)


#endif // !__X_MACRO_HPP_INCLUDED__

/* End of File */
