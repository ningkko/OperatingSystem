#ifndef PA2MINE_FITS_H
#define PA2MINE_FITS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "block.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>

//fit methods
Block* block_split(Simulation* sim, Block* block, char* name, size_t request_size, int index);
Block* first_fits(Simulation* sim, char* name, int request_size);
Block* random_fits(Simulation* sim, char* name, size_t request_size);
Block* worst_fits(Simulation* sim, char* name, size_t request_size);
Block* best_fits(Simulation* sim, char* name, size_t request_size);
Block* next_fits(Simulation* sim, char* name, size_t request_size);

#endif //PA2MINE_FITS_H
