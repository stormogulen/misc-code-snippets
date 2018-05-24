#include "index.hpp"
#include "stream.hpp"
#include <algorithm>
#include <atomic>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <future>

/*
  clang -D_HASH=$(git rev-parse --short HEAD), in code:
  #define STR_EXPAND(tok) #tok
  #define STR(tok) STR_EXPAND(tok)

  STR(_HASH)
*/


class Counter
{
 public:
    constexpr Counter()
    : value_(0)
    {
    }

    constexpr void increment()
    {
        ++value_;
    }
    constexpr void decrement()
    {
        --value_;
    }

    constexpr int counter()
    {

        return value_.load();
    }

 private:
    std::atomic<int> value_;
};

void
test_counter()
{
    Counter counter;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([&counter]() {
                    for (int i = 0; i < 500; ++i)
                        counter.increment();
                }));
    }
    for (auto& thread : threads)
        thread.join();

    std::cout << counter.counter() << std::endl;
}

inline unsigned int
sdbm_hash(const std::string& key)
{
    unsigned int result = 0;

    for (unsigned int i = 0; i < key.length(); ++i) {
        int c  = key[i];
        result = static_cast<unsigned int>(c) + (result << 6) + (result << 16) - result;
    }

    return result;
}

std::string
trim_left(const std::string& str)
{
    auto tmp = str;
    tmp.erase(std::begin(tmp),
              std::find_if(std::begin(tmp), std::end(tmp), [](char c) {
                      return !std::isspace(c, std::locale());
                  }));

    return tmp;
}

std::string
trim_right(const std::string& str)
{
    auto tmp = str;
    tmp.erase(std::find_if(std::rbegin(tmp),
                           std::rend(tmp),
                           [](char c) { return !std::isspace(c, std::locale()); })
              .base(),
              std::end(tmp));

    return tmp;
}

std::string
trim(const std::string& str)
{
    return trim_left(trim_right(str));
}

constexpr static const char* begin_msg = "--- - BEGIN ---\n";
constexpr static const char* end_msg   = "--- - END   ---\n";



int some_computation(int x)
{
    for (int i=0; i < 999999999; ++i) {
        x++;
    }

    return x;
}


void
test_computation()
{
    std::packaged_task<int(int)> task1(&some_computation);
    std::packaged_task<int(int)> task2(&some_computation);

    std::future<int> val1 = task1.get_future();
    std::future<int> val2 = task2.get_future();

    // Schedule promises
    std::thread t1(std::move(task1), 0);
    std::thread t2(std::move(task2), 5);


    using namespace std;
    // Print status while we wait
    bool s1 = false, s2 = false;
    do {
        s1 = val1.wait_for(chrono::milliseconds(50)) == future_status::ready;
        s2 = val2.wait_for(chrono::milliseconds(50)) == future_status::ready;
        cout<< "Value 1 is " << (s1 ? "" : "not ") << "ready" << endl;
        cout<< "Value 2 is " << (s2 ? "" : "not ") << "ready" << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    } while (!s1 || !s2);

    // Cleanup threads-- we could obviously block and wait for our threads to finish if we don't want to print status.
    t1.join();
    t2.join();

    // Final result
    cout<< "Value 1: " << val1.get() << endl;
    cout<< "Value 2: " << val2.get() << endl;
}


template <typename T, std::size_t N>
class array_result
{
 public:
    constexpr std::size_t size() const { return N; }
    constexpr T& operator[](std::size_t n)
    {
        return data_[n];
    }

    constexpr const T& operator[](std::size_t n) const
    {
        return data_[n];
    }

    using iterator = T*;

    constexpr iterator begin() { return &data_[0]; }
    constexpr iterator end() { return &data_[N]; }

 private:
    constexpr static std::size_t size_ = N;
    T data_[N] { };
};


