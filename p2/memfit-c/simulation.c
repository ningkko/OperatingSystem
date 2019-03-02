#include "simulation.h"
#include <assert.h>
#include <stdio.h>

void simulation_init(Simulation *sim) {
    list_init(&sim->free_list);
    list_init(&sim->used_list);
    sim->pool_size = 0;
}

void simulation_start(Simulation *sim, const char* strategy, size_t pool) {
    assert(sim->free_list.size == 0);
    assert(sim->used_list.size == 0);
    sim->pool_size = pool;
    list_push(&sim->free_list, block_new("Pool", pool));
}

void simulation_alloc(Simulation *sim, const char* name, size_t amount) {
    assert(sim != NULL);
    // for now, conjure blocks from thin-air;
    // TODO: do something more reasonable.
    list_push(&sim->used_list, block_new(name, amount));
}

void simulation_free(Simulation *sim, const char* name) {
    ssize_t position = list_find(&sim->used_list, name);
    if (position < 0) {
        fprintf(stderr, "Could not find previously-allocated: %s\n", name);
        exit(-2);
    }
    Block* found = list_remove(&sim->used_list, (size_t) position);
    assert(found != NULL);
    list_push(&sim->free_list, found);
}
