#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024
#define FENCESIZE LINESIZE*2+1

const int dir[4][2] = {{ 1,  0},
                       { 0,  1},
                       {-1,  0},
                       { 0, -1}};

struct fencePoint {
    char type;
    int checked, x, y;
};

struct fencePoint grid[LINESIZE][LINESIZE],
             fenceGrid[FENCESIZE][FENCESIZE];
int gridSize = 0, fenceGridSize = 0, area = 0, perimeter = 0;

struct fencePoint CreateFencePoint(char _type, int _x, int _y) {
    struct fencePoint fp;
    fp.type = _type; fp.checked = 0;
    fp.x = _x; fp.y = _y;
    return fp;
}

void PrintGrid() {
    for(int i = 0; i < gridSize; i++) {
        printf(" ");
        for(int j = 0; j < gridSize; j++) {
            printf("%c", grid[i][j].type);
        }
        printf("\n");
    }
    printf("\n");
}
void PrintFenceGrid() {
    for(int i = 0; i < fenceGridSize; i++) {
        // printf(" ");
        for(int j = 0; j < fenceGridSize; j++) {
            printf("%c", fenceGrid[i][j].type);
            // if(fenceGrid[i][j].type == '-' || fenceGrid[i][j].type == '|')
            //     printf("%d", fenceGrid[i][j].checked);
            // else
            //     printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

void ResetFenceGrid() {
    memset(fenceGrid, 0, sizeof(fenceGrid[0][0]) * FENCESIZE * FENCESIZE);
    int i, j;
    for(i = 0; i < fenceGridSize; i++) {
        for(j = 0; j < fenceGridSize; j++) {
            char spot = ' ';
            if(i % 2 == 1 && j % 2 == 1)
                spot = '#';
            fenceGrid[j][i] = CreateFencePoint(spot, j, i);
        }
    }
}

void AddToFenceGrid(int _x, int _y, int _dirI) {
    char fence = dir[_dirI][0] == 0 ? '-' : '|';
    int trueX = _x*2+1+dir[_dirI][0], 
        trueY = _y*2+1+dir[_dirI][1];

    fenceGrid[trueY][trueX] = CreateFencePoint(fence, trueX, trueY);
}

void FindFenceSize(int _x, int _y) {
    grid[_y][_x].checked = 1; area++;
    int pointPerimeter = 0, nextX, nextY;
    struct fencePoint nextPoint;
    for(int i = 0; i < 4 ; i++) {
        nextX = grid[_y][_x].x+dir[i][0];
        nextY = grid[_y][_x].y+dir[i][1];
        // printf("%d, %d\n", nextX, nextY);
        // Checking if out of bounds
        if(nextX < 0 || nextX >= gridSize || nextY < 0 || nextY >= gridSize) { 
            AddToFenceGrid(_x, _y, i);
            pointPerimeter++; continue;
        }

        nextPoint = grid[nextY][nextX];
        // Checking the expected stuff
        if (nextPoint.type == grid[_y][_x].type && nextPoint.checked == 0) {
            FindFenceSize(nextPoint.x, nextPoint.y);
        } else if(nextPoint.type != grid[_y][_x].type) {
            AddToFenceGrid(_x, _y, i);
            pointPerimeter++;
        }
    }
    // perimeter += pointPerimeter;
}

void FindFencePerimeter() {
    // Go through whole fence grid
    for(int i = 0; i < fenceGridSize; i++) {
        for(int j = i%2 == 0; j < fenceGridSize; j+=2) {
            // Check if fence point has already been checked
            if(fenceGrid[i][j].checked == 0 && fenceGrid[i][j].type != ' ') {
                char fence = fenceGrid[i][j].type;
                int direction[2] = {fence == '-', fence == '|'}, k = 0, inc[2];
                // Checking how long the fence is and checking each part of it then adding to perimeter
                do {
                    inc[0] = i+k*direction[1];
                    inc[1] = j+k*direction[0];
                    if(fenceGrid[inc[0]][inc[1]].type != fence) { break; }
                    // printf("%d, %d\t-> *", inc[0], inc[1]);
                    if(k > 0) {
                        if(fence == '-') {
                            // printf("%c %c*\n", fenceGrid[inc[0]-1][inc[1]-1].type, fenceGrid[inc[0]+1][inc[1]-1].type);
                            if(fenceGrid[inc[0]-1][inc[1]-1].type == '|' && fenceGrid[inc[0]+1][inc[1]-1].type == '|') { break; }
                        } if(fence == '|') {
                            // printf("%c %c*\n", fenceGrid[inc[0]-1][inc[1]-1].type, fenceGrid[inc[0]-1][inc[1]+1].type);
                            if(fenceGrid[inc[0]-1][inc[1]-1].type == '-' && fenceGrid[inc[0]-1][inc[1]+1].type == '-') { break; }
                        }
                    }

                    fenceGrid[inc[0]][inc[1]].checked = 1;
                    k+=2;
                } while(inc[0] < fenceGridSize && inc[1] < fenceGridSize);
                printf("\n");
                perimeter++;
            }
        }
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
        fenceGridSize = gridSize*2+1;

        fclose(file);
        PrintGrid();
    }
    // printf("\n");
    
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            if (grid[i][j].checked != 1) {
                ResetFenceGrid();
                FindFenceSize(j, i);
                // PrintFenceGrid();
                FindFencePerimeter();

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