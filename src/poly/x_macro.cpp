// -----------------------------------------------------------------------------
// x_macro.cpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2010.
// 

#include "x_macro.hpp"
#include <cstdio>

#define X(a) #a,
static char* color_strings[] = { COLORS };
#undef X

#define SELECT_STRING(a) #a,
static char* color_strings2[] = { FOR_ALL_COLORS(SELECT_STRING) };
#undef SELECT_STRING

int main()
{
    printf("macro - 1\n");
    printf("1 - the color is: %s\n", color_strings[1]);

    printf("macro - 2\n");
    printf("2 - the color is: %s\n", color_strings2[1]);
}
