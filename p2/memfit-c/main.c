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
        if (strcmp("pool", cmd) == 0) {
            int amt = 0;
            if (2 != sscanf(buffer, "%s %s %d", cmd, name, &amt)) {
                fprintf(stderr, "Bad pool command: <\n\t%s\n>\n", buffer);
                return -4;
            }
            printf("pool(%s, %d)\n", name, amt);
            if (amt < 0) {
                fprintf(stderr, "pool: can only allocate positive memory!\n");
                return -5;
            }
            simulation_start(&sim, name, amt);
        } else if (strcmp("alloc", cmd) == 0) {
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
        } else if (strcmp("free", cmd) == 0) {
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

    return 0;
}
