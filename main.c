#include <stdio.h>
#include "graphics.h"

int main() {
    initCanvas();                // prepare blank canvas
    drawRectangle(2, 2, 5, 3);   // draw a rectangle
    displayCanvas();             // show canvas
    return 0;
}
