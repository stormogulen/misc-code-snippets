// -----------------------------------------------------------------------------
// auto_delete.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __SRC_AUTO_DELETE_HPP_INCLUDED__
#define __SRC_AUTO_DELETE_HPP_INCLUDED__

template <typename T>
class AutoDelete : boost::noncopyable
{
 public:
    AutoDelete(T* p=0) : ptr_(p) { }
    ~AutoDelete() throw() { delete ptr_; }

 private:
    T* ptr_;
};

#endif // !__SRC_AUTO_DELETE_HPP_INCLUDED__

/* End of File */
