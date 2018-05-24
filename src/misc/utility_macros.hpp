inline constexpr auto likely(bool b) noexcept
{
    return __builtin_expect(b, true);
}

inline constexpr auto unlikely(bool b) noexcept
{
    return __builtin_expect(b, false);
}

enum class Compiler
{
    CLANG,
    GCC,
    MSVC,
    UNKNOWN
};

inline constexpr auto current_compiler() noexcept
{
#ifdef __clang__
    return Compiler::CLANG;
#elif __GNUC__
    return Compiler::GCC;
#eldif __MSC_VER
    return Compiler::MSVC;
#else
    return Compiler::UNKNOWN;
#endif
}


enum class Architecture
{
    x86,
    x64,
    UNKNWON
};


#if(defined(WIN_32) || defined(__i386__) || defined(i386) || defined(__x86__))
#define ARCH_32 1
#elif (defined(__amd64) || defined(__amd64__) || defined(__x86_64) ||   \
       defined(__x86_64__) || defined(_M_X64) || defined(__ia64__) ||   \
       defined(_M_IA64))
#define ARCH_64 1
#else
#define ARCH_UNKNOWN 1
#endif



inline constexpr auto current_architecture() noexcept
{
#if defined(ARCH_32)
    return Architecture::x86;
#elif defined(ARCH_64)
    return Architecture::x64;
#else
    return Architecture::UNKNOWN;
#endif
}
