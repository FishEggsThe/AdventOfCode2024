#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#define LINESIZE 300000

u_int64_t totals[LINESIZE];
int totalsSize = 25;

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

void PrintLine() {
    for(int i = 0; i < totalsSize; i++)
        printf("%llu ", totals[i]);
    printf("Total: %d\n\n", totalsSize);
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0;

    // Opening input file
    file = fopen("output.txt", "r");
    if (file) {
        int index;
        // Getting the next line
        fgets(line, LINESIZE, file);
        TrimLine(line);
        char *token = strtok(line, "  ");
        for(index = 0; token != NULL; index++) {
            totals[index] = atoi(token);
            token = strtok(NULL, "  ");
        }
        PrintLine();

        fclose(file);
    }
    printf("\n");
    
    // printf("total: %d\n", totalsSize);
    
    return 0;
}