#if !defined(LIST_H)
#define LIST_H

#include "allocator.h"

struct list;

enum libvec_status list_init(struct list *const self, const size_t esize, const size_t cap, const struct allocator *const allocator);
enum libvec_status list_deinit(struct list *const self);
enum libvec_status list_push(struct list *const self, const void *const elem);
enum libvec_status list_pop(struct list *const self, void *const elem);
enum libvec_status list_get(const struct list *const self, const size_t index, void *const elem);
enum libvec_status list_set(struct list *const self, const size_t index, const void *const elem);
enum libvec_status list_insert(struct list *const self, const size_t index, const void *const elem);
enum libvec_status list_remove(struct list *const self, const size_t index, void *const dest);

#endif
