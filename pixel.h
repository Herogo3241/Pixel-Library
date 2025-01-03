#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Vec2{
    int x;
    int y;
};

extern int width, height, maxvalue;
extern uint8_t **rChannel, **gChannel, **bChannel;


void startCanvas(int screenWidth, int screenHeight);
void setPixel(struct Vec2 pos, struct Color color);
void display();
void saveAsImage(const char* filename);
void endCanvas();



#endif
