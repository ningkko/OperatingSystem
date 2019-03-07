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
            printf("free capacity: %d\n",(int) sim.free_list.capacity);
            printf("used capacity: %d\n\n",(int) sim.used_list.capacity);

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
    printf("\nTotal allocation failed: %d\n",sim.failed_allocation_num);

    list_sort_by_offset(&(sim.free_list));
    list_sort_by_offset(&(sim.used_list));

    int totalUsedSize=0;
    int totalFreeSize=0;

    printf("\n"
           "========= Storage Report ========\n");

    printf("**Used list:\n");
    for (int i = 0; i < sim.used_list.size; ++i) {
        printf("Name: %s, offset: %i, size: %i\n",
                sim.used_list.array[i]->name,
               (int) sim.used_list.array[i]->offset,
               (int) sim.used_list.array[i]->size);
        totalUsedSize+=(int) sim.used_list.array[i]->size;
    }

    printf("**Free list:\n");
    for (int i = 0; i < sim.free_list.size; ++i) {
        printf("Name: %s, offset: %i, size: %i\n",
               sim.free_list.array[i]->name,
               (int) sim.free_list.array[i]->offset,
               (int) sim.free_list.array[i]->size);
        totalFreeSize+=(int) sim.free_list.array[i]->size;
    }

    int totalSize =totalUsedSize+totalFreeSize;

    printf("\n====== Memory usage report ======\n"
           "Total size:%i\nTotal used size: %i\nTotal free size: %i\n",
           totalSize,totalUsedSize,totalFreeSize);

    double used_percentage = (double) totalUsedSize/totalSize*100;
    double free_percentage = (double) totalFreeSize/totalSize*100;
    printf("Used memory percentage: %.2f%%.\nFree memory percentage: %.2f%%.\n", used_percentage, free_percentage);


    return 0;
}
