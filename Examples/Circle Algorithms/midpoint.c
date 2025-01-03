#include "../../pixel.h"


struct Color color[8] = {
    {34, 177, 76},    // Color 1: Greenish
    {255, 102, 0},    // Color 2: Orange
    {63, 81, 181},    // Color 3: Blue
    {255, 255, 0},    // Color 4: Yellow
    {0, 255, 255},    // Color 5: Cyan
    {255, 0, 255},    // Color 6: Magenta
    {0, 128, 255},    // Color 7: Light Blue
    {255, 165, 0}     // Color 8: Orange
};


void setCirclePoint(int x, int y, struct Vec2 center) {
    setPixel((struct Vec2){x + center.x, y + center.y}, color[0]);   // First quadrant
    setPixel((struct Vec2){x + center.x, -y + center.y}, color[1]);  // Fourth quadrant
    setPixel((struct Vec2){-x + center.x, y + center.y}, color[2]);  // Second quadrant
    setPixel((struct Vec2){-x + center.x, -y + center.y}, color[3]); // Third quadrant
    setPixel((struct Vec2){y + center.x, x + center.y}, color[4]);   // Fifth quadrant
    setPixel((struct Vec2){y + center.x, -x + center.y}, color[5]);  // Sixth quadrant
    setPixel((struct Vec2){-y + center.x, x + center.y}, color[6]);  // Seventh quadrant
    setPixel((struct Vec2){-y + center.x, -x + center.y}, color[7]); // Eighth quadrant
}


void midpoint(struct Vec2 center, int radius){
    int x = 0, y = radius;

    int p = 1-radius;

    while(y >= x){
        setCirclePoint(x, y, center);
        x++;
        if (p < 0){
            p = p + 2*x + 1;
        }else {
            y--;
            p = p + 2*x - 2*y + 1;
        }

    }
    
}


int main (void){
    startCanvas (1200, 960);

    struct Vec2 center = {600, 480};
    struct Color color = {255, 255, 0};
    int radius = 200;
    midpoint(center, radius);

    display();
    saveAsImage("midpoint_circle.png");
    endCanvas();

}













