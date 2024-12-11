#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define LINESIZE 1024
#define SIZE 130


void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

void PrintGrid(char _grid[SIZE][SIZE+1]) {
    for(int i = 0; i < SIZE; i++)
        printf("%s\n", _grid[i]);
}

char GuardFacing(int _dir) {
    char directions[5] = {'>', '^', '<', 'v'};
    int index = (_dir/90);
    return directions[index];
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

void IncrementPosition(char _grid[SIZE][SIZE+1], int _pos[3], int _dir[2], int *_total) {
    
}

void DetermineGuardStep(char _grid[SIZE][SIZE+1], int _guardPos[3], int _lastPos[3], int *_total) {
    // Setting values up
    double radianConversion = 3.141592653589793/180.0;
    double guardDir = (double)(_guardPos[2]) * radianConversion;
    int direction[2] = {(int)cos(guardDir), (int)sin(guardDir)};
    printf("%d, %d\n", direction[0], direction[1]);

    while (_grid[_guardPos[1]-direction[1]][_guardPos[0]+direction[0]] == '#') {
        // Turning
        _guardPos[2] -= 90;
        if (_guardPos[2] < 0) { _guardPos[2]+= 360; }
        printf("turn... (%d)\n", _guardPos[2]);

        // Conversion
        guardDir = (int)((double)(_guardPos[2]) * radianConversion);
        direction[0] = (int)cos(guardDir);
        direction[1] = (int)sin(guardDir);
    }


    // IncrementPosition(_grid, _guardPos, direction, _total);
    _grid[_guardPos[1]][_guardPos[0]] = 'X';
    SetPosition(_guardPos, _guardPos[0]+direction[0], _guardPos[1]-direction[1], _guardPos[2]);

    if (_grid[_guardPos[1]][_guardPos[0]] == '.') {
        *_total += 1;
    }
    _grid[_guardPos[1]][_guardPos[0]] = GuardFacing(_guardPos[2]);

    PrintGrid(_grid);
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE], grid[SIZE][SIZE+1];
    int total = 0, lastUpdatedPos[3], guardPos[3] = {-1, -1, -1};

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
                        printf(" <- Guard is here! (%d, %d)", x, y);
                        break;
                    }
                }
            }
            printf("\n");
            y++;
        }
        fclose(file);
    }
    printf("\n");

    // Figure out path
    do {
        // Desync check
        if (grid[guardPos[1]][guardPos[0]] != GuardFacing(guardPos[2])) 
        { printf("********** DESYNC!!! %c!=%c **********\n\n", grid[guardPos[1]][guardPos[0]], GuardFacing(guardPos[2])); break; }

        // The real deal
        DetermineGuardStep(grid, guardPos, lastUpdatedPos, &total);
        
        // Checking if guard leaves
        int OOB = 0;
        for(int i = 0; i < 2; i++) {
            OOB += guardPos[i] < 0 || guardPos[i] >= SIZE;
        }
        if (OOB > 0) { printf("Guard left\n"); break; }
    } while (PositionCompare(guardPos, lastUpdatedPos) == 0);
    
    printf("total: %d\n", total);
    return 0;
}