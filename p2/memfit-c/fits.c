#include "simulation.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "block.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>

Block* block_split(BlockList* free_list, BlockList* used_list, Block* block, char* name, size_t request_size, int index){
    if(block->size < request_size){
        fprintf(stderr, "Cannot split. Request size is larger than the size of given block.");
    }
    else if(block->size == request_size){
        list_remove(free_list, index);
        list_push(used_list, block);
        block_set_name(block, name);
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
        Block *a = list_get(free_list, curIndex);

        counter += 1;
        if(a->size >= request_size){
            return block_split(free_list, used_list, a, name, request_size, curIndex);
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
    BlockList* used_list = &(sim->used_list);
    srand(time(NULL));
    int index;
    size_t size = free_list->size;
    size_t curIndex = 0;
    Block* a = list_get(free_list, curIndex);
    index = rand()%size;
    int counter = 0;

    while(counter < size){
        counter += 1;
        if(a->size >= request_size){
            return block_split(free_list, used_list, a, name, request_size,index);
        }
        else{
            index = rand()%size;
            a = list_get(free_list, (size_t) index);
        }
    }

    sim->failed_allocation_num+=1;
    return NULL;
}


Block* worst_fits(Simulation* sim, char* name,size_t request_size){
    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    int availableIndexes[free_list->size];
    size_t sizes[free_list->size];
    size_t curIndex = 0;
    Block* a = list_get(free_list, curIndex);
    int arrayCounter = 0;
    size_t curLargest = 0;
    int curLargestIndex = 0;
    int counter = 0;

    while(counter < free_list->size){
        counter += 1;
        if(a->size >= request_size){
            availableIndexes[arrayCounter]= counter;
            sizes[arrayCounter]=a->size;
            arrayCounter += 1;
            curIndex += 1;
            a = list_get(free_list, curIndex);
        }
        else{
            curIndex += 1;
            a = list_get(free_list, curIndex);
        }
    }

    for(int i=0; i<(arrayCounter+1);i++){
        if(curLargest < sizes[i]){
            curLargest = sizes[i];
            curLargestIndex = i;
        }
    }


    a = list_get(free_list, availableIndexes[curLargestIndex]);
    if(a!=NULL){
        return block_split(free_list, used_list, a, name, request_size,availableIndexes[curLargestIndex]);
    }

    sim->failed_allocation_num+=1;
    fprintf(stderr, "All sizes of blocks inside the free_list are too small to fit in.");
    return NULL;
}



Block* best_fits(Simulation* sim, char* name,size_t request_size){

    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    int availableIndexes[free_list->size];
    size_t sizes[free_list->size];
    size_t curIndex = 0;
    Block* a = list_get(free_list, curIndex);
    int arrayCounter = 0;
    size_t curBest = 0;
    int curBestIndex = 0;
    int counter = 0;

    while(counter < free_list->size){
        counter += 1;
        if(a->size >= request_size){
            availableIndexes[arrayCounter]= counter;
            sizes[arrayCounter]=a->size;
            arrayCounter += 1;
            curIndex += 1;
            a = list_get(free_list, curIndex);
        }
        else{
            curIndex += 1;
            a = list_get(free_list, curIndex);
        }
    }

    for(int i=0; i<(arrayCounter+1);i++){
        if(curBest > sizes[i]){
            curBest = sizes[i];
            curBestIndex = i;
        }
    }


    a = list_get(free_list, availableIndexes[curBestIndex]);
    if(a != NULL){
        sim->prevIndex = availableIndexes[curBestIndex];
        return block_split(free_list, used_list, a, name, request_size, sim->prevIndex);
    }

    sim->failed_allocation_num+=1;
    fprintf(stderr, "All sizes of blocks inside the free_list are too small to fit in.");
    return NULL;
}

Block* next_fits(Simulation* sim, char* name, int request_size){
    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    size_t size = free_list->size;


    for(int i = 0; i < size; i++){
        int wrap = (i+sim->prevIndex)%(free_list->size);
        Block* b = list_get(free_list, wrap);
        if(b->size >= request_size){
            sim->prevIndex = wrap;
            return block_split(free_list, used_list, b, name, request_size,wrap);
        }
    }
    sim->failed_allocation_num+=1;
    return NULL;
}