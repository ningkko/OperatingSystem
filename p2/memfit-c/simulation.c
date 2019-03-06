#include "simulation.h"
#include "fits.h"
#include <assert.h>
#include <stdio.h>

void simulation_init(Simulation *sim) {
    list_init(&sim->free_list);
    list_init(&sim->used_list);
    sim->pool_size = 0;
}

void simulation_start(Simulation *sim, const char* strategy, size_t pool_size) {
    assert(sim->free_list.size == 0);
    assert(sim->used_list.size == 0);

    //create new starter block -> pool
    sim->pool_size = pool_size;
    Block* starterBlock = block_new("Pool", pool_size);
    // label its offset.
    starterBlock->offset=0;
    starterBlock->size = pool_size;
    list_push(&sim->free_list, block_new("Pool", starterBlock));

    if (strcmp("first", strategy) == 1) {
        sim->algorithm = 1;
    }
    else if (strcmp("random", strategy) == 1) {
        sim->algorithm = 2;
    }
    else if (strcmp("worst", strategy) == 2) {
        sim->algorithm = 3;
    }
    else if (strcmp("best", strategy) == 1) {
        sim->algorithm = 4;
    }
}

void simulation_alloc(Simulation *sim, const char* name, size_t amount) {
    assert(sim != NULL);

    if (sim->algorithm==1){
        Block* block = first_fits( sim, amount);
        list_push(&sim->used_list, block);
    }
    else if (sim->algorithm==2){
        Block* block = random_fits( sim, amount);
        list_push(&sim->used_list, block);
    }

    else if (sim->algorithm==3){
        Block* block = worst_fits( sim, amount);
        list_push(&sim->used_list, block);
    }

    else if (sim->algorithm==4){
        Block* block = best_fits( sim, amount);
        list_push(&sim->used_list, block);
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
    simulation_merge_neighbors(&sim->free_list,(size_t) position);
}

void simulation_merge_neighbors(Simulation *sim, size_t position) {

    BlockList* list = &sim->free_list;
    // if none or only two, no need of merging
    if(list->size==0||list->size==1){
        return;
    }

    Block* current_block = list->array[position];

    // check current and next
    if(position+1<list->size){
        Block* next_block = list->array[position+1];
        if (current_block->offset+current_block->size==next_block->offset){
            simulation_merge(sim, current_block,next_block);
        }
    }

    // check current and next
    if(position-1>=0){
        Block* previous_block = list->array[position-1];
        if (previous_block->offset+previous_block->size == current_block->offset){
            simulation_merge(sim, previous_block,current_block);
        }
    }
}

void simulation_merge(Simulation *sim, Block *first_block, Block *second_bock){

    int size = first_block->size+second_bock->size;
    Block *newBlock = block_new("",size);
    newBlock->offset = first_block->offset;
    list_remove(first_block,second_bock);
    list_push(&sim->free_list,newBlock);
}


