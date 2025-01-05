#include <pixel.h>
#include "stdio.h"

#define round(a) ((int)(a + 0.5))

void DDA(Vec2 startPos, Vec2 endPos){
    int dx = endPos.x - startPos.x;
    int dy = endPos.y - startPos.y;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx/(float)steps;
    float yIncrement = dy/(float)steps;
    
    float x = startPos.x;
    float y = startPos.y;

    for (int i = 0; i < steps; i++){
        setPixel((Vec2){round(x), round(y)}, (Color) {255, 0, 0});
        x += xIncrement;
        y += yIncrement;
        animate(i);
    }
}

int main() {
    Vec2 startPos = {5, 10};
    Vec2 endPos = {50, 50};

    startCanvas(64, 64);
    DDA(startPos, endPos);
    display();
    saveAsImage("line.png");
    saveVideo("line.mp4", 1);
    endCanvas();

}



