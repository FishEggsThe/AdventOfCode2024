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
int gridSize = 0, total = 0, startPointsSize = 0;
struct xyPos startPoints[LINESIZE];

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

int FindAllValidPaths(struct xyPos _pos, int *_total) {
    int currNum = grid[_pos.y][_pos.x] - 48;
    if (currNum >= 9) { *_total += 1; return 1; }

    int dir[4][2] = {{1, 0},
                     {0, 1},
                     {-1, 0},
                     {0, -1},};
    for(int m = 0; m < 4; m++) {
        struct xyPos nextPos = CreatePos(_pos.x+dir[m][0], _pos.y+dir[m][1]);
        int nextNum = grid[nextPos.y][nextPos.x] - 48;
        if(nextNum == currNum+1) { return FindAllValidPaths(nextPos, _total); }
    }
    return 0;
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];

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
                printf("%d, %d\n", startPoints[startPointsSize].x, startPoints[startPointsSize].y);
                startPointsSize++;
            }
        }
    }

    // Find all valid paths
    for(int i = 0; i < startPointsSize; i++) {
        FindAllValidPaths(startPoints[i], &total);
    }
    
    printf("total: %d\n", total);
    return 0;
}