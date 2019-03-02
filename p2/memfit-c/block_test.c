#include "block.h"
#include <assert.h>
#include <stdio.h>

void test_simple(void) {
    BlockList test_list;
    list_init(&test_list);

    Block a;
    Block b;
    Block c;
    block_init(&a, "A", 30);
    block_init(&b, "B", 60);
    block_init(&c, "C", 90);

    // add "A"
    list_push(&test_list, &a);
    assert(test_list.size == 1);
    assert(0 == list_find(&test_list, "A"));
    assert(-1 == list_find(&test_list, "Z"));
    
    // add "B"
    list_push(&test_list, &b);
    assert(test_list.size == 2);
    assert(0 == list_find(&test_list, "A"));
    assert(1 == list_find(&test_list, "B"));
    assert(-1 == list_find(&test_list, "Z"));

    // add "C"
    list_push(&test_list, &c);
    assert(test_list.size == 3);
    assert(0 == list_find(&test_list, "A"));
    assert(1 == list_find(&test_list, "B"));
    assert(2 == list_find(&test_list, "C"));
    assert(30 == list_get(&test_list, 0)->size);
    assert(60 == list_get(&test_list, 1)->size);
    assert(90 == list_get(&test_list, 2)->size);
    assert(-1 == list_find(&test_list, "Z"));

    // "B", "C"
    Block* front = list_remove(&test_list, 0);
    assert(front->size == 30);
    assert(test_list.size == 2);
    assert(0 == list_find(&test_list, "B"));
    assert(1 == list_find(&test_list, "C"));

    // "B"
    Block* back = list_remove(&test_list, 1);
    assert(back->size == 90);
    assert(test_list.size == 1);
    assert(0 == list_find(&test_list, "B"));

    // Free the list:
    list_free(&test_list);
}

void test_sort(void) {
    BlockList test_list;
    list_init(&test_list);

    Block a;
    Block b;
    Block c;
    block_init(&a, "A", 30);
    block_init(&b, "B", 60);
    block_init(&c, "C", 90);
    list_push(&test_list, &a);
    list_push(&test_list, &b);
    list_push(&test_list, &c);
    assert(test_list.size == 3);

    assert(0 == list_find(&test_list, "A"));
    assert(1 == list_find(&test_list, "B"));
    assert(2 == list_find(&test_list, "C"));

    list_sort(&test_list, false);
    assert(test_list.size == 3);
    assert(0 == list_find(&test_list, "C"));
    assert(1 == list_find(&test_list, "B"));
    assert(2 == list_find(&test_list, "A"));

    list_sort(&test_list, true);
    assert(test_list.size == 3);
    assert(0 == list_find(&test_list, "A"));
    assert(1 == list_find(&test_list, "B"));
    assert(2 == list_find(&test_list, "C"));
    
    // Free the list:
    list_free(&test_list);
}

int main(int argc, char *argv[]) {
    test_simple();
    test_sort();
}