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
void first_fits(Simulation* sim, char* name, int request_size);
void random_fits(Simulation* sim, char* name, size_t request_size);
void worst_fits(Simulation* sim, char* name, size_t request_size);
void best_fits(Simulation* sim, char* name, size_t request_size);
void next_fits(Simulation* sim, char* name, size_t request_size);

#endif //PA2MINE_FITS_H
