// future-1.cpp

#include <future>
#include <iostream>
#include <vector>

int
twice(int m)
{
    return 2 * m;
}

int main()
{
    std::vector<std::future<int>> futures;

    for (int i = 0; i < 10; ++i) {
        futures.push_back (std::async([](int m) {return 2 * m;} , i));
    }

    for (auto &e : futures) {
        std::cout << e.get() << std::endl;
    }
}
