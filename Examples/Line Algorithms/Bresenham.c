#include <pixel.h>

#define abs(a) ((a > 0 ? a : -a))

void lineBres(Vec2 startPos, Vec2 endPos, Color color){
    int dx = abs(endPos.x - startPos.x);
    int dy = abs(endPos.y - startPos.y);

    int x, y, p = 2 * dy - dx;

    if (startPos.x > endPos.x){
        x = endPos.x;
        y = endPos.y;
        endPos.x = startPos.x;
    }else{
        x = startPos.x;
        y = startPos.y;
    }

    Vec2 newPos = {x, y};
    setPixel(newPos, color);

    while(newPos.x < endPos.x){
        newPos.x++;
        if (p < 0)
            p += 2 * dy;
        else{
            newPos.y++;
            p += 2 * (dy - dx);
        }

        setPixel(newPos, color);
    }
}


int main(void){
    startCanvas(800, 600);

    Vec2 startPos = {220, 55};
    Vec2 endPos = {600, 543};
    Color color = {123, 213, 154};
    lineBres(startPos, endPos, color);
    display();
    saveAsImage("bresLine.png");
    endCanvas();
}
