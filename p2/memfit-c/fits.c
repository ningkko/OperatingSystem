#include "simulation.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "block.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>

Block* block_split(Simulation* sim, Block* block, char* name, size_t request_size, int index){
    BlockList* free_list = &sim->free_list;
    BlockList* used_list = &sim->used_list;

    if(block->size < request_size){
        sim->failed_allocation_num++;
        fprintf(stderr, "Cannot split. Request size is larger than the size of given block.");
        return NULL;
    }
    else if(block->size == request_size){
        list_remove(free_list, index);
        list_push(used_list, block);
        block_set_name(block, name);
        list_sort_by_offset(free_list);
        return block;
    }
    else{
        Block* newBlockForUsed = block_new(name, request_size);
        Block* newBlockForFree = block_new(name, (block->size) - (request_size));
        // assign new offset
        newBlockForUsed->offset = block->offset;
        newBlockForFree->offset = block->offset+request_size;

        list_remove(free_list,index);
        list_push(used_list, newBlockForUsed);
        list_push(free_list, newBlockForFree);

        list_sort_by_offset(free_list);
        ssize_t new_position = list_find(&sim->free_list, name);
        simulation_merge_neighbors(sim,(size_t) new_position);
        return newBlockForUsed;
    }
}

Block* first_fits(Simulation* sim, char* name, int request_size){

    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    size_t size = free_list->size;
    int curIndex = 0;
    int counter = 0;

    while( counter < size){
        Block *a = free_list->array[curIndex];

        counter += 1;
        if((int)a->size >= request_size){
            return block_split(sim, a, name, request_size, curIndex);
        }
        else{
            curIndex += 1;
        }
    }
    sim->failed_allocation_num+=1;
    return NULL;
}

Block* random_fits(Simulation* sim,char* name, size_t request_size){
    BlockList* free_list = &(sim->free_list);
    int index = 0;
    srand(time(NULL));
    int indexes[free_list->size];
    int correct_size=0;
    for(int i=0; i< free_list->size; i++){
        Block* block = free_list->array[i];
        if(free_list->array[i]->size >= request_size){
            indexes[correct_size]=i;
            correct_size += 1;
        }

    }

    if(correct_size<=0){
        sim->failed_allocation_num++;
        return NULL;
    }

    index = rand()%correct_size;
    Block* found = free_list->array[index];
    if(found != NULL){
        return block_split(sim, found, name, request_size, index);
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
    BlockList* used_list = &(sim->used_list);

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