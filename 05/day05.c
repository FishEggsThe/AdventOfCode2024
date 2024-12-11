#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SIZE 2000
#define LINESIZE 1024

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length] == '\n')
        _line[length-1] = 0;
}

void ScrutinizeUpdate(const int _rules[SIZE][2], int _rulesSize, int *_total) {
    for (int i = 0; i < _rulesSize; i++) {}
}

int main() {
    // Variables
    FILE *file;
    int total = 0, rulesSize = 0, rules[SIZE][2];
    char line[LINESIZE], divider = '|';

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        int index = 0;
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            if (line[0] == '\n') {
                printf("Switch! (| -> ,)\n");
                divider = ',';
            } else if (divider == '|') { // If the line is a rule (first half)
                TrimLine(line);
                char* token = strtok(line, " | ");
                rules[rulesSize][0] = atoi(token);
                token = strtok(NULL, " | ");
                rules[rulesSize][1] = atoi(token);

                printf("%d|%d\n", rules[rulesSize][0], rules[rulesSize][1]);
                rulesSize++;
            } else if (divider == ',') { // If the line is an update (second half)
                ScrutinizeUpdate(rules, rulesSize, &total);
            }
            
        }
        fclose(file);
    }
    printf("\n");
    
    printf("Sum of middle numbers: %d\n", total);
    return 0;
}