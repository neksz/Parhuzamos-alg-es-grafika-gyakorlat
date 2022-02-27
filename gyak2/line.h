#ifndef LINE_H
#define LINE_H
#include "color.h"

typedef struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
    Color color;
} Line;

void set_line_coords(Line *line, int x1, int y1, int x2, int y2);

void set_line_color(Line *line, Color color);

#endif