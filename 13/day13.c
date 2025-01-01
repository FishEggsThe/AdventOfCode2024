#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024

struct button {
    int xInc, yInc;
};

struct clawMachine {
    struct button buttons[2];
    int prizeCoords[2];
};

struct clawMachine clawMachines[LINESIZE];
int lowestWinningTokenAmount,
numOfClawMachines = 0;

struct clawMachine CreateClawMachine(int _buttonA[2], int _buttonB[2], int _prizeCoords[2]) {
    struct clawMachine claw;

    // A Button
    claw.buttons[0].xInc = _buttonA[0];
    claw.buttons[0].yInc = _buttonA[1];

    // B Button
    claw.buttons[1].xInc = _buttonB[0];
    claw.buttons[1].yInc = _buttonB[1];

    // Prize Coordinates
    claw.prizeCoords[0] = _prizeCoords[0];
    claw.prizeCoords[1] = _prizeCoords[1];
    
    return claw;
}
// struct clawMachine functions
int GetButton(char _button, char _axis, struct clawMachine _claw) {
    int buttonPressed = _button - 'a';
    if(_axis == 'x')
        return _claw.buttons[buttonPressed].xInc;
    else if(_axis == 'y')
        return _claw.buttons[buttonPressed].yInc;
    return -1;
}
int CheckIfPrizeWon(struct clawMachine _claw, int _x, int _y) {
    return _x == _claw.prizeCoords[0]
        && _y == _claw.prizeCoords[1];
}
int CheckIfPrizeOvershot(struct clawMachine _claw, int _x, int _y) {
    return _x > _claw.prizeCoords[0]
        || _y > _claw.prizeCoords[1];
}

// For reading the dumb stupid lines from the input.txt file so stupid
void GetNumbers(int _i, char _line[LINESIZE], int _coords[3][2]) {
                                // So many integers ik lol
    int offset = _i == 2 ? 9 : 12, i, j, k = 0;
    char currNum[64];

    for(i = offset; i < strlen(_line); i++) {
        // Scraping the number off the pan
        j = 0;
        while(_line[i+j] >= '0' && _line[i+j] <= '9') {
            currNum[j] = _line[i+j]; j++;
        }
        if(j > 0) {
            _coords[_i][k] = atoi(currNum); k++;
            memset(currNum, 0, sizeof(currNum));
        }

        i += j;
    }
    
}
// Functions for how many wins you get at a claw machine
int CheckIfLowestTokens(int _tokens) {
    return _tokens < lowestWinningTokenAmount;
}
void SetWin(int _tokens) {
    lowestWinningTokenAmount = _tokens;
}
void ResetWin() {
    lowestWinningTokenAmount = 0;
}

// Fuck yeah math
void AttemptClawMachine(struct clawMachine _claw, int *_total) {
    const int matrix[2][2] = {{GetButton('a', 'x', _claw), GetButton('a', 'y', _claw)}, 
                              {GetButton('b', 'x', _claw), GetButton('b', 'y', _claw)}},
              sum[2] = {_claw.prizeCoords[0], _claw.prizeCoords[1]};
    int determinant, xDeterminant, yDeterminant, x, y;

    determinant = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    xDeterminant = sum[0]*matrix[1][1] - sum[1]*matrix[1][0];
    yDeterminant = matrix[0][0]*sum[1] - matrix[0][1]*sum[0];
    x = xDeterminant/determinant; y = yDeterminant/determinant;

    // printf("D: %d\nDx: %d\nDy: %d\n", determinant, xDeterminant, yDeterminant);
    // printf("x: %d\nyx: %d\n\n", x, y);

    if(matrix[0][0]*x + matrix[1][0]*y == sum[0] && matrix[0][1]*x + matrix[1][1]*y == sum[1])
        *_total += x*3 + y;
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        int coords[3][2], index = 0;
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            // Button A
            GetNumbers(0, line, coords);

            // Button B
            fgets(line, LINESIZE, file);
            GetNumbers(1, line, coords);

            // Prize Coordinates
            fgets(line, LINESIZE, file);
            GetNumbers(2, line, coords);

            // for reading shenanigans whatever
            fgets(line, LINESIZE, file);

            // Adding to claw machine array
            clawMachines[index] = CreateClawMachine(coords[0], coords[1], coords[2]);
            index++; numOfClawMachines++;
        }
        fclose(file);
    }
    printf("\n");

    for(int i = 0; i < numOfClawMachines; i++) {
        printf("Button A: X+%d, Y+%d\n", clawMachines[i].buttons[0].xInc, clawMachines[i].buttons[0].yInc);
        printf("Button B: X+%d, Y+%d\n", clawMachines[i].buttons[1].xInc, clawMachines[i].buttons[1].yInc);
        printf("Prize: X=%d, Y=%d\n", clawMachines[i].prizeCoords[0], clawMachines[i].prizeCoords[1]);
        printf("\n");
    }

    // int totalTokens;
    for(int i = 0; i < numOfClawMachines; i++) {
        // printf("All wins for Claw Machine %d: %d\n", i, lowestWinningTokenAmount);
        AttemptClawMachine(clawMachines[i], &total);
        ResetWin();
        // break;
    }
    
    printf("total: %d\n", total);
    return 0;
}