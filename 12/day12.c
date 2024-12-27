#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024

const int dir[4][2] = {{1, 0},
                       {0, 1},
                       {-1, 0},
                       {0, -1}};

struct fencePoint {
    char type;
    int checked, x, y;
};

struct fencePoint grid[LINESIZE][LINESIZE];
int gridSize = 0, area = 0, perimeter = 0;

struct fencePoint CreateFencePoint(char _type, int _x, int _y) {
    struct fencePoint fp;
    fp.type = _type; fp.checked = 0;
    fp.x = _x; fp.y = _y;
    return fp;
}

void FindFenceSize(int _x, int _y) {
    grid[_y][_x].checked = 1; area++;
    int pointPerimeter = 0, nextX, nextY;
    struct fencePoint nextPoint;
    for(int i = 0; i < 4 ; i++) {
        nextX = grid[_y][_x].x+dir[i][0];
        nextY = grid[_y][_x].y+dir[i][1];
        // Checking if out of bounds
        if(nextX < 0 || nextX >= gridSize || nextY < 0 || nextY >= gridSize) { 
            pointPerimeter++; continue;
        }

        nextPoint = grid[nextY][nextX];
        // Checking the expected stuff
        if (nextPoint.type == grid[_y][_x].type && nextPoint.checked == 0) {
            FindFenceSize(nextPoint.x, nextPoint.y);
        } else if(nextPoint.type != grid[_y][_x].type) { pointPerimeter++; }
    }
    perimeter += pointPerimeter;
}

void PrintGrid() {
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            printf("%c", grid[i][j].type);
            // printf("%d", grid[i][j].checked);
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
                grid[gridSize][index] = CreateFencePoint(c, index, gridSize);
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
                FindFenceSize(j, i);
                total += area * perimeter;
                printf("%c: %d X %d\n", grid[i][j].type, area, perimeter);
                area = 0; perimeter = 0;
            }
            // break;
        }
        // break;
    }

    printf("total: %d\n", total);
    return 0;
}