#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024

struct fencePoint {
    char type;
    int checked, fences[4];
};

struct fencePoint CreateFencePoint(char _type) {
    struct fencePoint fp;
    fp.type = _type; fp.checked = 0;
    for (int i = 0; i < 4; i++)
        //right, up, left, down
        fp.fences[i] = 0;
    return fp;
}

void FindFenceSize(struct fencePoint *_fp, int *_area, int *_perimeter) {
    
}

struct fencePoint grid[LINESIZE][LINESIZE];
int gridSize = 0;

void PrintGrid() {
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            printf("%c", grid[i][j].type);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0, c;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        int index = 0;
        for (c = getc(file); c != EOF; c = getc(file)) {
            if (c == '\n') {
                gridSize++;
                index = 0;
            } else {
                grid[gridSize][index] = CreateFencePoint(c);
                index++;
            }
            
        }
        gridSize++;

        fclose(file);
        PrintGrid();
    }
    printf("\n");
    
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            if (grid[i][j].checked != 1) {
                
            }
        }
    }

    printf("total: %d\n", total);
    return 0;
}