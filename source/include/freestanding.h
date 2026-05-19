#if !defined(VEC_FREESTANDING_H) && !defined(__STDC_HOSTED__)
#define VEC_FREESTANDING_H

#include <stddef.h> // This is a freestanding standard C header

void memcpy(void *dest, const void *source, size_t nbytes);

#endif