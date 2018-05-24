#include "index.hpp"
#include <future>
#include <string>
#include <iostream>
#include <algorithm>


void run()
{
    std::future<std::string> f = std::async(std::launch::async, reverse_string, "Roma tibi subito motibus ibit amor");
    auto g = std::async(std::launch::async, reverse_string, "Anita lava la tina");
    auto h = std::async(std::launch::async, reverse_string, "A man, a plan, a canal: Panama");

    std::cout << "SHOWING RESULTS...." << std::endl;

    std::cout << "R1: " << f.get() << std::endl << std::endl;
    std::cout << "R2: " << g.get() << std::endl << std::endl;
    std::cout << "R3: " << h.get() << std::endl << std::endl;
}

std::string reverse_string(const std::string& s)
{
    std::cout << "Reversing " << s << std::endl;
    std::string ss(s);
    std::reverse(ss.begin(), ss.end());

    return ss;
}


class Index::IndexImpl
{
 public:
    int value_;
};

Index::Index()
    : pimpl_{std::make_unique<IndexImpl>()}
{
}

Index::~Index() = default;

Index::Index(Index &&) = default;

Index &Index::operator=(Index &&) = default;

int
Index::value() const
{
    return pimpl_->value_;
}

void
Index::set_value(const int v)
{
    pimpl_->value_ = v;
}
