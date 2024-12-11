#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define LINESIZE 1024
#define SIZE 10

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

char GuardFacing(int _dir) {
    char directions[5] = {'^', '<', 'v', '>'};
    return directions[_dir/90];
}

void SetPosition(int _pos[3], int _x, int _y, int _a) {
    _pos[0] = _x;
    _pos[1] = _y;
    _pos[2] = _a;
}

void SetPositionArray(int _pos[3], int _newPos[3]) {
    for(int i = 0; i < 3; i++) {
        _pos[i] = _newPos[i];
    }
}

int PositionCompare(int _posA[3], int _posB[3]) {
    for(int i = 0; i < 3; i++) {
        if(_posA[i] != _posB[i]) { return 0; }
    }
    return 1;
}

void DetermineGuardPath(char _grid[SIZE][SIZE+1], int _guardPos[3], int _lastPos[3], int *_total) {
    return;
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE], grid[SIZE][SIZE+1];
    int total = 1, lastUpdatedPos[3], guardPos[3] = {-1, -1, -1};
    const double PI = 3.141592653589793;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        int y = 0;
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            TrimLine(line);
            strcpy(grid[y], line);
            printf("%s", line);
            if (guardPos[0] == -1) {
                for(int x = 0; x < strlen(line); x++) {
                    if (line[x] == '^') {
                        SetPosition(guardPos, x, y, 90);
                        printf(" <- Guard is here!");
                        break;
                    }
                }
            }
            printf("\n");
        }
        fclose(file);
    }
    printf("\n");

    // Figure out path
    do {
        // Desync check
        if (grid[guardPos[1]][guardPos[0]] == GuardFacing(guardPos[2])) 
        {printf("********** DESYNC!!! **********\n\n"); break; }
        // The real deal
        DetermineGuardPath(grid, guardPos, lastUpdatedPos, &total);
    } while (PositionCompare(guardPos, lastUpdatedPos) == 0);
    
    printf("total: %d\n", total);
    return 0;
}