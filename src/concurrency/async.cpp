#include <iostream>
#include <future>
#include <numeric>
#include <vector>

int
accumulate_block_worker(int* data, size_t count)
{
    return std::accumulate(data, data + count, 0);
}


void use_worker_in_std_async()
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    std::future<int> f = std::async(std::launch::async, accumulate_block_worker, v.data(), v.size());
    std::cout << "use_worker_async: " << f.get() << '\n';
}


using int_futures = std::vector<std::future<int>>;

int_futures launch_split_workers_with_std_async(std::vector<int>& v)
{
    int_futures futures;
    futures.push_back(std::async(std::launch::async, accumulate_block_worker,
                                 v.data(), v.size() / 2));
    futures.push_back(std::async(std::launch::async, accumulate_block_worker,
                                 v.data() + v.size() / 2, v.size() / 2));
    return futures;
}


void test()
{
    // Usage
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    int_futures futures = launch_split_workers_with_std_async(v);
    std::cout << "results from launch_split_workers_with_std_async: "
              << futures[0].get() << " and " << futures[1].get() << "\n";
}


template <typename F, typename... Ts>
inline auto reallyAsync(F&& f, Ts&&... params)
{
    return std::async(std::launch::async, std::forward<F>(f),
                      std::forward<Ts>(params)...);
}

#include <atomic>
#include <thread>

struct Counter
{
    Counter() : value(0) { }

    std::atomic<int> value;

    void increment() { ++value; }
    void decrement() { --value; }

    int get() { return value.load(); }
};

void test_counter()
{
    Counter counter;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([&counter]()
                                      {
                                          for (int i = 0; i < 500; ++i) {
                                              counter.increment();
                                          }
                                      }));
    }

    for (auto& thread : threads){
        thread.join();
    }

    std::cout << counter.get() << std::endl;
}


int main()
{
    use_worker_in_std_async();
    test();
    test_counter();

}
