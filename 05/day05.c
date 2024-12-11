#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SIZE 2000
#define LINESIZE 1024
#define UPDATESIZE 100

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length] == '\n')
        _line[length-1] = 0;
}

int ScrutinizeUpdate(int _rules[SIZE][2], int _rulesSize, int _update[UPDATESIZE], int _updateSize, int *_total) {
    // Print update because I said so
    for (int i = 0; i < _updateSize; i++)
        printf("%d ", _update[i]);

    // Go through each number in the update
    for (int i = 0; i < _updateSize; i++) {
        int startNumber = _update[i]; // The left rule number

        // Go through all the rules that apply
        for (int j = 0; j < _rulesSize; j++) {
            if (_rules[j][0] != startNumber) { continue; }
            // else if (_rules[j][0] == startNumber)
            int endNumber = _rules[j][1]; // The right rule number

            // Go through update, if the rule is broken then return
            for (int k = 0; k < _updateSize; k++) {
                if (_update[k] == endNumber) {
                    // i: left number - k: right number
                    if (i > k) { 
                        printf("*** Rule Broken! (%d|%d)\n", _rules[j][0], _rules[j][1]);
                        int temp = _update[i];
                        _update[i] = _update[k];
                        _update[k] = temp;
                        return 0; 
                    }
                    break;
                }
            }
        }
    }

    printf("--- Good To Go (%d)\n", _update[_updateSize/2]);
    *_total += _update[_updateSize/2];
    return 1;
}

int main() {
    // Variables
    FILE *file;
    int total = 0, fixedTotal = 0, rulesSize = 0, rules[SIZE][2];
    char line[LINESIZE], divider = '|';

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        while (fgets(line, LINESIZE, file)) {
            char* token;
            if (line[0] == '\n') {
                printf("Switch! (| -> ,)\n");
                divider = ',';
            } else if (divider == '|') { // If the line is a rule (first half)
                TrimLine(line);
                token = strtok(line, " | ");
                rules[rulesSize][0] = atoi(token);
                token = strtok(NULL, " | ");
                rules[rulesSize][1] = atoi(token);

                printf("%d|%d\n", rules[rulesSize][0], rules[rulesSize][1]);
                rulesSize++;
            } else if (divider == ',') { // If the line is an update (second half)
                token = strtok(line, " , ");
                int update[UPDATESIZE], updateSize = 0;
                while(token != NULL) {
                    update[updateSize] = atoi(token);
                    token = strtok(NULL, " , ");
                    updateSize++;
                }
                int pass = ScrutinizeUpdate(rules, rulesSize, update, updateSize, &total);
                if (pass == 0) {
                    do {
                        pass = ScrutinizeUpdate(rules, rulesSize, update, updateSize, &fixedTotal);
                    } while (pass == 0);
                }
            }
            
        }
        fclose(file);
    }
    printf("\n");
    
    printf("Sum of middle numbers: %d\n", total);
    printf("Sum of fixed numbers: %d\n", fixedTotal);
    return 0;
}