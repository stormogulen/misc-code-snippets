#ifndef __SHARED_QUEUE_HPP_INCLUDED__
#define __SHARED_QUEUE_HPP_INCLUDED__


#include <queue>
#include <mutex>
#include <exception>
#include <condition_variable>

//  Multiple producer, multiple consumer thread safe queue

template<typename T>
class shared_queue
{
 public:

    using guard = std::lock_guard<std::mutex>;

    shared_queue() {}
    shared_queue& operator=(const shared_queue&) = delete;
    shared_queue(const shared_queue& other) = delete;

    void push(T item)
    {
        {
            guard g{mutex_};
            queue_.push(std::move(item));
        }
        condition_variable_.notify_one();
    }

    bool try_and_pop(T& popped_item)
    {
        guard g{mutex_};
        if (queue_.empty()) {
            return false;
        }
        popped_item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void wait_and_pop(T& popped_item)
    {
        guard g{mutex_};
        while (queue_.empty()) {
            condition_variable_.wait(g);
        }
        popped_item = std::move(queue_.front());
        queue_.pop();
    }

    bool empty() const
    {
        guard g{mutex_};
        return queue_.empty();
    }

    unsigned size() const
    {
        guard g{mutex_};
        return queue_.size();
    }

 private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_variable_;


};

#endif // !__SHARED_QUEUE_HPP_INCLUDED__
