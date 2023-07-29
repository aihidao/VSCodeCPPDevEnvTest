#ifndef __DRAW_UTILS__H__
#define __DRAW_UTILS__H__
#include "SDL.h"
class DrawUtils{
    public:
        static void drawTriangle(SDL_Renderer* renderer,SDL_Point points[],SDL_Color colors[]);
        static void drawQuadrilateral(SDL_Renderer* renderer,SDL_Point points[],SDL_Color colors[]);
        static SDL_Color overlayColors(SDL_Color colorA, SDL_Color colorB);
};
#endif