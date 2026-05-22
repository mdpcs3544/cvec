#if !defined(VEC_FREESTANDING_H) && !defined(__STDC_HOSTED__)
#define VEC_FREESTANDING_H

#include <stddef.h> // This is a freestanding standard C header

/* Users of this library must provide these functions on freestanding targets */
void memcpy(void *dest, const void *source, size_t nbytes);
void *malloc(const size_t size);
void free(void *buf);

#endif