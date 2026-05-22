#include "list.h"

#if defined (__STDC_HOSTED__)
#include <string.h>
#include <stdlib.h>
#else
#include "freestanding.h"
#endif

struct list_node {
    void *data;
    struct list_node *prev, *next;
};

struct list {
    size_t esize;
    size_t len;
    struct list_node *head, *tail;
};

enum libvec_status list_init(struct list *const self, const size_t esize, const struct allocator *const allocator)
{
    if (!self || !allocator) {
        return LVSTAT_INVALID_ARGUMENT;
    }

    *self = (struct list){
        .esize = esize,
        .len = 0,
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

        free(current->data);
        free(current);
    }

    return LVSTAT_SUCCESS;
}

enum libvec_status list_push(struct list *const self, const void *const elem)
{
        if (!self || !elem) {
            return LVSTAT_INVALID_ARGUMENT;
        }
    
        struct list_node *new_node = malloc(sizeof(*new_node));
        if (!new_node) {
            return LVSTAT_ALLOCATION_FAILURE;
        }
    
        new_node->data = malloc(self->esize);
        if (!new_node->data) {
            free(new_node);
            return LVSTAT_ALLOCATION_FAILURE;
        }
    
        memcpy(new_node->data, elem, self->esize);
        new_node->prev = self->tail;
        new_node->next = nullptr;
    
        if (self->tail) {
            self->tail->next = new_node;
        } else {
            self->head = new_node;
        }
        self->tail = new_node;
        self->len++;
    
        return LVSTAT_SUCCESS;
}

enum libvec_status list_pop(struct list *const self, void *const elem)
{
    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (self->len == 0) {
        return LVSTAT_EMPTY;
    }

    struct list_node *tail = self->tail;
    memcpy(elem, tail->data, self->esize);

    if (tail->prev) {
        tail->prev->next = nullptr;
        self->tail = tail->prev;
    } else {
        self->head = nullptr;
        self->tail = nullptr;
    }

    free(tail->data);
    free(tail);
    self->len--;

    return LVSTAT_SUCCESS;
}

enum libvec_status list_get(const struct list *const self, const size_t index, void *const elem)
{
    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (index >= self->len) {
        return LVSTAT_INDEX_OUT_OF_BOUNDS;
    }

    struct list_node *current = self->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    memcpy(elem, current->data, self->esize);
    return LVSTAT_SUCCESS;
}

enum libvec_status list_set(struct list *const self, const size_t index, const void *const elem)
{
    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (index >= self->len) {
        return LVSTAT_INDEX_OUT_OF_BOUNDS;
    }

    struct list_node *current = self->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    memcpy(current->data, elem, self->esize);
    return LVSTAT_SUCCESS;
}

enum libvec_status list_insert(struct list *const self, const size_t index, const void *const elem)
{
    if (!self || !elem) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (index > self->len) {
        return LVSTAT_INDEX_OUT_OF_BOUNDS;
    }

    if (index == self->len) {
        return list_push(self, elem);
    }

    struct list_node *new_node = malloc(sizeof(*new_node));
    if (!new_node) {
        return LVSTAT_ALLOCATION_FAILURE;
    }

    new_node->data = malloc(self->esize);
    if (!new_node->data) {
        free(new_node);
        return LVSTAT_ALLOCATION_FAILURE;
    }

    memcpy(new_node->data, elem, self->esize);

    struct list_node *current = self->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    new_node->prev = current->prev;
    new_node->next = current;

    if (current->prev) {
        current->prev->next = new_node;
    } else {
        self->head = new_node;
    }
    current->prev = new_node;

    self->len++;
    return LVSTAT_SUCCESS;
}

enum libvec_status list_remove(struct list *const self, const size_t index, void *const dest)
{
    if (!self || !dest) {
        return LVSTAT_INVALID_ARGUMENT;
    }
    if (index >= self->len) {
        return LVSTAT_INDEX_OUT_OF_BOUNDS;
    }

    struct list_node *current = self->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    memcpy(dest, current->data, self->esize);

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        self->head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        self->tail = current->prev;
    }

    free(current->data);
    free(current);
    self->len--;

    return LVSTAT_SUCCESS;
}