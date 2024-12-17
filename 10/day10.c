#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 64

struct xyPos {
  int x, y;
};

struct xyPos CreatePos(int _x, int _y) {
    struct xyPos pos;
    pos.x = _x;
    pos.y = _y;
    return pos;
}

char grid[LINESIZE][LINESIZE];
int gridSize = 0, startPointsSize = 0, endPointsSize = 0;
struct xyPos startPoints[LINESIZE*LINESIZE], endPoints[LINESIZE*LINESIZE];

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

void FindAllValidPaths(struct xyPos _pos, int *_total) {
    // Set up variables
    int currNum = grid[_pos.y][_pos.x] - 48,
        dir[4][2] = {{1, 0},
                     {0, 1},
                     {-1, 0},
                     {0, -1},};

    // Check for each direction
    for(int m = 0; m < 4; m++) {
        struct xyPos nextPos = CreatePos(_pos.x+dir[m][0], _pos.y+dir[m][1]);
        if (nextPos.y < 0 || nextPos.y >= gridSize || nextPos.x < 0 || nextPos.x >= gridSize) { continue; }
        int nextNum = grid[nextPos.y][nextPos.x] - 48;

        // If the next value (in that direction) is incremental from the last
        if(nextNum == currNum+1) {
            // If that next number is a 9
            if (nextNum >= 9) {
                // My face when star 2 feels like a star 1 solution 
                // Checking if it hasn't already been found
                // int check = 1;
                // for(int n = 0; n < endPointsSize; n++) {
                //     if (nextPos.x == endPoints[n].x && nextPos.y == endPoints[n].y) { check = 0; break; }
                // }
                // if (check) {
                //     endPoints[endPointsSize] = CreatePos(nextPos.x, nextPos.y);
                //     // printf("(%d, %d) -> (%d, %d)\n", _pos.x, _pos.y, endPoints[endPointsSize].x, endPoints[endPointsSize].y);
                //     endPointsSize++;
                //     *_total += 1;
                // }
                *_total += 1;
            }
            else { FindAllValidPaths(nextPos, _total); }
        }
    }
    // return 0;
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

    // Get starting points with struct :D!!!
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            if (grid[i][j] == '0') {
                startPoints[startPointsSize] = CreatePos(j, i);
                // printf("%d, %d\n", startPoints[startPointsSize].x, startPoints[startPointsSize].y);
                startPointsSize++;
            }
        }
    }
    printf("\n");

    // Find all valid paths
    for(int i = 0; i < startPointsSize; i++) {
        int lastTotal = total;
        // printf("Index: %d (%d, %d) \n", i, startPoints[i].x, startPoints[i].y);
        FindAllValidPaths(startPoints[i], &total);
        // printf("Total: %d\n", total-lastTotal);
        // for(int j = 0; j < endPointsSize; j++)
        //     printf("(%d, %d), ", endPoints[j].x, endPoints[j].y);
        // printf("\n\n");
        memset(endPoints, 0, sizeof(endPoints[0]) * LINESIZE * LINESIZE);
        endPointsSize = 0;
    }
    printf("\n");
    
    printf("total: %d\n", total);
    return 0;
}