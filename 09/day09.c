#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#define LINESIZE 20001

void PrintDiskMap(int _diskMap[LINESIZE][2], int _diskSize) {
    for (int i = 0; i < _diskSize; i++) {
        for (int j = 0; j < _diskMap[i][1]; j++) {
            if (_diskMap[i][0] == -1) {
                printf("."); continue;
            }
            printf("%d", _diskMap[i][0]);
        }
    }
    printf("\n");

    for (int i = 0; i < _diskSize; i++)
        printf("%d (%d)\n", _diskMap[i][0], _diskMap[i][1]);
    printf("Array Size: %d\n\n", _diskSize);
}

void FillDiskMap(int _diskMap[LINESIZE][2], int _num, int _size, int _i) {
    _diskMap[_i][0] = _num;
    _diskMap[_i][1] = _size;
}

// Thanks stackoverflow user 
void remove_element(int array[LINESIZE][2], int index, int *array_length)
{
    int i;
    for(i = index; i < *array_length - 1; i++) {
        array[i][0] = array[i + 1][0];
        array[i][1] = array[i + 1][1];
    }
    *array_length-=1;
}

// FUCK YOU stackoverflow user 
void add_element(int insert[2], int array[LINESIZE][2], int index, int *array_length)
{
    int num = insert[0], size = insert[1];
    int i;
    for(i = *array_length; i >= index; i--) {
        array[i+1][0] = array[i][0];
        array[i+1][1] = array[i][1];
    }
    array[index][0] = num;
    array[index][1] = size;
    *array_length+=1;
}

void JoinEmptySpace(int array[LINESIZE][2], int _i, int *array_length) {
    for (int k = _i; k < *array_length; k++) {
        if (array[k][0] <= -1) {
            // printf("%d\n", k);
            while (k+1 < *array_length && array[k+1][0] <= -1) {
                array[k][1] += array[k+1][1];
                remove_element(array, k+1, array_length);
            }
        }
    }
}

void GetTotal(int array[LINESIZE][2], int array_length, u_int64_t *_total) {
    int currNum = 0;
    for (int m = 0; m < array_length; m++) {
        for (int n = 0; n < array[m][1]; n++) {
            if (array[m][0] > -1)
                *_total += array[m][0] * currNum;
            currNum++;
        }
    }
}

void ArrangeDiskMap(int _diskMap[LINESIZE][2], int *_diskSize) {
    // Starting backwards
    for (int j = *_diskSize-1; j > 1; j--) {
        // If a row with numbers
        if (_diskMap[j][0] > -1) {
            printf(" * %d (%d)\n", _diskMap[j][0], _diskMap[j][1]);
            // Start to end
            for (int i = 1; i < j; i++) {
                // Checking if empty space has space for number(s)
                if (_diskMap[i][0] <= -1 && _diskMap[j][1] <= _diskMap[i][1]) {
                    add_element(_diskMap[j], _diskMap, i, _diskSize);
                    _diskMap[j+1][0] = -1;

                    _diskMap[i+1][1] -= _diskMap[i][1];
                    if (_diskMap[i+1][1] <= 0) {
                        remove_element(_diskMap, i+1, _diskSize);
                    }
                    // printf("found :3\n");

                    // Making sure the array isn't bloated
                    JoinEmptySpace(_diskMap, i, _diskSize);

                    // Check for if the do while should loop ONE more time
                    // return;
                    // PrintDiskMap(_diskMap, *_diskSize);
                    break;
                }
            }
        }
    }
    printf("\n");
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int diskMap[LINESIZE][2];
    u_int64_t total = 0;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        fgets(line, LINESIZE, file);
        printf("%s", line);
        printf("\n");
        fclose(file);
    }

    // Create Disk Map
    int currNum = 0, diskSize = 0;
    for(int i = 0; i < strlen(line); i++) {
        int size = line[i]-48;
        if (i % 2 == 0) { FillDiskMap(diskMap, currNum, size, diskSize); }
        else { FillDiskMap(diskMap, -1, size, diskSize); currNum++; }
        diskSize++;
    }
    printf("Disk created\n");

    // Fill Disk Map empty spaces and add to total at the same time >:3
    ArrangeDiskMap(diskMap, &diskSize);
    // PrintDiskMap(diskMap, diskSize);

    // GET THE TOTAL FINALLY
    GetTotal(diskMap, diskSize, &total);
    printf("total: %llu\n", total);
    return 0;
}