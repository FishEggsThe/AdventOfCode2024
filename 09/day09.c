#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#define LINESIZE 20001

void FillDiskMap(int _diskMap[LINESIZE][2], int _num, int _size, int _i) {
    _diskMap[_i][0] = _num;
    _diskMap[_i][1] = _size;
}

void ArrangeDiskMap(int _diskMap[LINESIZE][2], int _diskSize, u_int64_t *_total) {
    int j = _diskSize-1, currNum = 0;
    // Go through each number
    for(int i = 0; i < _diskSize; i++) {
        while(_diskMap[i][1] > 0) {
            int trueI = i, check = _diskMap[i][0] == -1;
            while (check) {
                if (_diskMap[j][0] != -1 && _diskMap[j][1] > 0) { trueI = j; break; }
                if (j <= i) { return; }
                j--;
            }

            *_total += currNum * _diskMap[trueI][0];
            _diskMap[trueI][1]--; currNum++;
            if (check) { _diskMap[i][1]--; }
            printf("%d: %d (%d)\n", currNum, _diskMap[trueI][0], _diskMap[trueI][1]);
        }
    }
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
    for (int i = 0; i < diskSize; i++)
        printf("%d (%d)\n", diskMap[i][0], diskMap[i][1]);
    printf("\n");


    // Fill Disk Map empty spaces and add to total at the same time >:3
    ArrangeDiskMap(diskMap, diskSize, &total);
    printf("\n");
    
    printf("total: %llu\n", total);
    return 0;
}