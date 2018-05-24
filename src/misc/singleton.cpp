// url: http://mariusbancila.ro/blog/2017/01/16/dining-philosophers-in-cpp11/
// url: http://mariusbancila.ro/blog/2017/01/20/dining-philosophers-in-c11-chandy-misra-algorithm/
// url: http://howardhinnant.github.io/dining_philosophers.html


#include <iostream>
#include <mutex>

class Singleton
{
 public:
    Singleton() = default;

    static void notify_init()
    {
        std::cout << "initializing singleton\n";
    }

    static Singleton& instance()
    {
        std::call_once(Singleton::once_flag_, []() {
                notify_init();
                instance_.reset(new Singleton);
            });

        std::cout << "getting singleton instance\n";
        return *(instance_.get());
    }

 private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static std::unique_ptr<Singleton> instance_;
    static std::once_flag once_flag_;
};

std::unique_ptr<Singleton> Singleton::instance_;
std::once_flag Singleton::once_flag_;

int main()
{
    Singleton& s1 = Singleton::instance();
    Singleton& s2 = Singleton::instance();
}
