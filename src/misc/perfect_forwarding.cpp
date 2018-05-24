#include <iostream>
#include <string>

using namespace std;

struct A { };
struct B { int a; int b; };
struct C { int a; int b; string c; };
struct D
{
 public:
    D(int a) {}
};

struct E
{
    int& e;
    E(int& e) : e(e) { e++; }
};

template <typename T, typename ... ARGS>
unique_ptr<T> factory(ARGS&&... args)
{
    return unique_ptr<T>(new T { std::forward<ARGS>(args)... });
}

int main()
{
    auto a = factory<A>();
    auto b = factory<B>(10, 20);
    auto c = factory<C>(30, 40, "Hello");
    auto d = factory<D>(10);

    int x = 2;
    auto e = factory<E>(x);
    cout << x << endl;
}



using namespace std;

struct X
{
    X() { cout << "ctor" << endl; }
    X(const X&) { cout << "copy ctor" << endl; }
    X(X&&) { cout << "move ctor" << endl; }
};

struct Wrapper
{
    X w;

    template <typename Q>
    Wrapper(Q&& w) : w(std::forward<Q>(w)) { }
};

int main()
{
    Wrapper w1(X { });
    cout << "***" << endl;
    X y;
    Wrapper w2(y);
}
