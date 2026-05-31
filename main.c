#include <stdio.h>
#include "graphics.h"

int main() {
    initCanvas();
    drawRectangle(2, 2, 5, 3);
    displayCanvas();
    return 0;
}

