#include <SDL2/SDL.h>
#include "line.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
        {
            SDL_bool done = SDL_FALSE;

            Line line;
            Color color;

            SDL_Rect redRect;
            redRect.h = 15;
            redRect.w = 15;
            redRect.x = 0;
            redRect.y = 0;
            SDL_Rect greenRect;
            greenRect.h = 15;
            greenRect.w = 15;
            greenRect.x = 15;
            greenRect.y = 0;
            SDL_Rect blueRect;
            blueRect.h = 15;
            blueRect.w = 15;
            blueRect.x = 30;
            blueRect.y = 0;

            int count = 0;

            set_color(&color, 100, 255, 255);
            set_line_coords(&line, 300, 240, 400, 240);
            set_line_color(&line, color);

            while (!done)
            {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &redRect);
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &greenRect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &blueRect);

                SDL_SetRenderDrawColor(renderer, line.color.r, line.color.g, line.color.b, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);

                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        done = SDL_TRUE;
                    }
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if ((event.button.x >= 0 && event.button.x <= 45) && (event.button.y <= 15 && event.button.y >= 0))
                        {
                            Color tempColor;
                            if (event.button.x >= 0 && event.button.x <= 15)
                            {
                                // Red
                                set_color(&tempColor, 255, 0, 0);
                                printf("Set to red color\n");
                            }
                            else if (event.button.x >= 15 && event.button.x <= 30)
                            {
                                // Green
                                set_color(&tempColor, 0, 255, 0);
                                printf("Set to green color\n");
                            }
                            else
                            {
                                // Blue
                                set_color(&tempColor, 0, 0, 255);
                                printf("Set to blue color\n");
                            }
                            set_line_color(&line, tempColor);
                        }
                        else
                        {
                            Line tempLine;
                            set_line_coords(&tempLine, line.x1, line.y1, line.x2, line.y2);
                            set_line_color(&tempLine, line.color);
                            if (count == 0)
                            {
                                set_line_coords(&line, tempLine.x1, tempLine.y1, event.button.x, event.button.y);
                                printf("x:%d\ty:%d\n", event.button.x, event.button.y);

                                count = 1;
                            }
                            else if (count == 1)
                            {
                                set_line_coords(&line, event.button.x, event.button.y, tempLine.x2, tempLine.y2);
                                printf("x:%d\ty:%d\n", event.button.x, event.button.y);

                                count = 0;
                            }
                        }
                    }
                }
            }
        }

        if (renderer)
        {
            SDL_DestroyRenderer(renderer);
        }
        if (window)
        {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}