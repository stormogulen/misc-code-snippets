#ifndef __EXECUTOR_HPP_INCLUDED__
#define __EXECUTOR_HPP_INCLUDED__

#include <thread>
#include <string>
#include "concurrent_queue.hpp"
#include <functional>
#include <future>
#include <memory>

// Got most of the information from here:
// https://github.com/CasparCG/server/blob/master/src/common/executor.h
// https://stackoverflow.com/questions/6230893/developing-c-concurrency-library-with-futures-or-similar-paradigm

template <typename T>
class executor
{
 public:
    typedef std::function<void()>  task_t;
    
    explicit executor(const std::string& name = "executor")
        : name_(name)
        , thread_(std::thread([this] { run(); }))
    {
    }
    
    ~executor()
    {
        stop();
        thread_.join();
    }

    executor(const executor&) = delete;
    executor& operator=(const executor&) = delete;

    template <typename F>
    auto begin_invoke(F&& func)
    {
        if (!is_running_) {
            std::cerr << "Not running!";
        }

        typedef decltype(func()) result_type;
        auto task = std::make_shared<std::packaged_task<result_type()>>(std::forward<F>(func));

        return task->get_future();
    }

    template <typename F>
    auto 
    invoke(F&& func) -> decltype(func())
    {
        if (std::this_thread::get_id() == thread_.get_id()) {
            return func();
        }
        
        return begin_invoke(std::forward<F>(func)).get();
    }
 
    void stop() { }
    void wait() { invoke([] {}); }
    
    
 private:
    void run()
    {
        while (true) {
            std::function<void()> func;
            queue_.try_pop(func);
            if (!func) {
                break;
            }
            func();
        }
    }
    
    std::string name_;
    concurrent_queue<task_t> queue_;
    std::thread thread_;
    std::atomic<bool> is_running_{true};
};



#endif // !__EXECUTOR_HPP_INCLUDED__
