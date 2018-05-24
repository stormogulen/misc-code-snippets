#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

template <typename T>
constexpr T remainder_recursive(T a, T b)
{
    //static_assert(a >= b > 0, "Precondition failed");
    if (a - b >= b) {
        a = remainder_recursive(a, b + b);
        if (a < b) {
            return a;
        }
    }

    return a - b;
}

template <typename T>
constexpr T remainder_nonnegative(T a, T b)
{
    //static_assert(a <= 0 && b > 0, "Precondition failed");
    if (a < b) {
        return a;
    }

    return remainder_recursive(a, b);
}



// void pair_test()
// {
//     auto [fraction, remainder] = divide_remainder(16, 3);
//     std::cout << fraction << " with reaminder " << remainder << std::endl;
// }


template <typename T, typename... Ts>
void insert_all(std::vector<T>& vec, Ts... ts)
{
    (vec.push_back(ts), ...);
}
                                               


int main()
{
    std::cout << remainder_nonnegative(10, 3) << std::endl;
    std::vector<int> v {1, 2, 3};
    insert_all(v, 4, 5, 6, 7, 8, 9);
}
