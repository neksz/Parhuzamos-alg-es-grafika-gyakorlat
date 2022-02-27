#ifndef COLOR_H
#define COLOR_H

typedef struct Color
{
    int r;
    int g;
    int b;
} Color;

void set_color(Color *color, int r, int g, int b);

#endif