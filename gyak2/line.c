#include "line.h"

void set_line_coords(Line *line, int x1, int y1, int x2, int y2)
{
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
}

void set_line_color(Line *line, Color color)
{
    line->color = color;
}