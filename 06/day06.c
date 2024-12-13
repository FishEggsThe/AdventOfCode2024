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

void Pause() {
    char hold;
    scanf("%c\n", &hold);
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

void SetDirectionValues(int _direction[2], int _guardPos[3]) {
    double radianConversion = 3.141592653589793/180.0;
    double guardDir = ((double)_guardPos[2]) * radianConversion;
    _direction[0] = (int)cos(guardDir);
    _direction[1] = (int)sin(guardDir);
}

void CreateGrid(char _grid[SIZE][SIZE+1], int _guardPos[3]) {
    FILE *file;
    char line[LINESIZE];

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        int y = 0;
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            TrimLine(line);
            strcpy(_grid[y], line);
            // printf("%s", line);
            if (_guardPos[0] == -1) {
                for(int x = 0; x < strlen(line); x++) {
                    if (line[x] == '^') {
                        SetPosition(_guardPos, x, y, 90);
                        // printf(" <- Guard is here! (%d, %d)", x, y);
                        break;
                    }
                }
            }
            // printf("\n");
            y++;
        }
        fclose(file);
    }
    // printf("\n");
}

void ResetGrid(char _grid[SIZE][SIZE+1], int _guardPos[3]) {
    _guardPos[0] = -1;
    memset(_grid, 0, sizeof(_grid[0][0]) * SIZE * (SIZE+1));
    CreateGrid(_grid, _guardPos);
    // printf("grid reset!\n");
}

void DetermineGuardPath(char _grid[SIZE][SIZE+1], int _guardPos[3], int _lastPos[3], int *_total, int *_loopTotal) {
    // Setting values up
    int direction[2];
    SetDirectionValues(direction, _guardPos);

    int OOB = 0;
    char guardArrow = '^';
    while (OOB == 0) {
        while (_grid[_guardPos[1]-direction[1]][_guardPos[0]+direction[0]] == '#') {
            // Turning
            _guardPos[2] -= 90;
            if (_guardPos[2] < 0) { _guardPos[2]+= 360; }
            // printf("turn... (%d)\n", _guardPos[2]);

            // Conversion
            SetDirectionValues(direction, _guardPos);
            guardArrow = GuardFacing(_guardPos[2]);
        }

        // IncrementPosition(_grid, _guardPos, direction, _total);
        _grid[_guardPos[1]][_guardPos[0]] = 'X';
        SetPosition(_guardPos, _guardPos[0]+direction[0], _guardPos[1]-direction[1], _guardPos[2]);

        // Out of Bounds check
        for(int i = 0; i < 2; i++) {
            OOB += _guardPos[i] < 0 || _guardPos[i] >= SIZE;
        }
        if (OOB != 0) { 
            printf("Guard left\n"); 
            *_total += 1; break; 
        }

        // Loop Check
        if (PositionCompare(_guardPos, _lastPos) == 1) {
            printf("Loop Achieved!!!\n");
            *_loopTotal += 1; break;
        }
        // Check if should update last position
        if (_grid[_guardPos[1]][_guardPos[0]] == '.') {
            SetPositionArray(_lastPos, _guardPos);
            // *_total += 1;
        }
        _grid[_guardPos[1]][_guardPos[0]] = guardArrow;

        // printf("Position: %d, %d\n", _guardPos[0], _guardPos[1]);
        // printf("Last Position: %d, %d\n", _guardPos[0], _guardPos[1]);
        // printf("Last Position (Raw): %lf, %lf (%lf)\n", cos(guardDir), sin(guardDir), guardDir);
        // printf("Direction: %d, %d (%d)\n", direction[0], direction[1], _guardPos[2]);
        // PrintGrid(_grid);

        // Pause();
    }
    

    // PrintGrid(_grid);
}

int main() {
    // Variables
    char grid[SIZE][SIZE+1];
    int total = 0, loopTotal = 0, lastUpdatedPos[3], guardPos[3] = {-1, -1, -1};

    CreateGrid(grid, guardPos);
    // Pause();

    for(int y = 0; y < SIZE; y++) {
        for(int x = 0; x < SIZE; x++) {
            // Place barrier if possible, otherwise skip to next iteration
            if (grid[y][x] != '.') { continue; }
            grid[y][x] = '#';
            // PrintGrid(grid);
            // Pause();

            // Figure out path
            DetermineGuardPath(grid, guardPos, lastUpdatedPos, &total, &loopTotal);
            // Pause();

            // Reset Grid for next iteration
            ResetGrid(grid, guardPos);
            // Pause();
        }
    }
    
    // printf("total: %d\n", total);
    printf("loop total: %d\n", loopTotal);
    return 0;
}