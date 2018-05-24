#include <string>
#include <iostream>
#include <algorithm> 
#include <cctype>
#include <locale>



std::string
trim_left(const std::string& s)
{
    std::string /*auto*/ tmp = s;

    const auto tmp_beg = tmp.begin();
    const auto tmp_end = tmp.end();

    tmp.erase(tmp_beg,
              std::find_if(tmp_beg, tmp_end,
                           [](char c){ return !std::isspace(c, std::locale());
                           }));
  
#if 0
    tmp.erase(std::begin(tmp),
              std::find_if(std::begin(tmp), std::end(tmp),
                           [](char c){ return !std::isspace(c, std::locale());
                           }));
#endif
    return tmp;
}

std::string
trim_right(const std::string& s)
{
    std::string /*auto*/ tmp = s;

    const auto tmp_rbeg = tmp.rbegin();
    const auto tmp_rend = tmp.rend();

    tmp.erase(std::find_if(tmp_rbeg, tmp_rend,
                           [](char c){ return !std::isspace(c, std::locale()); }).base(),
              std::end(tmp));
#if 0
    tmp.erase(std::find_if(std::rbegin(tmp), std::rend(tmp),
                           [](char c){ return !std::isspace(c, std::locale()); }).base(),
              std::end(tmp));
#endif
    return tmp;
}


std::string
trim(const std::string& s)
{
    return trim_left(trim_right(s));
}

std::string
replace_str(const std::string& in, const std::string& what, const std::string& new_str)
{ 
#if 0
    size_t what_len = what.length();
    if (what_len == 0) {
        return in;
    }
  
    size_t new_len = new_str.length();
    size_t pos = in.find(what);
    std::cout << pos << std::endl;
    std::string tmp(in);

    while (pos != std::string::npos) {
        std::cout << what_len << " - " << new_len << std::endl;
        if (what_len > new_len) {
            tmp.erase(pos, what_len-new_len);
            std::cout << "pos\n";
        }
        else if (what_len < new_len) {
            tmp.insert(pos, new_len-what_len, '*');
            std::cout << pos << std::endl;;
        }

        tmp.replace(pos, new_str.length(), new_str);
        pos = tmp.find(what);
    }

    return tmp;
#endif
    return "NOT WORKING!\n";
}


template <typename T>
std::ostream&
operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    std::string comma;

    for (auto& v: vec) {
        os << comma << v;
        comma = ", ";
    }
    os << "]";

    return os;
}


template <typename T>
void
insertion_sort(T start, T end)
{
    for (auto i=start; i != end; ++i) {
        std::rotate(std::upper_bound(start, i, *i), i, std::next(i));
    }
}

void insertion_sort_test()
{
    std::vector<int> v{4, 2, 5, 8, 1, 9, 6};
    std::cout << v << std::endl;
    insertion_sort(std::begin(v), std::end(v));
    std::cout << v << std::endl;
}
  


int main()
{
    std::string s = "                This is a string that needs to be trimmed!     ";
    std::cout << s << " [size: " << s.size() << "]" << std::endl;
    std::cout << "\nTrimmed:\n" << trim(s) << " [size: " << s.size() << "]" << std::endl;
    //s = replace_str(s, "string", "std::string");
    //  std::cout << s << std::endl;

  
    insertion_sort_test();
  
}
