#include "simulation.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "block.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>

// sim and free list, used list?
// next fit?
Block* block_split(BlockList* free_list, BlockList* used_list, Block* block, size_t request_size){
    if(block->size < request_size){
        fprintf(stderr, "Cannot split. Request size is larger than the size of given block.");
    }
    else if(block->size == request_size){
        list_remove(free_list, block);
        list_push(used_list, block);
        return block;
    }
    else{
        Block* newBlockForUsed = block_new(block->name, request_size);
        Block* newBlockForFree = block_new("", (block->size) - (request_size));
        // assign new offset
        newBlockForUsed->offset = block->offset;
        newBlockForFree->offset = block->offset+request_size;

        list_remove(free_list,block);
        list_push(used_list, newBlockForUsed);
        list_push(free_list, newBlockForFree);

        return newBlockForUsed;
    }
}

Block* first_fits(Simulation* sim, int request_size){

    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    size_t size = free_list->size;
    int curIndex = 0;
    Block* a = list_get(free_list, curIndex);

    while( a != NULL){
        if(a->size >= request_size){
            return block_split(free_list, used_list, a, request_size);
        }
        else{
            curIndex += 1;
            a = list_get(free_list, curIndex);
        }
    }
    sim->failed_allocation_num+=1;
    return NULL;
}

Block* random_fits(Simulation* sim,size_t request_size){

    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    srand(time(NULL));
    int index;
    size_t size = free_list->size;
    size_t curIndex = 0;
    Block* a = list_get(free_list, curIndex);
    index = rand()%size;

    while(a != NULL){
        if(a->size >= request_size){
            return block_split(free_list, used_list, a, request_size);
        }
        else{
            index = rand()%size;
            a = list_get(free_list, (size_t) index);
        }
    }

    sim->failed_allocation_num+=1;
    return NULL;
}


Block* worst_fits(Simulation* sim, size_t request_size){
    //TODO: is this the correct way to have a list of name ptr?

    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    char* avaliableIndexes[free_list->size];
    size_t sizes[free_list->size];
    size_t curIndex = 0;
    Block* a = list_get(free_list, curIndex);
    int arrayCounter = 0;
    size_t curLargest = 0;
    int curLargestIndex = 0;

    while(a != NULL){
        if(a->size >= request_size){
            avaliableIndexes[arrayCounter]= a->name;
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


    a = list_get(free_list, avaliableIndexes[curLargestIndex]);
    if(a!=NULL){
        return block_split(free_list, used_list, a, request_size);
    }

    sim->failed_allocation_num+=1;
    fprintf(stderr, "All sizes of blocks inside the free_list are too small to fit in.");
    return NULL;
}



Block* best_fits(Simulation* sim, size_t request_size){

    BlockList* free_list = &(sim->free_list);
    BlockList* used_list = &(sim->used_list);
    //TODO: is this the correct way to have a list of name ptr?
    char* avaliableIndexes[free_list->size];
    size_t sizes[free_list->size];
    size_t curIndex = 0;
    Block* a = list_get(free_list, curIndex);
    int arrayCounter = 0;
    size_t curBest = 0;
    int curBestIndex = 0;

    while(a != NULL){
        if(a->size >= request_size){
            avaliableIndexes[arrayCounter]= a->name;
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


    a = list_find(free_list, avaliableIndexes[curBestIndex]);
    if(a != NULL){
        return block_split(free_list, used_list, a, request_size);
    }

    sim->failed_allocation_num+=1;
    fprintf(stderr, "All sizes of blocks inside the free_list are too small to fit in.");
    return NULL;
}