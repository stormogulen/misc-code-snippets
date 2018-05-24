#include <chrono>
#include <string>

class Constants
{
 public:
  
    //
    // Common
    //

    // An error response string
    static const std::string ERROR_RESPONSE;

    // Successful reply
    static const std::string SUCCESS_RESPONSE;

    // constexpr char constString[] = "constString";
    static constexpr auto constString = "constString";

    // Break from the poll waiting
    static constexpr std::chrono::milliseconds POLL_TIMEOUT{50};

    // Max time we wait for read data on a socket
    static constexpr std::chrono::milliseconds READ_TIMEOUT{1000};
};

// Impl
const std::string Constants::ERROR_RESPONSE{"ERR"};

const std::string Constants::SUCCESS_RESPONSE{"OK"};



struct StringUtil
{
    static std::string concat_1(const std::string& str1, std::string& str2)
    {
        return str1 + str2;
    }
};
