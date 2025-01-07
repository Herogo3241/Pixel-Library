#include <pixel.h>
#include <stdio.h>
#include <math.h>

typedef struct Node {
    Vec2 data;
    struct Node* next;
} Stack;

Color red = {255, 0, 0};
Color black = {0, 0, 0}; // Assuming background color is black

Stack* createNode(Vec2 data) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    if (!newNode) {
        perror("Allocation Error");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;  // Added missing return statement
}

void push(Stack** top, Vec2 item) {
    Stack* newNode = createNode(item);
    newNode->next = *top;
    *top = newNode;
}

Vec2 pop(Stack** top) {  // Fixed parameter type and return type
    if (*top == NULL) {
        perror("Stack Underflow");
        Vec2 error = {-1, -1};  // Return error value
        return error;
    }
    Stack* temp = *top;
    Vec2 item = temp->data;
    *top = temp->next;
    free(temp);
    return item;
}


// Display stack contents
void displayStack(Stack* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    Stack* temp = top;
    printf("Stack contents: ");
    while (temp != NULL) {
        printf("{%d, %d} ", temp->data.x, temp->data.y);
        temp = temp->next;
    }
    printf("\n");
}



// Check if a pixel is within canvas bounds
int isValid(Vec2 pos, int width, int height) {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}

// Check if colors are equal
int colorEquals(Color c1, Color c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

void fillPolygon(Vec2 pos, Color fillColor) {
    Stack* stack = NULL;
    int width = 800;
    int height = 600;
    
    // Define the 8 adjacent directions
    Vec2 directions[8] = {
        {0, 1},   // North
        {1, 1},   // Northeast
        {1, 0},   // East
        {1, -1},  // Southeast
        {0, -1},  // South
        {-1, -1}, // Southwest
        {-1, 0},  // West
        {-1, 1}   // Northwest
    };
    
    // Push the starting position
    push(&stack, pos);

    int frame = 0;
    animate(frame);
    
    while (stack != NULL) {
//        displayStack(stack);
        Vec2 current = pop(&stack); 
        // Skip if pixel is out of bounds
        if (!isValid(current, width, height)) {
            continue;
        }
                
        Color currentColor = getPixel(current);
        
        // Skip if pixel is already filled or is boundary
        if (colorEquals(currentColor, fillColor) || colorEquals(currentColor, red)) {
            continue;
        }
        
        // Fill the current pixel
        setPixel(current, fillColor);
        
        // Check all 8 adjacent pixels
        for (int i = 0; i < 8; i+=2) {
            Vec2 next = {
                current.x + directions[i].x,
                current.y + directions[i].y
            };
            
            if (isValid(next, width, height)) {
                Color nextColor = getPixel(next);
                if (!colorEquals(nextColor, fillColor) && !colorEquals(nextColor, red)) {
                    push(&stack, next);
                }
            }
        }
        frame++;
        if (frame % 100 == 0)
            animate(frame / 100);
    }
}

void drawLine(Vec2 startPos, Vec2 endPos) {
    int dx = abs(endPos.x - startPos.x);
    int dy = abs(endPos.y - startPos.y);
    int sx = (endPos.x > startPos.x) ? 1 : -1; // Step for x direction
    int sy = (endPos.y > startPos.y) ? 1 : -1; // Step for y direction

    int err = dx - dy; // Error term
    Vec2 newPos = startPos;

    while (1) {
        setPixel(newPos, red); // Draw the current pixel

        if (newPos.x == endPos.x && newPos.y == endPos.y) {
            break; // Exit when we reach the end point
        }

        int e2 = 2 * err; // Double the error term

        if (e2 > -dy) {
            err -= dy;    // Adjust error
            newPos.x += sx; // Move in x direction
        }

        if (e2 < dx) {
            err += dx;    // Adjust error
            newPos.y += sy; // Move in y direction
        }
    }
}

void drawPolygon(Vec2 vertex[], int size){
    for (int i = 1; i <= size; i++){
        drawLine(vertex[i - 1], vertex[i%size]);
    }
}

int main(void) {
    startCanvas(800, 600);
    
    // Draw a triangle
    Vec2 vertices[3] = {{100, 100}, {300, 300}, {500, 100}};
    drawPolygon(vertices, 3);
    
    // Fill the triangle with blue color
    Color blue = {0, 0, 255};
    Vec2 startFill = {300, 200}; // Point inside the triangle
    fillPolygon(startFill, red);
    saveVideo("boundaryFill.mp4", 30);

//  Stack* stack = NULL;
//    push(&stack, (Vec2){100, 100});
//    push(&stack, (Vec2){200, 200});
//    displayStack(stack);
    
//    Vec2 item = pop(&stack);
//    printf("%d, %d", item.x, item.y);
//    displayStack(stack);
    display();
    endCanvas();
    return 0;
}
