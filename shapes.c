#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "canvas.h"

Shape shapes[MAX_SHAPES];
int next_id = 1;

// Helper to find a shape index by ID
static int find_shape_index(int id) {
    for (int i = 0; i < MAX_SHAPES; i++) {
        if (shapes[i].active && shapes[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Helper to find an empty slot in the shapes array
static int find_empty_slot(void) {
    for (int i = 0; i < MAX_SHAPES; i++) {
        if (!shapes[i].active) {
            return i;
        }
    }
    return -1;
}

int add_line(int x1, int y1, int x2, int y2) {
    int idx = find_empty_slot();
    if (idx == -1) return -1;

    shapes[idx].id = next_id++;
    shapes[idx].type = SHAPE_LINE;
    shapes[idx].active = true;
    shapes[idx].data.line.x1 = x1;
    shapes[idx].data.line.y1 = y1;
    shapes[idx].data.line.x2 = x2;
    shapes[idx].data.line.y2 = y2;

    return shapes[idx].id;
}
// Added rectangle drawing function
int add_rectangle(int x1, int y1, int x2, int y2) {
    int idx = find_empty_slot();
    if (idx == -1) return -1;

    shapes[idx].id = next_id++;
    shapes[idx].type = SHAPE_RECTANGLE;
    shapes[idx].active = true;
    shapes[idx].data.rect.x1 = x1;
    shapes[idx].data.rect.y1 = y1;
    shapes[idx].data.rect.x2 = x2;
    shapes[idx].data.rect.y2 = y2;

    return shapes[idx].id;
}
// Implemented circle drawing using midpoint algorithm

int add_circle(int cx, int cy, int radius) {
    int idx = find_empty_slot();
    if (idx == -1) return -1;

    shapes[idx].id = next_id++;
    shapes[idx].type = SHAPE_CIRCLE;
    shapes[idx].active = true;
    shapes[idx].data.circle.cx = cx;
    shapes[idx].data.circle.cy = cy;
    shapes[idx].data.circle.radius = radius;

    return shapes[idx].id;
}
// Implemented triangle drawing function
int add_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    int idx = find_empty_slot();
    if (idx == -1) return -1;

    shapes[idx].id = next_id++;
    shapes[idx].type = SHAPE_TRIANGLE;
    shapes[idx].active = true;
    shapes[idx].data.triangle.x1 = x1;
    shapes[idx].data.triangle.y1 = y1;
    shapes[idx].data.triangle.x2 = x2;
    shapes[idx].data.triangle.y2 = y2;
    shapes[idx].data.triangle.x3 = x3;
    shapes[idx].data.triangle.y3 = y3;

    return shapes[idx].id;
}

bool delete_shape(int id) {
    int idx = find_shape_index(id);
    if (idx == -1) return false;

    shapes[idx].active = false;
    return true;
}

bool modify_line(int id, int x1, int y1, int x2, int y2) {
    int idx = find_shape_index(id);
    if (idx == -1 || shapes[idx].type != SHAPE_LINE) return false;

    shapes[idx].data.line.x1 = x1;
    shapes[idx].data.line.y1 = y1;
    shapes[idx].data.line.x2 = x2;
    shapes[idx].data.line.y2 = y2;
    return true;
}

bool modify_rectangle(int id, int x1, int y1, int x2, int y2) {
    int idx = find_shape_index(id);
    if (idx == -1 || shapes[idx].type != SHAPE_RECTANGLE) return false;

    shapes[idx].data.rect.x1 = x1;
    shapes[idx].data.rect.y1 = y1;
    shapes[idx].data.rect.x2 = x2;
    shapes[idx].data.rect.y2 = y2;
    return true;
}

bool modify_circle(int id, int cx, int cy, int radius) {
    int idx = find_shape_index(id);
    if (idx == -1 || shapes[idx].type != SHAPE_CIRCLE) return false;

    shapes[idx].data.circle.cx = cx;
    shapes[idx].data.circle.cy = cy;
    shapes[idx].data.circle.radius = radius;
    return true;
}

bool modify_triangle(int id, int x1, int y1, int x2, int y2, int x3, int y3) {
    int idx = find_shape_index(id);
    if (idx == -1 || shapes[idx].type != SHAPE_TRIANGLE) return false;

    shapes[idx].data.triangle.x1 = x1;
    shapes[idx].data.triangle.y1 = y1;
    shapes[idx].data.triangle.x2 = x2;
    shapes[idx].data.triangle.y2 = y2;
    shapes[idx].data.triangle.x3 = x3;
    shapes[idx].data.triangle.y3 = y3;
    return true;
}

void list_shapes(void) {
    bool found = false;
    printf("\n=== Active Shapes ===\n");
    for (int i = 0; i < MAX_SHAPES; i++) {
        if (shapes[i].active) {
            found = true;
            printf("ID: %d | ", shapes[i].id);
            switch (shapes[i].type) {
                case SHAPE_LINE:
                    printf("Line: (%d, %d) to (%d, %d)\n",
                           shapes[i].data.line.x1, shapes[i].data.line.y1,
                           shapes[i].data.line.x2, shapes[i].data.line.y2);
                    break;
                case SHAPE_RECTANGLE:
                    printf("Rectangle: Top-Left (%d, %d), Bottom-Right (%d, %d)\n",
                           shapes[i].data.rect.x1, shapes[i].data.rect.y1,
                           shapes[i].data.rect.x2, shapes[i].data.rect.y2);
                    break;
                case SHAPE_CIRCLE:
                    printf("Circle: Center (%d, %d), Radius %d\n",
                           shapes[i].data.circle.cx, shapes[i].data.circle.cy,
                           shapes[i].data.circle.radius);
                    break;
                case SHAPE_TRIANGLE:
                    printf("Triangle: P1(%d, %d), P2(%d, %d), P3(%d, %d)\n",
                           shapes[i].data.triangle.x1, shapes[i].data.triangle.y1,
                           shapes[i].data.triangle.x2, shapes[i].data.triangle.y2,
                           shapes[i].data.triangle.x3, shapes[i].data.triangle.y3);
                    break;
            }
        }
    }
    if (!found) {
        printf("No active shapes.\n");
    }
    printf("=====================\n\n");
}

void draw_all_shapes(void) {
    // Clear canvas first
    init_canvas();

    // Draw active shapes
    for (int i = 0; i < MAX_SHAPES; i++) {
        if (shapes[i].active) {
            switch (shapes[i].type) {
                case SHAPE_LINE:
                    draw_line_to_canvas(shapes[i].data.line.x1, shapes[i].data.line.y1,
                                        shapes[i].data.line.x2, shapes[i].data.line.y2);
                    break;
                case SHAPE_RECTANGLE:
                    draw_rectangle_to_canvas(shapes[i].data.rect.x1, shapes[i].data.rect.y1,
                                             shapes[i].data.rect.x2, shapes[i].data.rect.y2);
                    break;
                case SHAPE_CIRCLE:
                    draw_circle_to_canvas(shapes[i].data.circle.cx, shapes[i].data.circle.cy,
                                          shapes[i].data.circle.radius);
                    break;
                case SHAPE_TRIANGLE:
                    draw_triangle_to_canvas(shapes[i].data.triangle.x1, shapes[i].data.triangle.y1,
                                            shapes[i].data.triangle.x2, shapes[i].data.triangle.y2,
                                            shapes[i].data.triangle.x3, shapes[i].data.triangle.y3);
                    break;
            }
        }
    }
}

// Drawing stubs (to be implemented incrementally in later stages)
void draw_line_to_canvas(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        set_pixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_rectangle_to_canvas(int x1, int y1, int x2, int y2) {
    draw_line_to_canvas(x1, y1, x2, y1); // Top edge
    draw_line_to_canvas(x1, y2, x2, y2); // Bottom edge
    draw_line_to_canvas(x1, y1, x1, y2); // Left edge
    draw_line_to_canvas(x2, y1, x2, y2); // Right edge
}

void draw_circle_to_canvas(int cx, int cy, int radius) {
    if (radius < 0) return;

    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (y >= x) {
        set_pixel(cx + x, cy + y);
        set_pixel(cx - x, cy + y);
        set_pixel(cx + x, cy - y);
        set_pixel(cx - x, cy - y);
        set_pixel(cx + y, cy + x);
        set_pixel(cx - y, cy + x);
        set_pixel(cx + y, cy - x);
        set_pixel(cx - y, cy - x);

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void draw_triangle_to_canvas(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line_to_canvas(x1, y1, x2, y2);
    draw_line_to_canvas(x2, y2, x3, y3);
    draw_line_to_canvas(x3, y3, x1, y1);
}

 
 
 
 
/ /   A d d e d   r e c t a n g l e   d r a w i n g   f u n c t i o n  
 