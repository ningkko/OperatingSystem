#include "simulation.h"
#include "fits.h"
#include <assert.h>
#include <stdio.h>

void simulation_init(Simulation *sim) {
    list_init(&sim->free_list);
    list_init(&sim->used_list);
    sim->pool_size = 0;
    sim->prevIndex = 0;
    sim->failed_allocation_num = 0;
}

void simulation_start(Simulation *sim, const char* strategy, size_t pool_size) {
    assert(sim->free_list.size == 0);
    assert(sim->used_list.size == 0);

    //create new starter block -> pool
    sim->pool_size = pool_size;
    Block* starterBlock = block_new("Pool", pool_size);
    // label its offset.
    starterBlock->offset=0;
    starterBlock->size=pool_size;
    list_push(&sim->free_list,starterBlock);

    if (strcmp("first", strategy) == 0) {
        sim->algorithm = 1;
    }
    else if (strcmp("random", strategy) == 0) {
        sim->algorithm = 2;
    }
    else if (strcmp("worst", strategy) == 0) {
        sim->algorithm = 3;
    }
    else if (strcmp("best", strategy) == 0) {
        sim->algorithm = 4;
    }
    else if (strcmp("next", strategy) == 0){
        sim->algorithm = 5;
    }
}

void simulation_alloc(Simulation *sim, const char* name, size_t amount) {
    assert(sim != NULL);

    if (sim->algorithm==1){
        first_fits( sim, name, amount);
    }

    else if (sim->algorithm==2){
        random_fits( sim, name, amount);
    }

    else if (sim->algorithm==3){
        worst_fits( sim, name, amount);
    }

    else if (sim->algorithm==4){
        best_fits( sim, name, amount);
    }

    else if (sim->algorithm==5){
        next_fits( sim, name, amount);
    }
    else {
        fprintf(stderr, "sim->algorithm set incorrectly!\n");
        exit(-2);
    }
}

void simulation_free(Simulation *sim, const char* name) {
    ssize_t position = list_find(&sim->used_list, name);
    if (position < 0) {
        fprintf(stderr, "Could not find previously-allocated: %s\n", name);
        return;
    }
    Block* found = list_remove(&sim->used_list, (size_t) position);
    assert(found != NULL);
    list_push(&sim->free_list, found);

    list_sort_by_offset(&sim->free_list);
    ssize_t new_position = list_find(&sim->free_list, name);
    simulation_merge_neighbors(sim,(size_t) new_position);
}

void simulation_merge_neighbors(Simulation *sim, size_t position) {

    BlockList* list = &sim->free_list;
    // if only one no need of merging
    if(list->size==1){
        return;
    }

    Block* current_block = list->array[position];


    //printf("Current bock,%s\nlist size:%i\nCurrent position: %i\n",current_block->name,(int) list->size,position);


    // check current and next
    if((int)position+1<list->size){
        Block* next_block = list->array[position+1];

        //printf("Next bock,%s\n",next_block->name);

        if (current_block->offset+current_block->size==next_block->offset){
            //printf("Next bock merged\n");

            current_block=simulation_merge(sim, current_block,next_block);
        }
    }

    // check current and previous
    if(((int)position)-1>=0){
        Block* previous_block = list->array[position-1];

        //printf("Previous bock,%s\n",previous_block->name);

        if (previous_block->offset+previous_block->size == current_block->offset){

            //printf("Previous bock merged\n");

            simulation_merge(sim, previous_block,current_block);
        }
    }
}

Block* simulation_merge(Simulation *sim, Block *first_block, Block *second_block){

    size_t size = first_block->size+second_block->size;
    Block* newBlock = block_new(first_block->name,size);
    newBlock->offset = first_block->offset;

    list_remove_given_block(&sim->free_list,first_block);
    list_remove_given_block(&sim->free_list,second_block);

    list_push(&sim->free_list,newBlock);
    return newBlock;
}


