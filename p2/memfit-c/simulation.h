#ifndef __SIMULATION_H
#define __SIMULATION_H 1

#include <stdlib.h>
#include "block.h"

typedef struct {
    size_t pool_size;
    BlockList free_list;
    BlockList used_list;
} Simulation;

void simulation_init(Simulation *sim);
void simulation_start(Simulation *sim, const char* strategy, size_t pool);
void simulation_alloc(Simulation *sim, const char* name, size_t amount);
void simulation_free(Simulation *sim, const char* name);

#endif // __SIMULATION_H