#include <boost/hana.hpp>
#include <iostream>
#include <string>

using namespace std;
namespace hana = boost::hana;

// Check if a type has a serialize method.
auto hasSerialize = hana::is_valid([](auto&& x) -> decltype(x.serialize()) { });

// Serialize any kind of objects.
template <typename T>
std::string serialize(T const& obj) {
    return hana::if_(hasSerialize(obj), // Serialize is selected if available!
                     [](auto& x) { return x.serialize(); },
                     [](auto& x) { return to_string(x); }
        )(obj);
}

// Type A with only a to_string overload.
struct A {};

std::string to_string(const A&)
{
    return "I am a A!";
}

// Type B with a serialize method.
struct B
{
    std::string serialize() const
    {
        return "I am a B!";
    }
};

// Type C with a "wrong" serialize member (not a method) and a to_string overload.
struct C
{
    std::string serialize;
};

std::string to_string(const C&)
{
    return "I am a C!";
}

int main() {
    A a;
    B b;
    C c;

    std::cout << serialize(a) << std::endl;
    std::cout << serialize(b) << std::endl;
    std::cout << serialize(c) << std::endl;
}
