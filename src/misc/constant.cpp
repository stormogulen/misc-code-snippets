#include <iostream>

constexpr int
hash_string(const char* str_to_hash)
{
    auto hash = 0;
    if (!str_to_hash) {
        return hash;
    }

    while (char char_value = *str_to_hash++) {
        hash = char_value + 31 * hash;
    }

    return hash;
}


class Constant
{
 public:
    constexpr Constant(const char* str)
    : str_(str)
        , value_(hash_string(str))
    {
    }

    constexpr bool operator==(const Constant& rhs)
    {
        return value_ == rhs.value_;
    }

    constexpr int value() { return value_; }
    constexpr const char* str() { return str_; }

 private:
    const char* str_;
    int value_;
};


Constant internal_error("Internal server error");
Constant unknown_error("Unknown error");
Constant bad_argument("Bad argument");
Constant invalid_parameter("Invalid parameter");

void test(const char* str)
{
    Constant c(str);
    if (c == internal_error) {
        std::cout << c.str() << " - " << internal_error.str() << std::endl;
    }

    if (c.value() == unknown_error.value()) {
        std::cout << c.str() << " - " << unknown_error.str() << std::endl;
    }
}

int main()
{
    test("Internal server error");
    test("Unknown error");

}
