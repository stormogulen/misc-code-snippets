// -----------------------------------------------------------------------------
// object.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __OBJECT_OBJECT_HPP_INCLUDED__
#define __OBJECT_OBJECT_HPP_INCLUDED__

#include <iostream>
#include <string>
#include <vector>

//! Print objects.
template <typename T>
void print(const T& x)
{
    std::cout << x << std::endl;
}

//! Object class.
/**
   The runtime-concept idiom allows polymorphism when needed without
   inheritance.
   Client isn't burdened with inheritance, factories, class
   registration, and memory management.
 */
class Object
{
 public:
    //! Constructor.
    template <typename T>
    explicit Object(const T& x) : object_(new Model<T>(x))
    {
    }

    //! Destructor.
    ~Object();

    //! Copy constructor.
    Object(const Object& x);
   
    //! Assignment operator.
    /**
       Pass sink arguments by value and swap or move into place. 
     */
    Object& operator=(Object x);
    
    //! Print objects.
    friend void print(const Object& x);

    //! A non-throwing swap function.
    friend void swap(Object& x, Object& y);

 private:
    struct Concept
    {
        virtual ~Concept() { }
        virtual void print_() const = 0;
        virtual Concept* copy_() const = 0;
    };

    template <typename T>
    struct Model : Concept
    {
        explicit Model(const T& x) : data(x) { }
        Concept* copy_() const { return new Model(data); }
        void print_() const { print(data); }

        T data;
    };

    Concept* object_;
};

// Friend function.
inline void swap(Object& x, Object& y)
{
    std::swap(x.object_, y.object_);
}

// Friend function.
inline void print(const Object& x)
{
    x.object_->print_();
}


#endif // !__OBJECT_OBJECT_HPP_INCLUDED__

/* End of File */
