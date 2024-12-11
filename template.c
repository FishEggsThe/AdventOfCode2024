#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length] == '\n')
        _line[length-1] = 0;
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 0;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            
        }
        fclose(file);
    }
    printf("\n");
    
    printf("total: %d\n", total);
    return 0;
}