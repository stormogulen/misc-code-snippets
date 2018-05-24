#ifndef __DISPATCH_QUEUE_HPP_INCLUDED__
#define __DISPATCH_QUEUE_HPP_INCLUDED__

#include <thread>
#include <functional>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>

#include <iostream>

class dispatch_queue
{
    using task_t = std::function<void()>;
    using unique_lock = std::unique_lock<std::mutex>;
    
 public:
    dispatch_queue(const std::string& name, size_t thread_count=1)
        : name_(name)
        , threads_(thread_count)
    {
        for (size_t i = 0; i < threads_.size(); ++i) {
            threads_[i] = std::thread(std::bind(&dispatch_queue::thread_handler, this));
        }
    }

    ~dispatch_queue()
    {     
        quit_ = true;
        condition_variable_.notify_all();

        for (size_t i = 0; i < threads_.size(); ++i) {
            if (threads_[i].joinable()) {
                threads_[i].join();
            }
        }
        
        // for (std::thread t : threads_) {
        //     if (t.joinable()) {
        //         t.join();
        //     }
        // }
    }

    dispatch_queue(const dispatch_queue& rhs) = delete;
    dispatch_queue& operator=(const dispatch_queue& rhs) = delete;
    dispatch_queue(dispatch_queue&& rhs) = delete;
    dispatch_queue& operator=(dispatch_queue&& rhs) = delete;
    

    void dispatch(const task_t& task)
    {
        unique_lock lock{mutex_};
        queue_.push(task);
        lock.unlock();
        condition_variable_.notify_all();
        
    }

    void dispatch(task_t&& task)
    {
        unique_lock lock{mutex_};
        queue_.push(std::move(task));
        lock.unlock();
        condition_variable_.notify_all();
    }

 private:
    void thread_handler()
    {
        unique_lock lock{mutex_};

        do {
            condition_variable_.wait(lock, [this] {
                    return (queue_.size() || quit_);
                });

            if (queue_.size() && !quit_) {
                auto func = std::move(queue_.front());
                queue_.pop();
                lock.unlock();
                func();
                lock.lock();
            }
        } while (!quit_);
    }

    
    std::string name_;
    std::mutex mutex_;
    std::vector<std::thread> threads_;
    std::queue<task_t> queue_;
    std::condition_variable condition_variable_;
    bool quit_ = false;
};



#endif // !__DISPATCH_QUEUE_HPP_INCLUDED__
