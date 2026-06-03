#ifndef SHAPES_H
#define SHAPES_H

#include <stdbool.h>

#define MAX_SHAPES 100

typedef enum {
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} ShapeType;

typedef struct {
    int x1, y1;
    int x2, y2;
} LineParams;

typedef struct {
    int x1, y1;
    int x2, y2;
} RectangleParams;

typedef struct {
    int cx, cy;
    int radius;
} CircleParams;

typedef struct {
    int x1, y1;
    int x2, y2;
    int x3, y3;
} TriangleParams;

typedef struct {
    int id;
    ShapeType type;
    bool active;
    union {
        LineParams line;
        RectangleParams rect;
        CircleParams circle;
        TriangleParams triangle;
    } data;
} Shape;

extern Shape shapes[MAX_SHAPES];
extern int next_id;

// Shape management functions
int add_line(int x1, int y1, int x2, int y2);
int add_rectangle(int x1, int y1, int x2, int y2);
int add_circle(int cx, int cy, int radius);
int add_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

bool delete_shape(int id);

bool modify_line(int id, int x1, int y1, int x2, int y2);
bool modify_rectangle(int id, int x1, int y1, int x2, int y2);
bool modify_circle(int id, int cx, int cy, int radius);
bool modify_triangle(int id, int x1, int y1, int x2, int y2, int x3, int y3);

// List active shapes to console
void list_shapes(void);

// Redraw all active shapes onto the canvas
void draw_all_shapes(void);

// Drawing algorithm declarations (to be implemented in following steps)
void draw_line_to_canvas(int x1, int y1, int x2, int y2);
void draw_rectangle_to_canvas(int x1, int y1, int x2, int y2);
void draw_circle_to_canvas(int cx, int cy, int radius);
void draw_triangle_to_canvas(int x1, int y1, int x2, int y2, int x3, int y3);

#endif // SHAPES_H
