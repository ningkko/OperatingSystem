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
Block* find_first(int request_size, BlockList* free_list, BlockList* used_list);
Block* random_fits(size_t request_size, BlockList* free_list, BlockList* used_list);
Block* worst_fits(size_t request_size, BlockList* free_list, BlockList* used_list);
Block* best_fits(size_t request_size, BlockList* free_list, BlockList* used_list);

#endif //PA2MINE_FITS_H
