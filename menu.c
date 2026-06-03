#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "canvas.h"
#include "shapes.h"

// Prompt user and read a safe integer within the specified range [min_val, max_val]
static int get_safe_int(const char *prompt, int min_val, int max_val) {
    int val;
    char buffer[100];
    while (1) {
        printf("%s (%d to %d): ", prompt, min_val, max_val);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) {
            continue;
        }
        if (sscanf(buffer, "%d", &val) != 1) {
            printf("Error: Invalid input. Please enter a valid integer.\n");
            continue;
        }
        if (val < min_val || val > max_val) {
            printf("Error: Value out of range. Please try again.\n");
            continue;
        }
        return val;
    }
}

static void handle_add_shape(void) {
    printf("\n--- Add Shape ---\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");
    printf("5. Back to Main Menu\n");
    
    int choice = get_safe_int("Select shape type", 1, 5);
    
    int x1, y1, x2, y2, x3, y3, cx, cy, radius;
    int id = -1;
    
    switch (choice) {
        case 1:
            printf("\nEnter Line Details:\n");
            x1 = get_safe_int("Start X", 0, WIDTH - 1);
            y1 = get_safe_int("Start Y", 0, HEIGHT - 1);
            x2 = get_safe_int("End X", 0, WIDTH - 1);
            y2 = get_safe_int("End Y", 0, HEIGHT - 1);
            id = add_line(x1, y1, x2, y2);
            break;
        case 2:
            printf("\nEnter Rectangle Details:\n");
            x1 = get_safe_int("Top-Left X", 0, WIDTH - 1);
            y1 = get_safe_int("Top-Left Y", 0, HEIGHT - 1);
            x2 = get_safe_int("Bottom-Right X", 0, WIDTH - 1);
            y2 = get_safe_int("Bottom-Right Y", 0, HEIGHT - 1);
            id = add_rectangle(x1, y1, x2, y2);
            break;
        case 3:
            printf("\nEnter Circle Details:\n");
            cx = get_safe_int("Center X", 0, WIDTH - 1);
            cy = get_safe_int("Center Y", 0, HEIGHT - 1);
            // Limit radius to canvas diagonal size for safety
            radius = get_safe_int("Radius", 0, WIDTH);
            id = add_circle(cx, cy, radius);
            break;
        case 4:
            printf("\nEnter Triangle Details:\n");
            x1 = get_safe_int("Point 1 X", 0, WIDTH - 1);
            y1 = get_safe_int("Point 1 Y", 0, HEIGHT - 1);
            x2 = get_safe_int("Point 2 X", 0, WIDTH - 1);
            y2 = get_safe_int("Point 2 Y", 0, HEIGHT - 1);
            x3 = get_safe_int("Point 3 X", 0, WIDTH - 1);
            y3 = get_safe_int("Point 3 Y", 0, HEIGHT - 1);
            id = add_triangle(x1, y1, x2, y2, x3, y3);
            break;
        case 5:
            return;
    }
    
    if (id != -1) {
        printf("Success: Added shape with ID %d.\n", id);
    } else {
        printf("Error: Failed to add shape (limit reached).\n");
    }
}

static void handle_delete_shape(void) {
    printf("\n--- Delete Shape ---\n");
    list_shapes();
    
    // Check if there are any active shapes
    bool any_active = false;
    for (int i = 0; i < MAX_SHAPES; i++) {
        if (shapes[i].active) {
            any_active = true;
            break;
        }
    }
    if (!any_active) {
        return;
    }
    
    int id = get_safe_int("Enter Shape ID to delete (0 to cancel)", 0, next_id - 1);
    if (id == 0) return;
    
    if (delete_shape(id)) {
        printf("Success: Shape %d deleted.\n", id);
    } else {
        printf("Error: Shape ID %d not found.\n", id);
    }
}

