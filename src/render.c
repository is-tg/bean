#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

typedef struct {
    SDL_Point point;
    int radius;
} Circle;

void DrawCircle(SDL_Renderer* renderer, Circle* circle, Color* color)
{
    int xm = circle->point.x,
        ym = circle->point.y,
        r = circle->radius;
    int x = -r, y = 0;
    int err = 2 - 2 * r;
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

    do {
        const SDL_FPoint points[4] = {
            { xm - x, ym + y },
            { xm - y, ym - x },
            { xm + x, ym - y },
            { xm + y, ym + x }
        };
        SDL_RenderPoints(renderer, points, 4);

        r = err;
        if (r <= y)
            err += ++y * 2 + 1;
        if (r > x || err > y)
            err += ++x * 2 + 1;
    } while (x < 0);
}
