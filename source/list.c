#include "list.h"

struct list_node {
    void *data;
    struct list_node *prev, *next;
};

struct list {
    size_t esize;
    size_t len;
    struct allocator allocator;
    struct list_node *head, *tail;
};

enum libvec_status list_init(struct list *const self, const size_t esize, const size_t cap, const struct allocator *const allocator);
enum libvec_status list_deinit(struct list *const self);
enum libvec_status list_push(struct list *const self, const void *const elem);
enum libvec_status list_pop(struct list *const self, void *const elem);
enum libvec_status list_get(const struct list *const self, const size_t index, void *const elem);
enum libvec_status list_set(struct list *const self, const size_t index, const void *const elem);
enum libvec_status list_insert(struct list *const self, const size_t index, const void *const elem);
enum libvec_status list_remove(struct list *const self, const size_t index, void *const dest);