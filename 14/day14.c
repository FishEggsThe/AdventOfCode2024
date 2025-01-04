#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINESIZE 1024
#define WIDTH 101
#define HEIGHT 103
#define SECONDS 100

// Structs and variables
struct vec2D {
    int x, y;
};
struct robot {
    struct vec2D pos, vel; // Position and Velocity
};
struct robot robots[1000];
int numOfRobots = 0, quadrantPopulations[2][2] = {{0, 0}, {0, 0}};

// Struct functions
void BuildRobot(int _values[2][2]) {
    struct robot robot;
    // Robot position
    robot.pos.x = _values[0][0];
    robot.pos.y = _values[0][1];
    // Robot velocity
    robot.vel.x = _values[1][0];
    robot.vel.y = _values[1][1];

    robots[numOfRobots] = robot;
    numOfRobots++;
}
void SimulateRobot(int _i) {
    struct robot robot = robots[_i];

    // Moving robot along x-axis
    robot.pos.x += (robot.vel.x * SECONDS);
    robot.pos.x %= WIDTH;
    if(robot.pos.x < 0) { robot.pos.x += WIDTH; }
    robots[_i].pos.x = robot.pos.x;

    // Moving robot along y-axis
    robot.pos.y += (robot.vel.y * SECONDS);
    robot.pos.y %= HEIGHT;
    if(robot.pos.y < 0) { robot.pos.y += HEIGHT; }
    robots[_i].pos.y = robot.pos.y;

    // Checking quadrant
    if(robot.pos.x == WIDTH/2 || robot.pos.y == HEIGHT/2) { return; }
    quadrantPopulations[robot.pos.y/(HEIGHT/2+1)][robot.pos.x/(WIDTH/2+1)]++;
}

void TrimLine(char _line[LINESIZE]) {
    int length = strlen(_line);
    if(_line[length-1] == '\n')
        _line[length-1] = 0;
}

void PrintGrid() {
    // Creating Grid
    char grid[1000][1000];
    int i, j;
    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            if(i == HEIGHT/2 || j == WIDTH/2)
                grid[i][j] = ' ';
            else
                grid[i][j] = '.';
        }
    }
    
    // Placing points where robots are
    for(i = 0; i < numOfRobots; i++) {
        if(!(robots[i].pos.y == HEIGHT/2 || robots[i].pos.x == WIDTH/2))
            grid[robots[i].pos.y][robots[i].pos.x] = 'X';
    }

    // Printing grid
    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// For reading the dumb stupid lines from the input.txt file so stupid
void GetNumbers(char _line[LINESIZE], int _coords[2][2]) {
                                // So many integers ik lol
    int offset = 2, i, j = 0, k = 0, l = 0, sign = 1;
    char currNum[64];
    // char* endPtr;
    // int base;

    for(i = offset; i < strlen(_line); i++) {
        // Scraping the number off the pan
        while((_line[i+j] >= '0' && _line[i+j] <= '9') || _line[i+j] == '-') {
            currNum[j] = _line[i+j];
            j++;
        }
        if(j > 0) {
            _coords[k][l] = atoi(currNum);
            sign = 1; memset(currNum, 0, sizeof(currNum));
            if(_line[i+j] == ',') { l++; }
            else { k++; l = 0; }
            i += j; j = 0;
        }
    }
}

int main() {
    // Variables
    FILE *file;
    char line[LINESIZE];
    int total = 1;

    // Opening input file
    file = fopen("input.txt", "r");
    if (file) {
        // Getting the next line
        int coords[2][2];
        while (fgets(line, LINESIZE, file)) {
            GetNumbers(line, coords);
            BuildRobot(coords);
        }
        fclose(file);
    }

    int i, j;
    // Simulating robot schmovement and final quadrant placement
    for(i = 0; i < numOfRobots; i++) {
        SimulateRobot(i);
    }
    // PrintGrid();

    // results
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            total *= quadrantPopulations[i][j];
        }
    }

    printf("total: %d\n", total);
    return 0;
}