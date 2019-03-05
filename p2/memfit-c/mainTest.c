#include "block.h"
#include "simulation.h"
#include "readFile.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define LINE_MAX_SIZE 128

void readFileToWords() {

    FILE *f;
    char line;

    f=fopen("test.txt","rt");

    while((line=fgetc(f))!=EOF){

        char *token = strtok(line, " ");
        while (token != NULL)
        {
            printf("%s\n", token);
            token = strtok(NULL, " ");
        }
        printf("---------");
    }


    fclose(f);
}


int main(){
    split();
    return 0;
}