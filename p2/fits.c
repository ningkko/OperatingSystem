#include "simulation.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "block.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>

/**
 * Splits a block in the free list with a given request size
 * returns the first new block as used block and he second one as free block.
 *
 * @param sim
 * @param block
 * @param name
 * @param request_size
 * @param index of the given block
 *
 * @return new used block
 */
Block* block_split(Simulation* sim, Block* block, char* name, size_t request_size, int index){

    BlockList* free_list = &sim->free_list;
    BlockList* used_list = &sim->used_list;

    // if block size == request size
    // 1. remove the block from free list and push it to the used list
    // 2. rename the block with the new name
    // 3. sort the free list
    if(block->size == request_size){

        list_remove(free_list, index);
        list_push(used_list, block);
        block_set_name(block, name);

        list_sort_by_offset(free_list);

        return block;
    }
    // else if block size > request size
    // 1. create 2 new blocks with request size and (block size - request size)
    // 2. set their offsets
    // 3. remove the old block from the free list, and push new blocks
    // 4. sort the free list and merge
    else if (block->size > request_size){

        /**
         * new used block with request size to be pushed
         */
        Block* newBlockForUsed = block_new(name, request_size);
        /**
         * new free block with left space to be pushed
         */
        Block* newBlockForFree = block_new(name, (block->size) - (request_size));
        // assign new offset
        newBlockForUsed->offset = block->offset;
        newBlockForFree->offset = block->offset+request_size;

        // push
        list_remove(free_list,index);
        list_push(used_list, newBlockForUsed);
        list_push(free_list, newBlockForFree);

        // sort and merge
        list_sort_by_offset(free_list);
        /**
         * position of the new free block
         */
        ssize_t new_position = list_find(&sim->free_list, name);
        simulation_merge_neighbors(sim,(size_t) new_position);

        return newBlockForUsed;
    }
    else{
        fprintf(stdout, "Cannot split. Request size is larger than the size of given block.");
        return NULL;
    }
}

/**
 * Find free space by always returning the first block in the free list that fits.
 *
 * @param sim
 * @param name
 * @param request_size
 */
void first_fits(Simulation* sim, char* name, int request_size){

    BlockList* free_list = &(sim->free_list);

    for (int i = 0; i < free_list->size; ++i) {

        // if find a block  in free list that fits
        if((int) (free_list->array[i]->size) >= request_size){

            // split it, and if succeed, return
            if (block_split(sim, free_list->array[i], name, (size_t) request_size, i)){
                return;
            };
        }
    }

    // else fail
    sim->failed_allocation_num+=1;
    printf("%s allocation failed. ", name);
}

/**
 * Find free block by returning a random block form the free list that fits
 * @param sim
 * @param name
 * @param request_size
 */
void random_fits(Simulation* sim,char* name, size_t request_size){

    BlockList* free_list = &(sim->free_list);

    /**
     *  A blocklist to store all blocks that fit the request size in free list
     */
    BlockList* all_fits;
    // initialize it
    list_init(all_fits);
    // push all usable blocks into it
    for(int i=0; i< free_list->size; i++){
        if(free_list->array[i]->size >= request_size) {
            list_push(all_fits, free_list->array[i]);
        }
    }

    // if none usable free block found, fail.
    if(all_fits->size<=0){
        sim->failed_allocation_num++;
        printf("%s allocation failed. ", name);
        return;
    }
    else{
        /**
         * random index in the list all_fits
         */
        int index_in_that_fit = rand()%all_fits->size;
        /**
         * the block we find in we're going to use
         */
        Block* found_in_all_fits = all_fits->array[index_in_that_fit];
        /**
         * the corresponding block of found_in_fits in free list
         */
        Block* found = list_get(free_list,(size_t) list_find(free_list,found_in_all_fits->name));
        /**
         * the index of Block found
         */
        int index = (int) list_find(free_list, found_in_all_fits->name);

        if(found != NULL) {
            if (block_split(sim, found, name, request_size, index)){
                return;
            };
        }else{
            sim->failed_allocation_num++;
            printf("%s allocation failed. ", name);
        }
    }
}


Block* worst_fits(Simulation* sim, char* name,size_t request_size){

    BlockList* free_list = &(sim->free_list);
    int curIndex = 0;
    size_t curSize = 0;
    for(int i=0; i < free_list->size; i++){
        Block* a = free_list->array[i];
        if((a->size >= request_size) && (a->size > curSize)){
            curIndex = i;
            curSize = a->size;
        }

    }
    Block* toReturn = free_list->array[curIndex];
    if(toReturn != NULL){
        return block_split(sim, toReturn, name, request_size, curIndex);
    }

    sim->failed_allocation_num+=1;
    fprintf(stderr, "All sizes of blocks inside the free_list are too small to fit in.");
    return NULL;
}



Block* best_fits(Simulation* sim, char* name,size_t request_size){

    BlockList* free_list = &(sim->free_list);

    int curIndex = 0;
    size_t curSize = 2147483647;
    for(int i=0; i < free_list->size; i++){
        Block* a = free_list->array[i];
        if((a->size >= request_size) && (a->size < curSize)){
            curIndex = i;
            curSize = a->size;
        }

    }
    Block* toReturn = free_list->array[curIndex];
    if(toReturn != NULL){
        return block_split(sim, toReturn, name, request_size, curIndex);
    }

    sim->failed_allocation_num+=1;
    fprintf(stderr, "All sizes of blocks inside the free_list are too small to fit in.");
    return NULL;
}

Block* next_fits(Simulation* sim, char* name, int request_size){
    BlockList* free_list = &(sim->free_list);
    size_t size = free_list->size;


    for(int i = 0; i < size; i++){
        int wrap = (i+sim->prevIndex)%(free_list->size);
        Block* b = free_list->array[wrap];
        if(b->size >= request_size){
            sim->prevIndex = wrap;
            return block_split(sim, b, name, request_size,wrap);
        }
    }
    sim->failed_allocation_num+=1;
    return NULL;
}