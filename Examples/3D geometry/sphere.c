#include <pixel.h>
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))  



struct Vec3 {
    double x, y, z;  
};


struct Vec3 normalize(struct Vec3 v) {
    double mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (mag == 0) {  // Added check for zero division
        return (struct Vec3){0, 0, 0};
    }
    struct Vec3 result = {v.x / mag, v.y / mag, v.z / mag};
    return result;
}

double dotProduct(struct Vec3 v1, struct Vec3 v2) {  
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double circleFunction(int x, int y, int r) { 
    return (x * x + y * y - r * r);
}

void drawSphere(struct Vec2 center, int radius, struct Color color, struct Vec3 lightSrc, struct Vec2 canvasSize) {
    for(int y = 0; y < canvasSize.y; y++) {
        for(int x = 0; x < canvasSize.x; x++) {
            int dx = x - center.x;
            int dy = y - center.y;
            double circle_val = circleFunction(dx, dy, radius);

            if (circle_val <= 0) {
                struct Vec2 coord = {x, y};
                double z = sqrt(-circle_val);
                
                struct Vec3 surfaceNormal = normalize((struct Vec3){
                    (double)dx,  
                    (double)dy,
                    z
                });
                
                struct Vec3 lightDir = normalize((struct Vec3){
                    lightSrc.x - x,
                    lightSrc.y - y,
                    lightSrc.z - z
                });

                double lightIntensity = max(0, dotProduct(surfaceNormal, lightDir));
                
                
                struct Color colorIntensity = {
                    (int)(color.r * lightIntensity) & 255,
                    (int)(color.g * lightIntensity) & 255,
                    (int)(color.b * lightIntensity) & 255
                };

                setPixel(coord, colorIntensity);
            }
        }
    }
}

int main(void) {
    struct Vec2 canvasSize = {800, 600};
    startCanvas(canvasSize.x, canvasSize.y);
    
    struct Vec2 center = {400, 300};
    int radius = 100;  
    struct Color color = {255, 253, 241};
    struct Vec3 lightSrc = {-2000, 1000, 1200};  
    int frame = 0;
    while(lightSrc.x <= 2000){
        drawSphere(center, radius, color, lightSrc, canvasSize);
        lightSrc.x += 5;
        animate(frame);
        frame++;
    }
    saveVideo("sphere.mp4", 60);

    display();
    //saveAsImage("sphere.png");
    endCanvas();
    
    return 0; 
}
