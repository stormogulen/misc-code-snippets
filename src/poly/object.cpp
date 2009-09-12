// -----------------------------------------------------------------------------
// object.cpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#include "object.hpp"

Object::~Object()
{
    delete object_;
}

Object::Object(const Object& rhs)
    : object_(rhs.object_->copy_())
{
}

Object& Object::operator=(Object rhs)
{
    swap(*this, rhs);
    return *this;
}
