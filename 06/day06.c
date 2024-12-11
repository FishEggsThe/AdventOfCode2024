#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define LINESIZE 1024
#define SIZE 10

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length] == '\n')
        _line[length-1] = 0;
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE], grid[SIZE][SIZE+1];
    int total = 0, lastUpdatedPos[3], guardPos[3];
    const double PI = 3.141592653589793;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            TrimLine(line);
            
        }
        fclose(file);
    }
    printf("\n");
    
    printf("total: %d\n", total);
    return 0;
}