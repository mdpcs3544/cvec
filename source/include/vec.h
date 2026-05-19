#if !defined(VEC_H)
#define VEC_H

#include <stddef.h>
#include "allocator.h"
#include "status.h"

struct vector;

enum libvec_status vector_init(struct vector *const self, const size_t esize, const size_t cap, const struct allocator *const allocator);
enum libvec_status vector_deinit(struct vector *const self);
enum libvec_status vector_push(struct vector *const self, const void *const elem);
enum libvec_status vector_pop(struct vector *const self, void *const elem);
enum libvec_status vector_get(const struct vector *const self, const size_t index, void *const elem);
enum libvec_status vector_set(struct vector *const self, const size_t index, const void *const elem);

#endif