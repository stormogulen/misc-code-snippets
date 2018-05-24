#include <functional>
#include <algorithm>


bool odd(unsigned int n) { return n & 0x1; }
int half(unsigned int n) { return n >> 1;  }

unsigned int gcd(unsigned int a, unsigned int b)
{
    while (b != 0) {
        a = a % b;
        std::swap(a, b);
    }

    return a;
}

template <typename T>
bool odd(T n)
{
    return bool(n & 0x1);
}

template <typename T>
T half(T n)
{
    return n >> 1;
}

template <typename T>
bool divides(const T& i, const T&n)
{
    return n % i == T(0);
}

template <typname T>
T smallest_divisor(T n)
{
    // precondition n > 0
    if (even(n)) {
        return T(2);
    }

    for (T i(3); n >= i * i; i += T(2)) {
        if (divides(i, n)) {
            return i;
        }
    }

    return n;
}

template <typename T>
T is_prime(const T& n)
{
    return n > T(1) && smallest_divisor(n) == n;
}

template <typename T>
bool positive(const T& a)
{
    return T(0) < a;
}

template <typename T>
bool negative(const T& a)
{
    return a < T(0);
}

template <typename T>
bool zero(const T& a)
{
    return a == T(0);
}

template <typename T>
bool one(const T& a)
{
    return a == T(1);
}




class INotification
{
 public:
    virtual void onCompleted() = 0;
};
using INotificationHolder = std::function<INotification&()>;

template<typename T, typename... Args>
INotificationHolder make_inotify(Args... args)
{
    return [impl=T(std::forward<Args>(args)...)]() mutable -> INotification& {
        return impl;
    };
}

class Implementation : public INotification
{
    void onCompleted() override {}
};

class Executer
{
 public:
    void submit(INotificationHolder holder)
    {
        holder().onCompleted();
    }
};

int main(int argc, char * argv[])
{
    Executer executer;
    executer.submit(make_inotify<Implementation>());
}
