#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    // Variables
    FILE *file;
    char line[1024];
    int numOfXMAS = 0;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, 1024, file)) {
        }
        fclose(file);
    }
    
    printf("All instances of XMAS: %d\n", numOfXMAS);
    return 0;
}