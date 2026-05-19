#include "list.h"

struct list_node {
    void *data;
    struct list_node *prev, *next;
};

struct list {
    size_t esize;
    size_t len;
    const struct allocator *allocator;
    struct list_node *head, *tail;
};

enum libvec_status list_init(struct list *const self, const size_t esize, const struct allocator *const allocator)
{
    if (!self || !allocator) {
        return LVSTAT_INVALID_ARGUMENT;
    }

    *self = (struct list) {
        .esize = esize,
        .len = 0,
        .allocator = allocator,
        .head = nullptr,
        .tail = nullptr
    };

    return LVSTAT_SUCCESS;
}
enum libvec_status list_deinit(struct list *const self)
{
    if (!self) {
        return LVSTAT_INVALID_ARGUMENT;
    }

    struct list_node *current = nullptr;
    struct list_node *next = self->head;
    while (next) {
        current = next;
        next = current->next;

        self->allocator->deallocate(current->data);
        self->allocator->deallocate(current);
    }

    return LVSTAT_SUCCESS;
}
enum libvec_status list_push(struct list *const self, const void *const elem);
enum libvec_status list_pop(struct list *const self, void *const elem);
enum libvec_status list_get(const struct list *const self, const size_t index, void *const elem);
enum libvec_status list_set(struct list *const self, const size_t index, const void *const elem);
enum libvec_status list_insert(struct list *const self, const size_t index, const void *const elem);
enum libvec_status list_remove(struct list *const self, const size_t index, void *const dest);