#include "block.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

// For qsort.
int by_size_increasing(const void* block_lhs, const void* block_rhs) {
    Block* lhs = *((Block**) block_lhs);
    Block* rhs = *((Block**) block_rhs);
    assert(lhs != NULL);
    assert(rhs != NULL);

    return (int) lhs->size - (int) rhs->size;
}

// For qsort.
int by_size_decreasing(const void* block_lhs, const void* block_rhs) {
    return by_size_increasing(block_rhs, block_lhs);
}

int by_offset_increasing(const void* block_lhs, const void* block_rhs){
    Block* lhs = *((Block**) block_lhs);
    Block* rhs = *((Block**) block_rhs);
    assert(lhs != NULL);
    assert(rhs != NULL);

    return (int) lhs->offset - (int) rhs->offset;
}

// for resizing.
static size_t max(size_t a, size_t b) {
    return (a > b) ? a : b;
}

void block_init(Block* b, const char* name, size_t size) {
    memset(b->name, 0, NAME_LEN+1);
    b->size = size;
    for (size_t i=0; i<NAME_LEN; i++) {
        if (name[i] != '\0') {
            b->name[i] = name[i];
        } else {
            break;
        }
    }
}

Block* block_new(const char* name, size_t size) {
    Block *b = (Block*) malloc(sizeof(Block));
    block_init(b, name, size);
    return b;
}


void list_init(BlockList* list) {
    list->array = NULL;
    list->capacity = 0;
    list->size = 0;
}

void list_free(BlockList* list) {
    if (list->array != NULL) {
        free(list->array);
        list->array = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

void list_grow(BlockList* list) {
    assert(list != NULL);
    Block** data = list->array;
    size_t new_capacity = max(4,list->capacity * 2);
    list->capacity = new_capacity;
    list->array = realloc(data, sizeof(Block*)*new_capacity);
}

void list_push(BlockList* list, Block *block) {
    assert(list != NULL);
    if (list->size >= list->capacity) {
        list_grow(list);
    }
    assert(list->size <= list->capacity);
    list->array[list->size++] = block;
}

ssize_t list_find(BlockList* list, const char* name) {
    for (size_t i=0; i<list->size; i++) {
        if (strcmp(list->array[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

Block* list_get(BlockList* list, size_t i) {
    assert(i <= list->size);
    return list->array[i];
}

Block* list_remove(BlockList* list, size_t i) {
    assert(i <= list->size);

    Block* retv = list->array[i];

    for (size_t j=i; j<list->size-1; j++) {
        list->array[j] = list->array[j+1];
    }
    list->array[--list->size] = NULL;
    return retv;
}

void list_sort(BlockList* list, bool increasing) {
    if (increasing) {
        qsort(&list->array[0], list->size, sizeof(void*), &by_size_increasing);
    } else {
        qsort(&list->array[0], list->size, sizeof(void*), &by_size_decreasing);
    }
}

BlockList* list_sort_by_offset(BlockList* list){
    BlockList list_copy = *list;
    qsort(list_copy.array[0],list_copy.size, sizeof(void*), &by_offset_increasing);
    return &list_copy;
}