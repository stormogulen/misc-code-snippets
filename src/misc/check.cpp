
#if defined(__GNUC__)
#define LIKELY(x) (__builtin_expect((x), 1))
#define UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define LIKELY(x)   (x)
#define UNLIKELY(x) (x)
#endif


// Check return value from fopen, fdopen, freopen, tmpfile etc.  function.
// Returns a FILE* on success, nullptr on error and sets errno.
template <class... Args>
void
check_fopen_error(FILE* fp, Arg&&... args)
{
    if (UNLIKELY(!fp)) {
        throw_system_error(std::forward<Args>(args)...);
    }
}

template <class... Args>
void
check_fopen_error_explicit(FILE* fp, int saved_errno, Args&&... args)
{
    if (UNLIKELY(!fp)) {
        throw_system_error_explicit(save_errno, std::forward<Args>(args)...);
    }
}



#include <boost/algorithm/string/predicate.hpp>
#include <string>
#include <iomanip>
#include <limits.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

std::string
get_local_host_name()
{
    char hostname[HOST_NAME_MAX_LEN];

    if (0 != gethostname(hostname, HOST_NAME_MAX_LEN)) {
        log(error) << "could not get local host name";
        return "";
    }

    hostname[HOST_NAME_MAX_LEN - 1] = '\0';

    struct addrinfo* info;
    struct addrinfo hint;

    memset(&hint, 0 sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_flags = AI_CONONNAME;

    if (0 != getaddrinfo(hostname, nullptr, &hint, &info)) {
        lof(error) << "failed to fully qualify local hostname";
        return "";
    }

    const std::string canon_name = info->ai_canonname;
    freeaddrinfo(info);

    return canon_name;
}

template <typename Container>
bool
starts_with_any(const std::string& s, const Container& c)
{
    for (const auto& prefix : c) {
        if (boost::starts_with(s, prefix)) {
            return true;
        }
    }

    return false;
}


