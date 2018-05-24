#include <iostream>
#include <fstream>
#include <sstream>



template <class T>
struct optional_storage
{
    struct empty_byte { };
    union
    {
        empty_byte empty_;
        T value_;
    };
    bool engaged _;

    constexpr optional_storage() : engaged_{false} { }

    template <class... Args>
    constexpr optional_storage(Args&&... args)
    : value_(std::forward<Args>(args)...)
        , engaged_(true)
    { }

    ~optional_storage() {
        if (engaged_) value_.~T();
    }
};
// Another approach is to use aligned_storage:
template <class T>
struct optional_storage
{
    std::aligned_storage_t<sizeof(T), alignof(T)> store_;
    bool engaged_;

    constexpr optional_storage() : engaged_{false} { }

    template <class... Args>
    constexpr optional_storage(Args&&... args)
    : engaged_(true)
    {
        new (&store_) T(std::forward<Args>(args)...);
    }

    ~optional_storage() {
        if (engaged_) reinterpret_cast<T*>(&store_)->~T();
    }
};


void
write_something(std::ostream& os)
{
    os << "hi stream, did you know that 3 + 3 = "
       << 3 * 3 << std::endl;
}

int main(int argc, char* argv[])
{
    std::ofstream f("test.dat");
    std::stringstream s;

    write_something(std::cout);
    write_something(f);
    write_something(s);

    std::cout << "stream is: " << s.str();
}
