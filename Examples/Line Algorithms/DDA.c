#include <pixel.h>
#include "stdio.h"

#define round(a) ((int)(a + 0.5))

void DDA(struct Vec2 startPos, struct Vec2 endPos){
    int dx = endPos.x - startPos.x;
    int dy = endPos.y - startPos.y;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx/(float)steps;
    float yIncrement = dy/(float)steps;
    
    float x = startPos.x;
    float y = startPos.y;

    for (int i = 0; i < steps; i++){
        setPixel((struct Vec2){round(x), round(y)}, (struct Color) {255, 0, 0});
        x += xIncrement;
        y += yIncrement;
    }
}

int main() {
    struct Vec2 startPos = {4, 4};
    struct Vec2 endPos = {19, 20};

    startCanvas(64, 64);
    DDA(startPos, endPos);
    display();
    endCanvas();

}



