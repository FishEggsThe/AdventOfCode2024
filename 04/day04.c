#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE 140

void checkLetterXMAS(char crossword[SIZE][SIZE+1], int i, int j, int *total) {
    // The 'X' check because that's what we're looking for
    if (crossword[i][j] != 'X') { return; }
    
    // For loops to check if 'XMAS' is in realistic range
    int range = 3, addTotal = 0;
    for (int k = -1; k <= 1; k+=1) {
        if (i+k*range < 0 || i+k*range > SIZE-1) { printf("invalid I (%d, %d)\n", i+k*range, 0); continue; }
        for (int l = -1; l <= 1; l+=1) {
            if (j+l*range < 0 || j+l*range > SIZE-1) { printf("invalid J (%d, %d)\n", i+k*range, j+l*range); continue; }

            // Alright time to check
            char xmas[4] = "XMAS"; // Don't worry we're skipping the first letter haha
            printf("%c", xmas[0]);
            for (int m = 1; m <= range; m++) {
                if (crossword[i+k*m][j+l*m] != xmas[m]) { break; }
                printf("%c", xmas[m]);
                if (m >= range) { printf(" Lets go"); addTotal++; }
            }
            printf("\n");
        }
    }

    *total += addTotal;
}

int main() {
    // Variables
    FILE *file;
    int numOfXMAS = 0;
    char line[1024], crossword[SIZE][SIZE+1];

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        int index = 0;
        // Getting the next line
        while (fgets(line, 1024, file)) {
            // Removing the new line because it bothers me
            int lineLength = strlen(line)-1;
            if (line[lineLength] == '\n') { line[lineLength] = 0; }

            strcpy(crossword[index], line);
            printf("%s\n", crossword[index]);
            index++;
        }
        fclose(file);
    }
    printf("\n");

    // Going through the crossword
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            checkLetterXMAS(crossword, i, j, &numOfXMAS);
        }
    }
    
    printf("All instances of XMAS: %d\n", numOfXMAS);
    return 0;
}