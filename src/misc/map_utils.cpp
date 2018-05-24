#include <vector>
#include <map>
#include <iostream>
#include <string>

template <typename K, typename V>
std::vector<K>
extract_keys(std::map<K, V> const& input_map)
{
    std::vector<K> vec;
    for (auto const& element : input_map) {
        vec.push_back(element.first);
    }
    

    return vec;
}


template <typename K, typename V>
std::vector<V>
extract_values(std::map<K, V> const& input_map)
{
    std::vector<V> vec;
    for (auto const& element : input_map) {
        vec.push_back(element.second);
    }

    return vec;
}





#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

int main()
{
    std::map<int, std::string> m;
    for (int i=0; i < 20; ++i)
        m[i] = "TEST";

    auto keys = extract_keys(m);
    for (auto k : keys)
        std::cout << k << " ";
    std::cout << std::endl;

    auto values = extract_values(m);
    for (auto v : values)
        std::cout << v << " ";
    std::cout << std::endl;

    std::vector<int> output_vector;
    boost::copy(m | boost::adaptors::map_keys,
                std::back_inserter(output_vector));

    for (auto i : output_vector)
        std::cout << i << " ";
    std::cout << std::endl;
}
