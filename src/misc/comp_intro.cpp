#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void xor_test()
{
    int baseline[] = {1, 4, 2, 11, 56};
    int actual[] = {1, 11, 56, 4};

    const auto bs_xor =
        std::accumulate(std::begin(baseline),
                        std::end(baseline),
                        0,
                        std::bit_xor<>());
    const auto ac_xor =
        std::accumulate(std::begin(actual),
                        std::end(actual),
                        0,
                        std::bit_xor<>());

    std::cout << (bs_xor ^ ac_xor) << std::endl; // the missing number
}

int main()
{
    xor_test();
}
