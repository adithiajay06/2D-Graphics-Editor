#include <stdio.h>
#include "canvas.h"

char canvas[HEIGHT][WIDTH];

void init_canvas(void) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = '_';
        }
    }
}

void set_pixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

void display_canvas(void) {
    // Print tens digit for column header
    printf("     ");
    for (int x = 0; x < WIDTH; x++) {
        if (x % 10 == 0) {
            printf("%d", x / 10);
        } else {
            printf(" ");
        }
    }
    printf("\n");

    // Print units digit for column header
    printf("     ");
    for (int x = 0; x < WIDTH; x++) {
        printf("%d", x % 10);
    }
    printf("\n");

    // Print top border
    printf("   +");
    for (int x = 0; x < WIDTH; x++) {
        printf("-");
    }
    printf("+\n");

    // Print rows
    for (int y = 0; y < HEIGHT; y++) {
        printf("%2d |", y);
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", canvas[y][x]);
        }
        printf("|\n");
    }

    // Print bottom border
    printf("   +");
    for (int x = 0; x < WIDTH; x++) {
        printf("-");
    }
    printf("+\n");
}
