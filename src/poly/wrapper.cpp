// -----------------------------------------------------------------------------
// wrapper.cpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#include <iostream>
#include <string>
#include <cstdlib>

void print_prefix() { std::cout << "prefix\n"; }
void print_suffix() { std::cout << "suffix\n"; }

class Object
{
 public:
    Object(std::string name) : name_(name) { }

    void print_name()
    {
        std::cout << name_ << std::endl;
    }

    std::string name() const { return name_; }

 private:
    std::string name_;
};

template <typename T>
class CallProxy
{
 public:
    CallProxy(T* p) : ptr_(p) { }
    ~CallProxy()
    {
        print_suffix();
    }

    T* operator->() { return ptr_; }

 private:
    T* ptr_;
};
        

template <typename T>
class Wrap
{
 public:
    Wrap(T* p) : ptr_(p) { }

    CallProxy<T> operator->()
    {
        print_prefix();
        return CallProxy<T>(ptr_);
    }

 private:
    T* ptr_;
};

//////////////////////
template <typename T>
struct Wrapper : public T
{
    virtual size_t size() const
    {
        return sizeof(T);
    }

 protected:
    //Wrapper() { }
};

template <typename T>
T* create()
{
    return new Wrapper<T>;
}


struct Base
{
    virtual size_t size() const = 0;
};

struct Derived : public Base
{
    int x;
};



int main()
{
    Wrap<Object> object(new Object("test.object"));
    object->print_name();
    std::cout << object->name() << std::endl;

    Base* b = create<Derived>();
    size_t s = b->size();

    std::cout << "size: " << s << std::endl;
}
