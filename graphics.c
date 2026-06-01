#include <stdio.h>
#define SIZE 20

char canvas[SIZE][SIZE];

// Initialize canvas with '_'
void initCanvas() {
    for(int i=0; i<SIZE; i++)
        for(int j=0; j<SIZE; j++)
            canvas[i][j] = '_';
}

// Display canvas
void displayCanvas() {
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++)
            printf("%c ", canvas[i][j]);
        printf("\n");
    }
}

// Draw a rectangle
void drawRectangle(int x, int y, int w, int h) {
    for(int i=x; i<x+h; i++)
        for(int j=y; j<y+w; j++)
            canvas[i][j] = '*';
}
