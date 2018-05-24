#include <memory>
#include <string>

class Index
{
 public:
    Index();
    ~Index();

    Index(Index&&);
    Index& operator=(Index&&);
    int    value() const;
    void set_value(const int v);

 private:
    class IndexImpl;
    std::unique_ptr<IndexImpl> pimpl_;
};

void run();
std::string reverse_string(const std::string& s);
