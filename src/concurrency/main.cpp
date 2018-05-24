#include <iostream>
#include <thread>
#include "concurrent_queue.hpp"
#include "shared_queue.hpp"
#include "channel.hpp"
#include "lockfree_queue.hpp"
#include "dispatch_queue.hpp"

// Testing thread safety for copy constructor etc.

class A
{
 public:
    A() : i_(0) {}
    
    A(const A& a) : A(a, std::lock_guard<std::mutex>(a.mtx_))
    {
    }

 private:
    A(const A& a, const std::lock_guard<std::mutex>&)
        : i_(a.i_), i_squared_(a.i_squared_)
    {
    }

    mutable std::mutex mtx_;
    int i_;
    int i_squared_;
};


void test(A& a)
{
    A a1 = a;
}

concurrent_queue<int> q;
concurrent_queue<int> copy_q;


void setup_queue(int max, int interval)
{
    
    for (int i=0; i < max; ++i) {
        if ((i % interval) == 0) {
            q.push(i);
        }
    }
}

void pop_queue(int max, int interval)
{
    for (int i=0; i < max; ++i) {
        if ((i % interval) == 0) {
            q.pop();
        }
    }
}

int main()
{
    A a;
    test(a);

    int qmax = 100;

    concurrent_queue<float> aa1;
    concurrent_queue<float> aa2;

    aa1.push(1.4);
    aa1.push(1.5);

    std::cout << aa1.size() << " " << aa2.size() << std::endl;

    aa2 = aa1;
    std::cout << aa1.size() << " " << aa2.size() << std::endl;
    
    std::thread q1(setup_queue, qmax, 1);
    std::thread q2(setup_queue, qmax, 4);
    std::thread q3(setup_queue, qmax, 8);
    std::thread q4(setup_queue, qmax, 10);
    q1.join();
    q2.join();
    q3.join();
    q4.join();

    std::cout << q.size() << std::endl;

    std::thread p1(pop_queue, qmax, 1);
    std::thread p2(pop_queue, qmax, 4);
    std::thread p3(pop_queue, qmax, 8);
    std::thread p4(pop_queue, qmax, 10);
    p1.join();
    p2.join();
    p3.join();
    p4.join();
    
    std::cout << q.size() << std::endl; 


    concurrent_queue<int> t1;
    
    t1.push(4);
    std::cout << "t1.size(): " << t1.size() << '\n';
    t1.push(2);
    std::cout << "t1.size(): " << t1.size() << '\n';
    int n = t1.pop();

    std::cout << "n = " << n << std::endl;
    
    shared_queue<int> sq;
    channel<int> ch;    
    lockfree_queue<int, 20> lfq;

    {
        dispatch_queue dq("Dispatch Queue", 4);

        dq.dispatch([]{printf("Dispatch 1!\n");});
        dq.dispatch([]{printf("Dispatch 2!\n");});
        dq.dispatch([]{printf("Dispatch 3!\n");});
        dq.dispatch([]{printf("Dispatch 4!\n");});
    }
    std::cout << "Done!\n";

}
