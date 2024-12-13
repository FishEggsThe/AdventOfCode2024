#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

// int CheckNumber() {
//     if (CheckNumber() == 1) { return 1; }
//     if (CheckNumber() == 1) { return 1; }
// }

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0, currTotal = 0, numLength = 0, numbers[16];

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            TrimLine(line);
            char* token = strtok(line, ":");
            currTotal = atoi(token); numLength = 0;
            
            token = strtok(NULL, " ");
            while(token != NULL) {
                numbers[numLength] = atoi(token);
                numLength++;
                token = strtok(NULL, " ");
            }

            printf("%d:", currTotal);
            for(int i = 0; i < numLength; i++) {
                printf(" %d", numbers[i]);
            }
            printf("\n");
            
        }
        fclose(file);
    }
    printf("\n");
    
    printf("total: %d\n", total);
    return 0;
}