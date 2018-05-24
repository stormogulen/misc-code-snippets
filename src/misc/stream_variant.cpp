#include <iostream>
#include <variant>

template <typename T>
struct Streamer
{
    const T& value;
};

template <typename T>
Streamer(T) -> Streamer<T>;

template <typename T>
std::ostream&
operator<<(std::ostream& os, Streamer<T> s)
{
    os << s.value;
    return os;
}

template <tpename... Ts>
std::ostream&
opertor<<(std::ostream& os, Streamer<std::variant<Ts...>> sv)
{
    std::visit([&os](const auto& v) { os << Streamer{v}; }, sv.value);
    return os;
}


int main()
{
    std::variant<int, std::string> a, b;
    a = 1;
    b = "one";
    std::cout << Streamer{a} << Streamer{b} << '\n';
}
