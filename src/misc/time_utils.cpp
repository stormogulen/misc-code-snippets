//
// time_utils.cpp
//

#include <chrono>




inline uint64_t time_now_milliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
                                                                 .time_since_epoch())
        .count();
}

inline uint64_t time_now_microseconds()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()
                                                                 .time_since_epoch())
        .count();
}

inline std::chrono::milliseconds milliseconds_since_epoch()
{
    return std::chrono::duration_cast<ms_t>(system_clock_t::now().time_since_epoch());
}


// Used when getting a time to present to the user
using system_clock_t = std::chrono::system_clock;
using system_time_t = std::chrono::time_point<system_clock_t>;


// Get current system time
class system_time
{
 public:
    virtual ~system_time() {}

    virtual system_time_t current_time()
    {
        return std::chrono::system_clock::now();
    
    };
};


// Used when tracking time for computing an interval
using steady_clock_t = std::chrono::steady_clock;
using monotonic_time_t = std::chrono::time_point<steady_clock_t>; 

class monotonic_time
{
 public:
    virtual ~monotonic_time() {}

    virtual monotonic_time_t current_time()
    {
        return std::chrono::steady_clock::now();
    }
};

using high_resolution_lock_t = std::chrono::high_resolution_clock;
using ms_t = std::chrono::milliseconds;
using sec_t = std::chrono::seconds;



template <typename ClockType = steady_clock_t>
inline ms_t milliseconds_between(std::chrono::time_point<ClockType> finish,
                                 std::chrono::time_point<ClockType> start)
{
    return std::chrono::duration_cast<ms_t>(finish-start);
}


#include <iostream>
int main()
{
    std::cout << time_now_milliseconds() << std::endl;
    std::cout << time_now_microseconds() << std::endl;


    auto t1 = std::chrono::high_resolution_clock::now();
//process to be timed
    for (int i=0; i < 100000000; ++i) {
        auto j = i % 2;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "process took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds\n";

    auto took = milliseconds_between(t2, t1);
    std::cout << "time: " << std::chrono::duration_cast<ms_t>(took).count() << std::endl;
    
    system_time st;
    auto sys_time = st.current_time();
    std::cout << std::chrono::time_point_cast<std::chrono::milliseconds>(sys_time)
        .time_since_epoch()
        .count() << std::endl;


    monotonic_time mt;
    auto mono_time = mt.current_time();
    std::cout << std::chrono::time_point_cast<std::chrono::milliseconds>(mono_time)
        .time_since_epoch()
        .count()
              << std::endl;

}
