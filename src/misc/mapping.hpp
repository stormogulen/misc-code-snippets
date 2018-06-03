#ifndef __MAPPING_HPP_INCLUDED__
#define __MAPPING_HPP_INCLUDED__


#include <string>

struct Mapping
{
    const char* color_name;
    const char* hex_value;
    
}  constexpr mappings[] = {
    {"EMPTY", "#00000000"},
    {"BLACK", "#FF000000"},
    {"WHITE", "#FFFFFFFF"},
    {"RED", "#FFFF0000"}
};

constexpr bool equal(const char* lhs, const char* rhs)
{
    while (*lhs || *rhs) {
        if (*lhs++ != *rhs++) {
            return false;
        }
    }

    return true;
}

constexpr const char* name_to_hex(const char* name)
{
    for (Mapping m: mappings) {
        if (equal(m.color_name, name)) {
            return m.hex_value;
        }
    }
    // Return some defaults?
    return "#00000000";
}

//constexpr const char* XXX = name_to_hex("");


#endif // !__MAPPING_HPP_INCLUDED__
