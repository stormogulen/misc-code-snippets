// -----------------------------------------------------------------------------
// main.cpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#include <iostream>
#include <vector>
#include <string>

#include "object.hpp"

typedef std::vector<Object> document_t;

void print(const document_t& x)
{
    std::cout << "<document>" << std::endl;
    std::for_each(x.begin(), x.end(), (void (*)(const Object&))(&print));
    std::cout << "</document>" << std::endl;
}

Object function() { return Object(5); }

struct TestClass
{
};

void print(const TestClass& x)
{
    std::cout << "TestClass" << std::endl;
}

int main()
{
    document_t document;

    document.push_back(Object(0));
    document.push_back(Object(std::string("Hello")));
    document.push_back(Object(2));
    document.push_back(Object(3));
    document.push_back(Object(TestClass()));

    print(document);

    Object x(0);
    x = function();
}
