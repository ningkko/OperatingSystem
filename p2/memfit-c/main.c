#include "block.h"
#include "simulation.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define LINE_MAX_SIZE 128

// Look at the next character from the file:
int fpeek(FILE *fp) {
    int what = fgetc(fp);
    ungetc(what, fp);
    return what;
}

void print_list_by_offset(Simulation *sim){

    printf("Free list sections sorted by offset: \n");
    BlockList* sorted_free_list = list_sort_by_offset(&(sim->free_list));
    for (int i = 0; i < sorted_free_list->size; ++i) {
        printf("No.%d: Offset: %d; Size: %d.\n",
                i, (int) sorted_free_list->array[i]->offset, (int) sorted_free_list->array[i]->size);
    }


    //TODO: Why no used list printed?
    printf("Used list sections sorted by offset: \n");
    BlockList* sorted_used_list = list_sort_by_offset(&(sim->used_list));
    for (int i = 0; i < sorted_used_list->size; ++i) {
        printf("%s: Offset: %d; Size: %d.\n",
                sorted_used_list->array[i]->name, (int) sorted_used_list->array[i]->offset, (int) sorted_used_list->array[i]->size);
    }

}

int main(int argc, char *argv[]) {
    // Print usage:
    if (argc != 2) {
        fprintf(stderr, "Usage: memfit input.txt\n");
        return -1;
    }

    // Read from stdin or a file:
    FILE* input;
    if (strcmp(argv[1], "-") == 0) {
        input = stdin;
    } else {
        input = fopen(argv[1], "r");
    }
    assert(input != NULL);

    Simulation sim;
    simulation_init(&sim);

    // Static buffers for the line, the command and the name of the memory block.
    char buffer[LINE_MAX_SIZE];
    char cmd[LINE_MAX_SIZE];
    char name[NAME_LEN];

    while(!feof(input)) {
        // Skip whitespace:
        if (fpeek(input) <= ' ') {
            fgetc(input);
            continue;
        }

        if (NULL == fgets(buffer, LINE_MAX_SIZE, input)) {
            fprintf(stderr, "Error reading from %s\n", argv[1]);
            return -2;
        }

        // Support line-based comments.
        if (buffer[0] == '#') {
            continue;
        }

        // Read the first word on the line as our command.
        if (1 != sscanf(buffer, "%s", cmd)) {
            fprintf(stderr, "Could not make sense of line: <\n\t%s\n>\n", buffer);
            return -3;
        }

        // Handle our 3 commands:
        //pool
        if (strcmp("pool", cmd) == 0) {
            int amt = 0;
            if (3 != sscanf(buffer, "%s %s %d", cmd, name, &amt)) {
                fprintf(stderr, "Bad pool command: <\n\t%s\n>\n", buffer);
                return -4;
            }
            printf("pool(%s, %d)\n", name, amt);
            if (amt < 0) {
                fprintf(stderr, "pool: can only allocate positive memory!\n");
                return -5;
            }
            simulation_start(&sim, name, amt);
        }
        // alloc
        else if (strcmp("alloc", cmd) == 0) {
            int amt = 0;
            if (3 != sscanf(buffer, "%s %s %d", cmd, name, &amt)) {
                fprintf(stderr, "Bad alloc command: <\n\t%s\n>\n", buffer);
                return -6;
            }
            printf("%s = alloc(%d)\n", name, amt);
            if (amt < 0) {
                fprintf(stderr, "alloc: can only allocate positive memory!\n");
                return -7;
            }

            simulation_alloc(&sim, name, amt);

        }
        // free
        else if (strcmp("free", cmd) == 0) {
            if (2 != sscanf(buffer, "%s %s", cmd, name)) {
                fprintf(stderr, "Bad free command: <\n\t%s\n>\n", buffer);
                return -8;
            }
            printf("free(%s)\n", name);

            simulation_free(&sim, name);

        } else {
            fprintf(stderr, "Unknown command: <\n\t%s\n>\n", buffer);
            return -9;
        }
    }

    fclose(input);

    //print failed allocation times
    printf("Total allocation failed: %d\n",sim.failed_allocation_num);

    // print memory used

    simulation_memory_usage_report(&sim);
    //print section list in offset order
   // print_list_by_offset(&sim);

    printf("\n\n===========================\n"
           "Test: What's in sim?\nFree list:\n");

    for (int i = 0; i < sim.free_list.size; ++i) {
        printf("Offset: %d, Size: %d\n",(int)sim.free_list.array[i]->offset,(int) sim.free_list.array[i]->size);
    }
    printf("Used list:\n");

    for (int i = 0; i < sim.used_list.size; ++i) {
        printf("%s\n",sim.used_list.array[i]->name);
    }

    return 0;
}
