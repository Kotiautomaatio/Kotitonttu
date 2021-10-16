#ifndef KOTITONTTU_MACROS_HPP
#define KOTITONTTU_MACROS_HPP

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#elif defined(__cplusplus)
# define UNUSED(x) x
#else
# define UNUSED(x) x
#endif


#endif // KOTITONTTU_MACROS_HPP
