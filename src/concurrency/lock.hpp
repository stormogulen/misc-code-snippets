#ifndef __LOCK_HPP_INCLUDED__
#define __LOCK_HPP_INCLUDED__


#include <mutex>
#include <vector>
#include <deque>
#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>

template <typename M, typename F, typename... Args> 
auto lock_guard(M& mtx, F&& f, Args&&... args)
{
    std::lock_guard<M> guard(mtx);
    return std::forward<F>(f)(std::forward<Args>(args)...);
}


#endif // !__LOCK_HPP_INCLUDED__
