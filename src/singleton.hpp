// -----------------------------------------------------------------------------
// singleton.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __SRC_SINGLETON_HPP_INCLUDED__
#define __SRC_SINGLETON_HPP_INCLUDED__

#include <boost/utility.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>

//
// usage:
//
//class TestSingleton : public Singleton<TestSingleton>
//{
//    friend class Singleton<TestSingleton>;
//      
// private:
//    TestSingleton() { }
//};
//

template <typename T>
class Singleton : private boost::noncopyable
{
 public:
    static T& instance()
    {
        boost::call_once(init, flag_);
        return *instance_;
    }
    
    static void init()  // never throws
    {
        instance_.reset(new T());
    }
    
 protected:
    Singleton() { }
    ~Singleton() { }
    
 private:
    static boost::scoped_ptr<T> instance_;
    static boost::once_flag flag_;
};


template <typename T>
boost::scoped_ptr<T> Singleton<T>::instance_(0);

template <typename T>
boost::once_flag Singleton<T>::flag_ = BOOST_ONCE_INIT;


#endif // !__SRC_SINGLETON_HPP_INCLUDED__

/* End of File */