static void handle_modify_shape(void) {
    printf("\n--- Modify Shape ---\n");
    list_shapes();
    
    // Check if there are any active shapes
    bool any_active = false;
    for (int i = 0; i < MAX_SHAPES; i++) {
        if (shapes[i].active) {
            any_active = true;
            break;
        }
    }
    if (!any_active) {
        return;
    }
    
    int id = get_safe_int("Enter Shape ID to modify (0 to cancel)", 0, next_id - 1);
    if (id == 0) return;
    
    // Find shape type
    int idx = -1;
    for (int i = 0; i < MAX_SHAPES; i++) {
        if (shapes[i].active && shapes[i].id == id) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) {
        printf("Error: Shape ID %d not found.\n", id);
        return;
    }
    
    int x1, y1, x2, y2, x3, y3, cx, cy, radius;
    bool success = false;
    
    switch (shapes[idx].type) {
        case SHAPE_LINE:
            printf("\nEnter New Line Details:\n");
            x1 = get_safe_int("Start X", 0, WIDTH - 1);
            y1 = get_safe_int("Start Y", 0, HEIGHT - 1);
            x2 = get_safe_int("End X", 0, WIDTH - 1);
            y2 = get_safe_int("End Y", 0, HEIGHT - 1);
            success = modify_line(id, x1, y1, x2, y2);
            break;
        case SHAPE_RECTANGLE:
            printf("\nEnter New Rectangle Details:\n");
            x1 = get_safe_int("Top-Left X", 0, WIDTH - 1);
            y1 = get_safe_int("Top-Left Y", 0, HEIGHT - 1);
            x2 = get_safe_int("Bottom-Right X", 0, WIDTH - 1);
            y2 = get_safe_int("Bottom-Right Y", 0, HEIGHT - 1);
            success = modify_rectangle(id, x1, y1, x2, y2);
            break;
        case SHAPE_CIRCLE:
            printf("\nEnter New Circle Details:\n");
            cx = get_safe_int("Center X", 0, WIDTH - 1);
            cy = get_safe_int("Center Y", 0, HEIGHT - 1);
            radius = get_safe_int("Radius", 0, WIDTH);
            success = modify_circle(id, cx, cy, radius);
            break;
        case SHAPE_TRIANGLE:
            printf("\nEnter New Triangle Details:\n");
            x1 = get_safe_int("Point 1 X", 0, WIDTH - 1);
            y1 = get_safe_int("Point 1 Y", 0, HEIGHT - 1);
            x2 = get_safe_int("Point 2 X", 0, WIDTH - 1);
            y2 = get_safe_int("Point 2 Y", 0, HEIGHT - 1);
            x3 = get_safe_int("Point 3 X", 0, WIDTH - 1);
            y3 = get_safe_int("Point 3 Y", 0, HEIGHT - 1);
            success = modify_triangle(id, x1, y1, x2, y2, x3, y3);
            break;
    }
    
    if (success) {
        printf("Success: Shape %d modified.\n", id);
    } else {
        printf("Error: Failed to modify shape.\n");
    }
}

void run_menu(void) {
    init_canvas();
    
    while (1) {
        printf("\n====================================\n");
        printf("       2D GRAPHICS EDITOR           \n");
        printf("====================================\n");
        printf("1. Draw / View Canvas\n");
        printf("2. Add a Shape\n");
        printf("3. Modify a Shape\n");
        printf("4. Delete a Shape\n");
        printf("5. List All Active Shapes\n");
        printf("6. Exit\n");
        printf("====================================\n");
        
        int choice = get_safe_int("Enter selection", 1, 6);
        
        switch (choice) {
            case 1:
                draw_all_shapes();
                display_canvas();
                break;
            case 2:
                handle_add_shape();
                break;
            case 3:
                handle_modify_shape();
                break;
            case 4:
                handle_delete_shape();
                break;
            case 5:
                list_shapes();
                break;
            case 6:
                printf("\nExiting program. Goodbye!\n");
                return;
        }
    }
}
