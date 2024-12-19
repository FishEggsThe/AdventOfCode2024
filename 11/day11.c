#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#define LINESIZE 1024
#define ARRAYSIZE 7245000000

u_int64_t rockLine[ARRAYSIZE], firstHalf, secondHalf, multiplySN;
int rockLineSize, blinks = 75, allTotals[25];

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

void PrintLine() {
    // for(int i = 0; i < rockLineSize; i++)
        // printf("%llu ", rockLine[i]);
    printf("Total: %d\n", rockLineSize);
}

// FUCK YOU stackoverflow user 
void add_element(int insert, u_int64_t array[ARRAYSIZE], int index, int *array_length)
{
    int i;
    for(i = *array_length; i >= index; i--) {
        array[i+1] = array[i];
    }
    array[index] = insert;
    *array_length+=1;
}

void BlinkRocks() {
    // Go through rocks
    for(int i = 0; i < rockLineSize; i++) {
        // printf("%d (%d):\n", i, rockLine[i]);
        // If the rock is a zero
        if(rockLine[i] == 0) {
            // printf("0 -> 1\n");
            rockLine[i] = 1; continue;
        }

        // If the rock has an even number of digits
        u_int64_t num = rockLine[i];
        int digitNum = 0;
        while(num >= 1.0) {
            num /= 10;
            digitNum++;
        }
        if(digitNum % 2 == 0) {
            // printf("Even number of digits\n");
            multiplySN = 1;
            for(int i = 0; i < digitNum/2; i++)
                multiplySN *= 10;
            
            firstHalf = rockLine[i]/multiplySN;
            secondHalf = rockLine[i] - firstHalf*multiplySN;
            // printf("%llu - %llu (%llu)\n", firstHalf, secondHalf, multiplySN);

            rockLine[i] = (u_int64_t)firstHalf;
            i++;
            add_element(secondHalf, rockLine, i, &rockLineSize);
            
            // if (blinks == 3) { return; }
            continue;
        }

        // If either are false, just multiply by 2024
        // printf("Multiply by 2024\n");
        rockLine[i] *= 2024;
    }
    printf("\n");
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        int index;
        // Getting the next line
        fgets(line, LINESIZE, file);
        TrimLine(line);
        char *token = strtok(line, "  ");
        for(rockLineSize = 0; token != NULL; rockLineSize++) {
            rockLine[rockLineSize] = atoi(token);
            token = strtok(NULL, "  ");
        }
        PrintLine();

        // Start blinking
        for(int b = 1; b <= blinks; b++) {
            // printf("Blink #%d:\t", b);
            BlinkRocks();
            printf("\nBlink #%d ", b);
            PrintLine();
            allTotals[b-1] = rockLineSize;
        }

        fclose(file);
    }
    printf("\n");
    
    printf("total: %d\n", rockLineSize);
    
    return 0;
}