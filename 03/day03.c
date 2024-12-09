#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void checkForMul(char line[], int length, int *i, int *total) {
    char mul[13];
    int j;

    // Copying line segment to mul for analysis
    if (line[*i] == 'm') {
        for(j = 0; j < 12; j++) {
            if (*i+j > length) {break;}
            mul[j] = line[*i+j];
            printf("%c", mul[j]);
        }
        printf("\n");
    } else { return; }
    if (strlen(mul) < 8) { return; }

    // Checking for closing parenthesis
    printf("Checking for closing parenthesis\n");
    for(j = 0; j < 5; j++) {
        // mul(1,1)**** -  8
        // mul(111,111) - 12
        if (mul[11-j] == ')') { break; }
        if (j >= 4) { return; }
    }

    // Checking for first half
    printf("Checking for first half\n");
    int mulLength = strlen(mul);
    char temp[] = "mul(";
    for(j = 0; j < strlen(temp); j++) {
        if (temp[j] != mul[j]) { return; }
    }

    // Retrieving the numbers possibly within
    printf("Retrieving the numbers possibly within\n");
    char numbers[8];
    int commas = 0, numLength = 0;
    while(mul[j] != ')') {
        // Check if valid char
        printf("%c %d%d - ", mul[j], mul[j] != ',', !(mul[j] >= '0' && mul[j] <= '9'));
        if (mul[j] != ',' && !(mul[j] >= '0' && mul[j] <= '9')) { return; }

        // Comma check
        if (mul[j] == ',' && numLength > 0) { commas++; numLength=0; }
        else if (mul[j] == ',' && numLength == 0) { printf("Stupid comma"); return; }
        // Number check
        if (mul[j] >= '0' && mul[j] <= '9') { numLength++; }
        // Excessive amount check
        if (commas > 1 || numLength > 3) { printf("Too long\n"); return; }
        // When all goes through
        numbers[j-4] = mul[j];
        j++;
    }
    if (commas != 1) { return; }
    numbers[j-4] = '\0';
    *i += j-1;
    printf("%s %li\n", numbers, strlen(numbers));

    // Get the product
    printf("Get the product\n");
    int addTotal = 0;
    char* token = strtok(numbers, " , ");
    addTotal += atoi(token);
    token = strtok(NULL, " , ");
    addTotal *= atoi(token);

    printf("%d\n", addTotal);
    *total += addTotal;
}

int main() {
    // Variables
    char line[4096];
    int mulTotal = 0;

    // Opening input file
    FILE *file;
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, 4096, file)) {
            // Go through line and checking for mul's
            int lineLength = strlen(line);
            for(int i = 0; i < lineLength; i++) {
                checkForMul(line, lineLength, &i, &mulTotal);
            }
        }
        fclose(file);
    }
    
    printf("Total of all multiplied numbers: %d\n", mulTotal);
    return 0;
}