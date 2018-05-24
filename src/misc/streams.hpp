
#include <iostream>
#include <vector>
#include <list>
#include <deque>

template <typename T>
std::ostream&
operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    std::string comma;

    for (auto& v: vec) {
        os << comma << v;
        comma = ", ";
    }
    os << "]";

    return os;
}


template <typename T>
std::ostream&
operator<<(std::ostream& os, const std::list<T>& list)
{
    os << "[";
    std::string comma;

    for (auto& l : list) {
        os << comma << l;
        comma = ", ";
    }
    os << "]";

    return os;
}

template <typename T>
std::ostream&
operator<<(std::ostream& os, const std::dequeu<T>& deq)
{
    os << "[";
    std::string comma;

    for (auto& d : deq) {
        os << comma << d;
        comma = ", ";
    }
    os << "]";

    return os;
}

template <typename T>
void
binary_write(std::ostream& os, const T& t)
{
    os.write(reinterpret_cast<const char*>(&t), sizeof(t));
}

template <typename Container>
void
binary_write_all(std::ostream& os, const Container& container)
{
    for (auto& c : container) {
        binary_write(os, c);
    }
}

template <typename T>
void
binary_load(std::istream& is, T& t)
{
    is.read(reinterpret_cast<char*>(&t), sizeof(t));
}

template <typename Container>
void
binary_load_all(std::istream& is, Container& container)
{
    for (auto& c : container) {
        binary_load(is, c);
    }
}
