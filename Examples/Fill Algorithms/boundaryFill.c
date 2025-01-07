#include <pixel.h>
#include <stdio.h>
#include <math.h>

typedef struct Node {
    Vec2 data;
    struct Node* next;
}Stack;


Color red = {255, 0, 0};


Stack* createNode(Vec2 data){
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    if (!newNode) {
        perror("Allocation Error");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
}

void push(Stack** top, Vec2 item){
    Stack* newNode = createNode(item);
    newNode->next = *top;
    *top = newNode;
}

void stackDisplay(Vec2 *stack){

    int n = sizeof(&stack) / sizeof(Vec2);
    for (int i = 0; i < n; i++){
        printf("%d, %d\n", stack[i].x, stack[i].y);
    }

}

Vec2 pop(Vec2 *stack){
    
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

int main(void){
    startCanvas(800, 600);
    Vec2 vertices[3] = {{100, 100}, {300, 300}, {500, 100}};
    //drawPolygon(vertices, 3);
    //display();
    endCanvas();

}
