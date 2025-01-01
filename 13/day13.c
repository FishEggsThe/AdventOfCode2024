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
int numOfClawMachines = 0;

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

void PressButton(struct clawMachine _claw, char _button) {
    int buttonPressed = _button == 'B';
    _claw.prizeCoords[0] += _claw.buttons[buttonPressed].xInc;
    _claw.prizeCoords[1] += _claw.buttons[buttonPressed].yInc;
}

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

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        int coords[3][2], index = 0;;
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
    
    printf("total: %d\n", total);
    return 0;
}