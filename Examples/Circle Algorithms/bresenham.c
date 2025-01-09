#include <pixel.h>


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
    setPixel((struct Vec2){x + center.x, y + center.y}, color[0]);   // First 
    setPixel((struct Vec2){x + center.x, -y + center.y}, color[1]);  // Fourth 
    setPixel((struct Vec2){-x + center.x, y + center.y}, color[2]);  // Second 
    setPixel((struct Vec2){-x + center.x, -y + center.y}, color[3]); // Third 
    setPixel((struct Vec2){y + center.x, x + center.y}, color[4]);   // Fifth 
    setPixel((struct Vec2){y + center.x, -x + center.y}, color[5]);  // Sixth 
    setPixel((struct Vec2){-y + center.x, x + center.y}, color[6]);  // Seventh 
    setPixel((struct Vec2){-y + center.x, -x + center.y}, color[7]); // Eighth 
}


void bresenham(struct Vec2 center, int radius){
    int x = 0, y = radius;

    int p = 3 - 2 * radius;

    while(x <= y){
        setCirclePoint(x, y, center);
        if (p < 0){
            p = p + 4 * x + 6;
        }else {
            p = p + 4 * (x - y) + 1;
            y--;
        }
        x++;

    }
    
}


int main (void){
    startCanvas(800, 600);

    struct Vec2 center = {400, 300};
    struct Color color = {255, 255, 0};
    int radius = 200;
    bresenham(center, radius);

    display();
    saveAsImage("bresham.jpg");
    endCanvas();

}













