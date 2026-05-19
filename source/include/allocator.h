#if !defined(ALLOCATOR_H)
#define ALLOCATOR_H

#include <stddef.h>

struct allocator {
    void *(*const allocate)(size_t size);
    void (*const deallocate)(void *ptr);
};

#endif
