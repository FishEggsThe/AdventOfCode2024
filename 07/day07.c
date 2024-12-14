#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#define LINESIZE 1024

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

// int CheckNumber(int _checkTotal, int _nums[16], int _numsSize, int _i, int _expTotal) {
int CheckNumber(int _nums[16], int _numsSize, int _i, int _expTotal, int _checkTotal) {
    // Checking if at end
    if (_i >= _numsSize) {
        if (_checkTotal == _expTotal)
            return 1; 
        else
            return 0;
    }

    // Check addition then multipliction (Recursive), if either false then return false
    if (CheckNumber(_nums, _numsSize, _i+1, _expTotal, _checkTotal+_nums[_i]) == 1) { printf("add "); return 1; }
    if (CheckNumber(_nums, _numsSize, _i+1, _expTotal, _checkTotal*_nums[_i]) == 1) { printf("mul "); return 1; }
    return 0;
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    uint64_t total = 0, expectedTotal = 0;
    int numLength = 0, numbers[16];

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            // Get line data
            TrimLine(line);
            char* token = strtok(line, ":");
            expectedTotal = atoll(token); numLength = 0;
            
            token = strtok(NULL, " ");
            while(token != NULL) {
                numbers[numLength] = atoi(token);
                numLength++;
                token = strtok(NULL, " ");
            }

            printf("%llu:\t", expectedTotal);
            for(int i = 0; i < numLength; i++) {
                printf(" %d", numbers[i]);
            }
            printf("\n");
            
            // Do math
            int check = CheckNumber(numbers, numLength, 1, expectedTotal, numbers[0]);
            if (check == 1) { printf("possible :)"); total += expectedTotal; }
            else { printf("IMPOSSIBLE >:C"); }
            printf("\n");
        }
        fclose(file);
    }
    printf("\n");
    
    printf("total: %llu\n", total);
    return 0;
}