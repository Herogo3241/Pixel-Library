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
    int frame = 0;
    for (int i = 0; i < steps; i++){
        setPixel((Vec2){round(x), round(y)}, (Color) {255, 0, 0});
        x += xIncrement;
        y += yIncrement;
        if(frame % 10 == 0)
            animate(frame);
    }
}

int main() {
    Vec2 startPos = {100, 150};
    Vec2 endPos = {500, 550};

    startCanvas(800, 600);
    DDA(startPos, endPos);
    display();
    saveAsImage("DDA.png");
    saveVideo("DDA.mp4", 30);
    endCanvas();

}



