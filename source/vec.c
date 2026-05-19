#include "vec.h"

#include <stddef.h>
#include <stdint.h>

#if defined (__STDC_HOSTED__)
#include <string.h>
#else
#include "freestanding.h"
#endif

struct vector {
    const struct allocator *allocator;
    size_t esize;
    uint8_t *ptr;
    size_t len;
    size_t cap;
};

enum libvec_status vector_init(struct vector *const self, const size_t esize, const size_t cap, const struct allocator *const allocator)
{
    uint8_t *buf = nullptr;

    if (!self || !allocator || !allocator->allocate || !allocator->deallocate) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (esize == 0 || cap == 0) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    buf = allocator->allocate(esize * cap);
    if (!buf) {
        return LVSTAT_OUT_OF_MEMORY;
    }

    *self =  (struct vector) {
        .allocator = allocator,
        .esize = esize,
        .ptr = buf,
        .len = 0,
        .cap = cap
    };

    return LVSTAT_SUCCESS;
}

enum libvec_status vector_deinit(struct vector *const self)
{
    if (!self) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    self->allocator->deallocate(self->ptr);
    self->ptr = nullptr;
    self->len = 0ull;
    self->cap = 0ull;

    return LVSTAT_SUCCESS;
}

enum libvec_status vector_push(struct vector *const self, const void *const elem)
{
    uint8_t *new_buf = nullptr;

    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (self->len == self->cap) {
        new_buf = self->allocator->allocate(self->esize * self->cap * 2);
        if (!new_buf) {
            return LVSTAT_OUT_OF_MEMORY;
        }
        memcpy(new_buf, self->ptr, self->len * self->esize);
        self->allocator->deallocate(self->ptr);
        self->ptr = new_buf;
        self->cap *= 2;
    }

    // Copy the element into the vector
    memcpy(&self->ptr[self->len * self->esize], elem, self->esize);
    self->len++;

    return LVSTAT_SUCCESS;
}

enum libvec_status vector_pop(struct vector *const self, void *const elem)
{
    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (self->len == 0) {
        return LVSTAT_EMPTY;
    }

    self->len--;
    memcpy(elem, &self->ptr[self->len * self->esize], self->esize);

    return LVSTAT_SUCCESS;
}

enum libvec_status vector_get(const struct vector *const self, const size_t index, void *const elem)
{
    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (index >= self->len) {
        return LVSTAT_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(elem, &self->ptr[index * self->esize], self->esize);

    return LVSTAT_SUCCESS;
}

enum libvec_status vector_set(struct vector *const self, const size_t index, const void *const elem)
{
    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (index >= self->len) {
        return LVSTAT_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(&self->ptr[index * self->esize], elem, self->esize);

    return LVSTAT_SUCCESS;
}