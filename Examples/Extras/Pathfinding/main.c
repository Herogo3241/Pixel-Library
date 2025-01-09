#include <pixel.h>

#define round(a) ((int)(a + 0.5))
#define abs(a) ((a > 0 ? a : -a))


void drawLine(Vec2 startPos, Vec2 endPos, Color color){
    int dx = endPos.x - startPos.x;
    int dy = endPos.y - startPos.y;

    int steps = abs(dx) > abs(dy) ? dx : dy;
    int xInc = dx/steps;
    int yInc = dy/steps;

    int x = startPos.x;
    int y = startPos.y;
    for(int i = 0; i <= steps; i++){    
        Vec2 newPos = {round(x), round(y)};
        setPixel(newPos, color);
        x += xInc;
        y += yInc;
    }
}

void drawSquare(Vec2 pos, int size, Color color){
    //vertices
    Vec2 topLeft = {pos.x - size/2, pos.y + size/2};
    Vec2 topRight = {pos.x + size/2, pos.y + size/2};
    Vec2 bottomLeft = {pos.x - size/2, pos.y - size/2};
    Vec2 bottomRight = {pos.x + size/2, pos.y - size/2};

    //draw edges
    drawLine(topLeft, topRight, color);
    drawLine(bottomLeft, topLeft, color);
    drawLine(bottomLeft, bottomRight, color);
    drawLine(bottomRight, topRight, color);


}

void setup(){

    Color green = {0, 255, 0};
    drawSquare((Vec2){10, 10}, 20, green);
    int size = 20;
    for(int j = 0; j < 600; j+=size){
        for (int i = 0; i < 800; i+=size){
            drawSquare((Vec2){i + size/2, j + size / 2}, size, green);
        }
    }

}

int main(){
    startCanvas(800, 600);
    setup();

    display();
    endCanvas();
}
