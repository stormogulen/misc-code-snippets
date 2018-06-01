#ifndef __EXCEPT_HPP_INCLUDED__
#define __EXCEPT_HPP_INCLUDED__

#include <exception>
#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <boost/stacktrace.hpp>

namespace xyz {

std::string u8(const std::wstring& str)
{
    return boost::locale::conv::utf_to_utf<char>(str); // std::string(str.begin(), str.end());
}

std::string u8(const std::string& str) { return str; }

using arg_name_info_t = boost:error_info<struct tag_arg_name_info, std::string>;

template <typename T>
inline arg_name_info_t arg_name_info(const T& str)
{
    return arg_name_info_t(u8(str));
}


// class bad_any_cast : public std::bad_cast
// {
//  public:
//     const char* what() const noexcept override
//     {
//         return "bad any cast";
//     }
// };



struct SystemException
    : virtual boost::exception
    , virtual std::exception
{
    SystemException() { }
    const char* what() const throw() override
    {
        return boost::diagnostic_information_what(*this);
    }
};


struct IOError : virtual SystemException
{
};


#define THROW_SYSTEM_EXCEPTION(x)                                       \
    ::boost::throw_exception(::boost::enable_error_info(x)              \
                             << ::boost::throw_function(BOOST_THROW_EXCEPTON_CURRENT_FUNCTION) \
                             << ::boost::throw_file(__FILE__) << ::boost::throw_line((int)__LINE__) \
                             << stacktrace_info())                      


} // namespace xyz

#endif // !__EXCEPT_HPP_INCLUDED__
