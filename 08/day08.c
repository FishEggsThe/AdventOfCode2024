#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024
#define GRIDSIZE 1024
#define MAXSIZE 64

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

void PrintGrid(char _grid[GRIDSIZE][GRIDSIZE+1], char _signalGrid[GRIDSIZE][GRIDSIZE+1], int _gridSize) {
    char nextChar;
    for(int i = 0; i < _gridSize; i++) {
        for(int j = 0; j < _gridSize; j++) {
            if (_grid[i][j] == '.')
                nextChar = _signalGrid[i][j];
            else
                nextChar = _grid[i][j];
            printf("%c", nextChar);
        }
        printf("\n");
    }
}

int FindLetter(char _letter, char _letters[MAXSIZE], int _lettersSize) {
    for(int i = 0; i < _lettersSize; i++) {
        if(_letters[i] == _letter)
            return 1;
    }
    return 0;
}

void ConfirmSignal(int _coords[MAXSIZE][2], int _i, int _j, char _signalGrid[GRIDSIZE][GRIDSIZE+1], int _gridSize, int *_total) {
    int increments[2], newPos[2];
    increments[0] = _coords[_i][0] - _coords[_j][0];
    increments[1] = _coords[_i][1] - _coords[_j][1];
    newPos[0] = _coords[_i][0];// + increments[0];
    newPos[1] = _coords[_i][1];// + increments[1];

    
    while (newPos[1] >= 0 && newPos[1] < _gridSize && 
        newPos[0] >= 0 && newPos[0] < _gridSize) {
        if (_signalGrid[newPos[1]][newPos[0]] != '#') {
            _signalGrid[newPos[1]][newPos[0]] = '#';
            printf("%d, %d (%d, %d)\n", newPos[1], newPos[0], _coords[_i][0], _coords[_i][1]);
            *_total += 1;
        }
        newPos[0] += increments[0];
        newPos[1] += increments[1];
    }
}

void SearchSignal(char _currChar, int _x, int _y, char _grid[GRIDSIZE][GRIDSIZE+1], int _gridSize, int *_total, char _signalGrid[GRIDSIZE][GRIDSIZE+1]) {
    // Gathering all coordinates for the current character
    printf("Function start\n");
    int coords[MAXSIZE][2], coordsSize = 0;
    for(int i = 0; i < _gridSize; i++) {
        for(int j = 0; j < _gridSize; j++) {
            // printf("%c", _grid[i][j]);

            if (_grid[i][j] == _currChar) {
                coords[coordsSize][0] = j;
                coords[coordsSize][1] = i;
                coordsSize++;
                printf("%d, %d\n", i, j);
            }
        }
    }
    printf("Coords coordinated (%d)\n", coordsSize);

    // Applying signal thing
    for(int i = 0; i < coordsSize-1; i++) {
        for(int j = i+1; j < coordsSize; j++) {
            ConfirmSignal(coords, i, j, _signalGrid, _gridSize, _total);
            ConfirmSignal(coords, j, i, _signalGrid, _gridSize, _total);
        }
    }
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE], grid[GRIDSIZE][GRIDSIZE+1], letters[MAXSIZE], signalGrid[GRIDSIZE][GRIDSIZE+1];
    int gridSize = 0, lettersSize = 0, total = 0;

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
    for(int i = 0; i < gridSize; i++) {
        strcpy(signalGrid[i], grid[i]);
        printf("%s\n", grid[i]);
    }
    printf("Grid Size: %d\n", gridSize);

    // Searching grid for signals
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            char currChar = grid[i][j];
            if (currChar != '.' && currChar != '#') {
                if (FindLetter(currChar, letters, lettersSize) == 0) {
                    printf("%c (%d, %d)\n", currChar, i, j);
                    letters[lettersSize] = currChar;
                    lettersSize++;
                    SearchSignal(currChar, j, i, grid, gridSize, &total, signalGrid);
                }
            }
        }
    }
    
    PrintGrid(grid, signalGrid, gridSize);
    printf("total: %d\n", total);
    return 0;
}