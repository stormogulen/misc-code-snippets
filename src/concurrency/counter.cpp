#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

class Counter {
 public:
    constexpr Counter() : value_(0) {}

    constexpr void increment() { ++value_; }
    constexpr void decrement() { --value_; }

    constexpr int counter() { return value_.load(); }

 private:
    std::atomic<int> value_;
};

void test_counter() {
    Counter counter;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([&counter]() {
                    for (int i = 0; i < 500; ++i)
                        counter.increment();
                }));
    }
    for (auto &thread : threads)
        thread.join();

    std::cout << counter.counter() << std::endl;
}

inline unsigned int sdbm_hash(const std::string &key) {
    unsigned int result = 0;

    for (unsigned int i = 0; i < key.length(); ++i) {
        int c = key[i];
        result = c + (result << 6) + (result << 16) - result;
    }

    return result;
}

int main() {
    std::cout << "----------------------------\n";
    test_counter();

    std::cout << "bad_access"
              << " - " << sdbm_hash("bad_access");
}
