#ifndef __GRID_COORDINATE_CONVERTER_UTILS__H__
#define __GRID_COORDINATE_CONVERTER_UTILS__H__
#include "SDL.h"
class GridCoordinateConverterUtils{
    public:
        static SDL_Point convertToDraw(SDL_Point position);
        static SDL_Point convertToReal(SDL_Point position);
};
#endif