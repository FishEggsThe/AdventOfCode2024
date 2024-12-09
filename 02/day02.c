#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void printReport(int arr[], int size, int safe) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("(%d)\n\n", size);
}

// Thanks stackoverflow user 
void remove_element(int *array, int index, int array_length)
{
   int i;
   for(i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

int getSign(int a, int b) {
    int diff = a - b;
    if (diff == 0) { return 0; }
    return diff/abs(diff);
}

int checkIfSafe(int arr[], int size) {

    // Going through each number in the report
    for(int j = -1; j < size; j++){
        int currArr[1024], currSize = size;
        for(int k = 0; k < size; k++) {currArr[k] = arr[k];}
        if(j > -1) {remove_element(currArr, j, size); currSize--;}
        
        else {currSize--;}
        int sign = getSign(currArr[1], currArr[0]);

        for(int i = 1; i < currSize; i++){
            int diff = currArr[i] - currArr[i-1];
            int absDiff = abs(diff);

            // Many checks for numbers
            if(sign == 0 || diff/absDiff != sign){ // Checking if counting the correct direction
                break;
            } else if(absDiff < 1 || absDiff > 3) { // Checking difference
                break;
            }

            // If you get to the end with no problems
            if(i == currSize-1) {return 1;}
        }
    }

    return 0; // If you have gone through all possibilities and none are correct
}

int main() {
    // Variables
    char line[1024];
    int safeReports = 0;

    // Opening input file
    FILE *file;
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, 1024, file)) {
            int report[1024], count = 0;
            char* token = strtok(line, " ");

            // Fill temp array with report numbers
            while (token != NULL) {
                report[count] = atoi(token);
                token = strtok(NULL, " ");
                count++;
            }

            // Check if the report was safe
            if(checkIfSafe(report, count) == 1) {safeReports++;}
        }
        fclose(file);
    }
    
    printf("Safe reports: %d\n", safeReports);
    return 0;
}