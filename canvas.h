#ifndef CANVAS_H
#define CANVAS_H

#define WIDTH 60
#define HEIGHT 20

extern char canvas[HEIGHT][WIDTH];

// Initialize the canvas with '_' (underscore) characters
void init_canvas(void);

// Set a pixel to '*' at coordinate (x, y) if it falls within bounds
void set_pixel(int x, int y);

// Display the canvas on the console with coordinate headers
void display_canvas(void);

#endif // CANVAS_H
