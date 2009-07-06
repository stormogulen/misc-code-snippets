// -----------------------------------------------------------------------------
// defs.hpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2009.
// 

#ifndef __COMMON_DEFS_HPP_INCLUDED__
#define __COMMON_DEFS_HPP_INCLUDED__

#if __GNUC__ >= 3
#  define INLINE inline __attribute__ ((always_inline))
#  define FORCE_INLINE inline __attribute__ ((flatten))
#  define NO_INLINE     __attribute__ ((noinline))
#  define PURE		const __attribute__ ((pure))
#  define CONST  	const __attribute__ ((const))
#  define NO_RETURN	__attribute__ ((noreturn))
#  define __malloc	__attribute__ ((malloc))
#  define CHECK_RETVAL	__attribute__ ((warn_unused_result))
#  define DEPRECATED	__attribute__ ((deprecated)) 
#  define USED		__attribute__ ((used))
#  define UNUSED 	__attribute__ ((unused)) 
#  define PACKED 	__attribute__ ((packed))
#  define NON_NULL      __attribute__ ((nonnull))
#  define NO_RETURN     __attribute__ ((noreturn))
#  define NO_INSTRUMENT_FUNCTION __attribute__ ((no_instrument_function))
#  define SENTINEL      __attribute__ ((sentinel))
#  define WEAK          __attribute__ ((weak))
#  define WEAK_ALIAS(x) __attribute__ ((weak, alias(x)))
#  define LIKELY(x)	__builtin_expect (!!(x), 1)
#  define UNLIKELY(x)	__builtin_expect (!!(x), 0)
#  define CONSTRUCTOR   __attribute__ ((constructor))
#  define DESTRUCTOR    __atrribute__ ((destructor))
#else
#  if defined(_MS_VER)
#    define INLINE        __forceinline
#    define FORCE_INLINE  __forceinline
#  else
#    define INLINE	 inline
#    define FORCE_INLINE inline
#  endif
#  define NOINLINE      /* no inline */
#  define PURE		const /* no pure */
#  define CONST  	const /* no const */
#  define NO_RETURN	/* no noreturn */
#  define __malloc	/* no malloc */
#  define CHECK_RETVAL	/* no warn_unused_result */
#  define DEPRECATED	/* no deprecated */
#  define USED		/* no used */
#  define UNUSED 	/* no unused */
#  define PACKED 	/* no packed */
#  define NON_NULL
#  define NO_RETURN
#  define SENTINEL
#  define WEAK
#  define WEAK_ALIAS
#  define LIKELY(x)	(x)
#  define UNLIKELY(x)	(x)
#  define CONSTRUCTOR
#  define DESTRUCTOR
#endif

//! Additional GCC attributes
#ifdef __GNUC__
#  define ALIGN_N(x)        __attribute__ ((aligned(x)))
#  define ALIGN             __attribute__ ((aligned))
#  define VECTOR_SIZE(x)    __attribute__ ((vector_size(x)) 
#  define TRANSPARENT_UNION __attribute__ ((__transparent_union__)) 
#  define SECTION(x)        __attribute__ ((x)) 
#  define SHARED(x)         __attribute__ ((section (x), shared))
#  define NO_COMMON         __attribute__ ((nocommon))
#  define MODE(mode)        __attribute__ ((mode))
#else
#  define ALIGN_N(x)
#  define ALIGN
#  define VECTOR_SIZE(x)
#  define TRANSPARENT_UNION
#  define SECTION(x)
#  define SHARED(x)
#  define NO_COMMON
#  define MODE
#endif

//! GCC builtins.xs
/**
 * The following ISO C89 functions are recognized as built-in
 * functions unless `-fno-builtin' is specified: abs, cos, fabs,
 * fprintf, fputs, labs, memcmp, memcpy, memset, printf, sin, sqrt,
 * strcat, strchr, strcmp,strcpy, strcspn, strlen, strncat, strncmp,
 * strncpy, strpbrk, strrchr, strspn, and strstr. All of these
 * functions have corresponding versions prefixed with __builtin_.
 * 
 */
#ifdef __GNUC__
#  define INDEX            __builtin_index
#  define RINDEX           __builtin_rindex
#  define FFS              __builtin_ffs
#  define ALLOCA           __builtin_alloca
#  define BCMP             __builtin_bcmp
#  define BZERO            __builtin_bzero
#  define COSF             __builtin_cosf
#  define COSL             __builtin_cosl
#  define FASBSF           __builtin_fabsf
#  define FABSL            __builtin_fabsl
#  define SINF             __builtin_sinf
#  define SINL             __builtin_sinl
#  define IS_GREATER       __builtin_isgreater
#  define IS_GREATER_EQUAL __builtin_isgreaterequal
#  define IS_LESS          __builtin_isless
#  define IS_LESS_EQUAL    __builtin_islessequal
#  define IS_LESS_GREATER  __builtin_islessgreater
#  define IS_UNORDERED     __builtin_isunoredered
#  define CONSTANT_P(exp)  __builtin_constant_p(exp)
#else
#  define INDEX           
#  define RINDEX           
#  define FFS             
#  define ALLOCA           
#  define BCMP             
#  define BZERO            
#  define COSF             
#  define COSL             
#  define FASBSF           
#  define FABSL            
#  define SINF             
#  define SINL            
#  define IS_GREATER       
#  define IS_GREATER_EQUAL 
#  define IS_LESS          
#  define IS_LESS_EQUAL    
#  define IS_LESS_GREATER  
#  define IS_UNORDERED     
#  define CONSTANT_P(exp)  
#endif

//! GCC specific keywords
#ifdef __GNUC__
#  define TYPEOF(x)  __typeof__(x)
#  define ALIGNOF(x) __alignof__(x)
#  define WORD       __word__ 
#  define BYTE       __byte__ 
#  define POINTER    __pointer__ 
#else
#  define ALIGNOF(x)
#  define TYPEOF(x)
#  if defined(_MS_VER)
#    define BYTE
#  else
#    define WORD
#    define BYTE
#    define POINTER
#  endif
#endif

//! Make __restrict__ useable in C++.
/**
 * Because you cannot compile C++ by specifying the -std=c99 language
 * flag (restrict is not a keyword in C++).
 */
#ifdef __GNUC__
#  ifdef __cplusplus
#    define INIT_PRIORITY(priority) __attribute__ ((init_priority(priority)))
#    define RESTRICT __restrict__
#  else
#    define INIT_PRIORITY(priority) __attribute__ ((init_priority(priority)))
#    define RESTRICT restrict
#  endif
#else
#  define INIT_PRIORITY(p)
#  define RESTRICT 
#endif

//! GDB hack.
/**
 * An empty inline assembly statement you can rely on the side-effect
 * of splitting the basic block witout actually adding any
 * instructions.
 */
#define GCC_SPLIT_BLOCK __asm__ ("")

//! Gnu extension
#ifdef __GNUC__
#  define EXTENSION __extension__
#else
#  define EXTENSION
#endif

#endif // !__COMMON_DEFS_HPP_INCLUDED__

/* End of File */
