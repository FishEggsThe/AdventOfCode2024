#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#define LINESIZE 300000

int totals[25], diffTotals[24];
int totalsSize = 25;

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

void PrintLine(int _array[], int size) {
    for(int i = 0; i < size; i++)
        printf("%d ", _array[i]);
    // printf("Total: %d\n", size);
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0, index;

    // Opening input file
    file = fopen("output.txt", "r");
    if (file) {
        // Getting the next line
        fgets(line, LINESIZE, file);
        TrimLine(line);
        char *token = strtok(line, "  ");
        for(index = 0; token != NULL; index++) {
            totals[index] = atoi(token);
            token = strtok(NULL, "  ");
        }
        PrintLine(totals, totalsSize);

        fclose(file);
    }
    printf("\n");

    for(index = 0; index < 24; index++) {
        diffTotals[index] = totals[index+1] - totals[index];
    }
    PrintLine(diffTotals, 24);
    
    return 0;
}