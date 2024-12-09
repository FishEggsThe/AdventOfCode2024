#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int comp(const void* a, const void* b) {
      
      // If a is smaller, positive value will be returned
    return (*(int*)a - *(int*)b);
}

int main() {

    // For number shenanigans
    int c, SIZE = 0, totalDist = 0, totalSimilarityScore = 0;

    // For file stuff
    char line[15];
    FILE *file;
    file = fopen("input.txt", "r");
    
    // Get the number of lines in the file
    for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // Increment count if this character is newline
            SIZE++;
    SIZE++;
    fclose(file);
    printf("\nCount: %d\n", SIZE);

    // Convert lines to integers and put them in respective arrays
    file = fopen("input.txt", "r");
    int leftList[SIZE];
    int rightList[SIZE];
    if (file) {
        int index = 0;
        while (fgets(line, 1024, file)) {
            // String split and convert to int
            char* token = strtok(line, "   ");
            leftList[index] = atoi(token);
            token = strtok(NULL, "   ");
            rightList[index] = atoi(token);
            index++;
        }
        fclose(file);
    }

    // Sort lowest to greatest for leftList and rightList
    qsort(leftList, SIZE, sizeof(int), comp);
    qsort(rightList, SIZE, sizeof(int), comp);

    // Distance calculation
    for(int i = 0; i < SIZE; i++) {
        int dist = abs(leftList[i] - rightList[i]);
        totalDist += dist;

        // Print
        printf("%d\t(%d, %d)\n", dist, leftList[i], rightList[i]);
    }
    printf("\nTotal distance: %d\n", totalDist);

    // Similarity Score
    for(int i = 0; i < SIZE; i++) {
        int similarityScore = 0;
        for(int j = 0; j < SIZE; j++) {
            if (leftList[i] == rightList[j]) {
                similarityScore += leftList[i];

            }
        }
        totalSimilarityScore += similarityScore;
    }


    printf("Total Similarity Score: %d\n", totalSimilarityScore);

    return 0;
}