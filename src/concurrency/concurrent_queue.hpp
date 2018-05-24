
#include <queue>
#include <thread>
#include <condition_variable>

#ifndef __CONCURRENT_QUEUE_HPP_INCLUDED__
#define __CONCURRENT_QUEUE_HPP_INCLUDED__


// TODO: add template arguments for mutex and container type
// template<typename T, typename Container=std::queue<T>>

// NOTE: spin_mutex seems to be an Intel TBB/boost mutex for busy wait
// Got  this from concurrency in action
// #include <atomic>

// class spinlock_mutex
// {
//  public:
//     spinlock_mutex() : flag_(ATOMIC_FLAG_INIT) {}

//     void lock()
//     {
//         while (flag_.test_and_set(std::memory_order_acquire))
//             ;
//     }

//     void unlock()
//     {
//         flag_.clear(std::memory_order_release); 
//     }

//  private:
//     std::atomic_flag flag_;
// };


template <typename T>
class concurrent_queue
{
 public:
    
    using guard = std::lock_guard<std::mutex>;
    
    // ctor
    explicit concurrent_queue() = default;
    
    // dtor
    ~concurrent_queue() = default;
    
    // copy ctor
    concurrent_queue(const concurrent_queue& rhs)
    {
        //std::lock_guard<std::mutex> lock(mutex_);
        std::unique_lock<std::mutex> lock(mutex_);
        values_ = rhs.values_;
    }
    
    concurrent_queue operator=(concurrent_queue& other)
    {
        if (this != &other) {
            //std::shared_lock<std::shared_timed_mutex> lhs_lock(mutex_, std::defer_lock);
            //std::shared_lock<std::shared_timed_mutex> rhs_lock(other.mutex_, std::defer_lock);
            std::unique_lock<std::mutex> lhs_lock(mutex_, std::defer_lock);
            std::unique_lock<std::mutex> rhs_lock(other.mutex_, std::defer_lock);
            std::lock(lhs_lock, rhs_lock); // avoid deadlock
            values_ = other.values_; //std::move(other.values_);
        }

        return *this;
    }

    // move ctor
    concurrent_queue(concurrent_queue&& other)
    {
        std::unique_lock<std::mutex> lock(mutex_); 
        values_ = std::move(other.values_);
    }

    concurrent_queue& operator=(concurrent_queue&& other)
    {
        if (this != &other){
            std::unique_lock<std::mutex> lhs_lock(mutex_, std::defer_lock);
            std::unique_lock<std::mutex> rhs_lock(other.mutex_, std::defer_lock);
            std::lock(lhs_lock, rhs_lock);
            values_ = std::move(other.values_);
        }

        return *this;
    }

    void push(const T& value)
    {
        guard g{mutex_};
        //values_.push(value);
        values_.push(std::move(value));
        condition_variable_.notify_one();
    }

    void push(T&& value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        values_.push(std::move(value));
        lock.unlock();
        condition_variable_.notify_one();
    }
    
    T pop()
    {
        // Cannot use scoped lock here because lock passed to
        // wait must be able to acquire and release the mutex
        std::unique_lock<std::mutex> lock(mutex_);
        while (values_.empty()) {
            condition_variable_.wait(lock);
        }

        auto v = values_.front();
        values_.pop();
        
        return v;
    }
    
    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (values_.empty()) {
            return false;
        }
        // If the value is available
        //value = values_.front();
        value = std::move(values_.front());
        values_.pop();

        return true;
    }

    typename std::queue<T>::size_type size() const
    {
        guard g{mutex_};
        return values_.size();
    }
    
    bool empty() const
    {
        guard g{mutex_};
        return values_.empty();
    }
    
 private:
    mutable std::mutex mutex_;
    std::queue<T> values_; 
    std::condition_variable_any condition_variable_;
};

#endif // !__CONCURRENT_QUEUE_HPP_INCLUDED__
