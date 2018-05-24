#include <chrono>


void init_uptime();
std::chrono::steady_clock::time_point get_boot_time();
std::chrono::steady_clock::duration get_uptime();


static std::chrono::steady_clock::time_point boot_time;

void
init_uptime()
{
    boot_time = std::chrono::steady_clock::now();
}

std::chrono::steady_clock::time_point
get_boot_time()
{
    return boot_time;
}

std::chrono::steady_clock::duration
get_uptime()
{
    return std::chrono::steady_clock::now() - boot_time;
}


//! Keep track of latencies

class LatencyCounter
{
 public:
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration = clock::duration;

    bool is_start() const
    {
        return start_.time_since_epoch().count();
    }

    LatencyCounter& stop()
    {
        stop_ = now();
        return *this;
    }

    bool is_stopped() const
    {
        return stop_.time_since_epoch().count();
    }

    duration latency() const 
    {
        return stop_ - start_;
    }

    LatencyCounter& check_and_stop()
    {
        if (!is_stopped()) {
            return stop();
        }

        return *this;
    }

    static time_point now()
    {
        return clock::now();
    }
	
 private:
    time_point start_;
    time_point stop_;
};


bool
super_duper_query()
{
    for (int i=0; i < 100000; ++i) {
        i += i*i;
    }
    return true;
}


void function()
{
    LatencyCounter lc;
    lc.start();

    if (super_duper_query()) {
        lambda {
            lc.stop();
            if (lc.is_start()) {
                read(lc.latency());
            }
        }
    }

}

int main()
{
    function();
}
