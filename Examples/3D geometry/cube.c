#include <pixel.h>
#include <math.h>
#define normalizeColor(a) ((a) < 0 ? 0 : ((a) > 255 ? 255 : (a)))
#define round(a) ((int)(a + 0.5))
#define min(a, b) (a > b ? b : a)
#define max(a, b) (a > b ? a : b)

struct Color interpolateColor(struct Color c1, struct Color c2, float t) {
    struct Color result = {
        normalizeColor(c1.r + t * (c2.r - c1.r)),
        normalizeColor(c1.g + t * (c2.g - c1.g)),
        normalizeColor(c1.b + t * (c2.b - c1.b))
    };
    return result;
}

void fillTriangle(struct Vec2 v1, struct Vec2 v2, struct Vec2 v3,
                  struct Color c1, struct Color c2, struct Color c3) {
    int minX = min(min(v1.x, v2.x), v3.x);
    int maxX = max(max(v1.x, v2.x), v3.x);
    int minY = min(min(v1.y, v2.y), v3.y);
    int maxY = max(max(v1.y, v2.y), v3.y);

    float area = (v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y);
    
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            struct Vec2 p = {x, y};
            
            float w1 = ((v2.y - v3.y) * (p.x - v3.x) + (v3.x - v2.x) * (p.y - v3.y)) / area;
            float w2 = ((v3.y - v1.y) * (p.x - v3.x) + (v1.x - v3.x) * (p.y - v3.y)) / area;
            float w3 = 1.0f - w1 - w2;

            if (w1 >= 0 && w2 >= 0 && w3 >= 0) {
                struct Color color = {
                    normalizeColor(w1 * c1.r + w2 * c2.r + w3 * c3.r),
                    normalizeColor(w1 * c1.g + w2 * c2.g + w3 * c3.g),
                    normalizeColor(w1 * c1.b + w2 * c2.b + w3 * c3.b)
                };
                setPixel(p, color);
            }
        }
    }
}

void drawLine(struct Vec2 start, struct Vec2 end, struct Color color){

    int dx = end.x - start.x;
    int dy = end.y - start.y;

    int steps = abs(dx) > abs(dy) ? dx : dy;

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    struct Vec2 pos = start;
    for(int i = 0; i<steps; i++){
        setPixel(pos, color);
        pos.x += xInc;
        pos.y += yInc;
    }

}

void drawGradientCube(struct Vec2 origin, int size) {
    // Define vertices
    struct Vec2 frontTopLeft = {origin.x, origin.y};
    struct Vec2 frontTopRight = {origin.x + size, origin.y};
    struct Vec2 frontBottomLeft = {origin.x, origin.y - size};
    struct Vec2 frontBottomRight = {origin.x + size, origin.y - size};
    
    struct Vec2 backTopLeft = {origin.x - size/2, origin.y + size/2};
    struct Vec2 backTopRight = {origin.x + size/2, origin.y + size/2};
    struct Vec2 backBottomLeft = {origin.x - size/2, origin.y - size/2};
    struct Vec2 backBottomRight = {origin.x + size/2, origin.y - size/2};

    // Define colors for vertices
    struct Color red = {255, 0, 0};
    struct Color green = {0, 255, 0};
    struct Color blue = {0, 0, 255};
    struct Color yellow = {255, 255, 0};
    struct Color white = {255, 255, 255};
    
    // Draw faces with gradients
    // Front face
    fillTriangle(frontTopLeft, frontTopRight, frontBottomLeft, red, green, blue);
    fillTriangle(frontBottomRight, frontBottomLeft, frontTopRight, green, blue, yellow);
    
    // Right face
    fillTriangle(frontTopRight, backTopRight, frontBottomRight, green, yellow, blue);
    fillTriangle(backBottomRight, frontBottomRight, backTopRight, red, blue, yellow);
    
    // Top face
    fillTriangle(frontTopLeft, frontTopRight, backTopLeft, red, green, yellow);
    fillTriangle(backTopRight, backTopLeft, frontTopRight, blue, yellow, green);

    // Left face
    fillTriangle(backTopLeft, backBottomLeft, frontTopLeft, red, green, blue);
    fillTriangle(frontTopLeft, frontBottomLeft, backBottomLeft, blue, yellow, green);
    

    // Draw borders for the cube
    // Edges of the front face
    drawLine(frontTopLeft, frontTopRight, white);
    drawLine(frontBottomRight, frontTopRight, white);
    drawLine(frontBottomLeft, frontBottomRight, white);
    drawLine(frontBottomLeft, frontTopLeft, white);

    // Edges of the top face
    drawLine(backTopLeft, backTopRight, white);
    drawLine(backBottomRight, backTopRight, white);
    drawLine(backBottomLeft, backBottomRight, white);
    drawLine(backBottomLeft, backTopLeft, white);


    // Connection between front and back
    drawLine(frontTopLeft, backTopLeft, white);
    drawLine(frontTopRight, backTopRight, white);
    drawLine(frontBottomLeft, backBottomLeft, white);
    drawLine(frontBottomRight, backBottomRight, white);

}

int main() {
    startCanvas(800, 600);
    struct Vec2 origin = {400, 300};
    int size = 200;
    
    drawGradientCube(origin, size);
    display();
    saveAsImage("cube.png");
    endCanvas();
    return 0;
}
