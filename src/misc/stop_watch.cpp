
#include <chrono>
#include <iostream>

using clock_type = std::chrono::high_resolution_clock;

template <typename Precision = std::chrono::milliseconds>
class StopWatch
{
 public:
    using precision = Precision;

    StopWatch()
    {
        start_point_ = clock_type::now();
    }

    double elapsed()
    {
        auto end_point = clock_type::now();
        auto time = std::chrono::duration_cast<precision>(end_point - start_point);

        return time.count();
    }

 private:
    clock_type::time_point start_point_;
};
