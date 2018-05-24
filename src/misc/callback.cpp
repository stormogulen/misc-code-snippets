#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

// url: https://sudomakeinstall.io/posts/2017/11/30/callbacks-in-cpp11/



void
function_pointer_callback(const size_t iteration, const double guess)
{
    std::cout << iteration << " : " << guess << " (function pointer)\n";
}

class MemberFunctionCallback
{
 public:
    void call(const size_t iteration, const double guess)
    {
        std::cout << iteration << " : " << guess << " (member function)\n";
    }
};


class FunctorCallback
{
 public:
    void operator()(const size_t iteration, const double guess)
    {
        std::cout << iteration << " : " << guess << " (functor)\n";
    }
};


class SquareRoot
{
 public:
    using Callback = std::function<void(const size_t, const double)>;
    using CallbackVector = std::vector<Callback>;

    void add(Callback cb)
    {
        callbacks_.emplace_back(cb);
    }

    double run(const double input)
    {
        if (input < 0.0)
            throw 0;

        iteration_ = 0;
        double guess = input;

        while (std::fabs(guess - input/guess) > epsilon_) {
            for (const auto& cb : callbacks_) {
                cb(iteration_, guess);
            }

            guess = (guess + input/guess) / 2.0;
            ++iteration_;
        }

        return guess;
    }


 private:
    const double epsilon_ = 1e-6;
    size_t iteration_;

    CallbackVector callbacks_;
};


int main()
{
    SquareRoot sq;

    //auto fun_ptr_callback = function_pointer_callback;
    //sq.add(fun_ptr_callback);
    sq.add(function_pointer_callback);

    MemberFunctionCallback mem_fun_callback;
    auto mem_cb = std::bind(&MemberFunctionCallback::call,
                            &mem_fun_callback,
                            std::placeholders::_1,
                            std::placeholders::_2);

    sq.add(mem_cb);


    FunctorCallback functor_callback;
    sq.add(functor_callback);

    auto lambda = [](const size_t iteration, const double guess) {
        std::cout << iteration << " : " << guess << " (lambda)\n"; };
    sq.add(lambda);

    std::cout << "result: " << sq.run(1234.5*1234.5) << std::endl;
}
