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
Block* block_split(BlockList* free_list, BlockList* used_list, Block* block, size_t request_size);
Block* first_fits(Simulation* sim, int request_size);
Block* random_fits(Simulation* sim, size_t request_size);
Block* worst_fits(Simulation* sim, size_t request_size);
Block* best_fits(Simulation* sim, size_t request_size);

#endif //PA2MINE_FITS_H
