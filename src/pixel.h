#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include <sys/stat.h>
#include <string.h>

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct Vec2{
    int x;
    int y;
} Vec2;

extern int width, height, maxvalue;
extern uint8_t **rChannel, **gChannel, **bChannel;


void startCanvas(int screenWidth, int screenHeight); // to generate the main window
void setPixel(Vec2 pos, Color color); // setting pixel
Color getPixel(Vec2 pos); // getting the color of the pixel
void display(); // to display the window
void animate(int frameNo); // for a storing each frame
void saveVideo(const char* filename, int frameRate); // animate must be called before saving the window
void saveAsImage(const char* filename); // call display before saving the image
void endCanvas(); // to free the allocates memory and close the window



#endif
