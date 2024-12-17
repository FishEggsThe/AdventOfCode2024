#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 64

char grid[LINESIZE][LINESIZE];
int gridSize = 0;

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

void PrintGrid() {
    for(int i = 0; i < gridSize; i++) {
        printf("%s\n", grid[i]);
    }
    printf("\n");
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            TrimLine(line);
            strcpy(grid[gridSize], line);
            gridSize++;
        }
        fclose(file);
    }
    PrintGrid();
    
    printf("total: %d\n", total);
    return 0;
}