template <std::size_t N>
constexpr auto
constexpr_to_upper(const char(&in)[N])
    -> array_result<char, N>
{
    array_result<char, N> out;
    for (std::size_t i=0; in[i] != 0; ++i) {
        char c = in[i];
        out[i] = ((c < 'a') || (c > 'z')) ? c : c - ('a' - 'A');
    }

    return out;
}


void
test_constexpr_to_upper()
{
    static constexpr auto a = constexpr_to_upper("Ulf Ejlertsson");
    static_assert(a.size() == 15, "Noooooooo!");
    static_assert(a[a.size() - 2] == 'N', "noooooooo");
    std::cout << &a[0] << std::endl;
    std::cout << a.size() << std::endl;
}




void
test_hash_async()
{
    auto a = std::async(std::launch::async, sdbm_hash, "constant_string_1");
    auto b = std::async(std::launch::async, sdbm_hash, "constant_string_2");
    auto c = std::async(std::launch::async, sdbm_hash, "constant_string_3");

    std::cout << "constant 1" << a.get() << "\n";
    std::cout << "constant 2" << b.get() << "\n";
    std::cout << "constant 3" << c.get() << "\n";
}

std::vector<int>
generate_hash_codes(const std::vector<std::string>& v)
{
    std::vector<int> vec;
    for (auto i : v) {
        vec.emplace_back(sdbm_hash(i));
    }

    return vec;
}

std::vector<std::string>
generate_test_strings()
{
    std::vector<std::string> v;
    for (int i=0; i < 50; ++i) {
        std::string s = "String_constant_" + std::to_string(i);
        v.emplace_back(s);
    }

    return v;
}

void
test_hash_vector()
{
    std::vector<std::string> ids = generate_test_strings();
    std::size_t const half_length = ids.size() >> 1;
    std::vector<std::string> v1(ids.begin(), ids.begin() + static_cast<long>(half_length));
    std::vector<std::string> v2(ids.begin() + static_cast<long>(half_length), ids.end());

    std::cout << "launch A\n";
    auto a = std::async(std::launch::async, generate_hash_codes, v1);
    std::cout << "launch B\n";
    auto b = std::async(std::launch::async, generate_hash_codes, v2);

    auto hc1 = a.get();
    auto hc2 = b.get();

    std::cout << "hc1" << std::endl;
    for (auto i : hc1)
        std::cout << i << std::endl;

    std::cout << "hc2" << std::endl;
    for (auto i : hc2)
        std::cout << i << std::endl;
}


//
//if( equal(vector1.begin(), vector1.end(), vector2.begin()) )

#include <iomanip>

int
main()
{
    std::cout << begin_msg;
    std::cout << "----------------------------\n";
    test_counter();

    std::string s = "TEST_STRING";

    std::cout << s << " - " << sdbm_hash(s) << std::endl;
    std::cout << sdbm_hash(trim_left("     " + s)) << std::endl;
    std::cout << sdbm_hash(trim_right(s + "     ")) << std::endl;
    std::cout << sdbm_hash(trim("    " + s + "     ")) << std::endl;
    std::cout << end_msg;

    Index index;
    index.set_value(42);
    std::cout << index.value() << std::endl;
    Index index2;

    auto half = [](auto n) {return n >> 1; };
    std::cout << "half: " << half(index.value()) << std::endl;

    test_computation();

    run();
    test_constexpr_to_upper();
    test_stream();
    std::cout << index.value() << std::endl;

    test_hash_async();

    std::vector<std::string> codes = generate_test_strings();
    for (auto i : codes)
        std::cout << i << std::endl;

    std::vector<int> hash_codes = generate_hash_codes(codes);
    for (auto i : hash_codes)
        std::cout << i << std::endl;


    test_hash_vector();
    std::string str = "Meet the new boss...";
    std::size_t str_hash = std::hash<std::string>{}(str);
    std::cout << "hash(" << std::quoted(str) << ") = " << str_hash << '\n';
}
