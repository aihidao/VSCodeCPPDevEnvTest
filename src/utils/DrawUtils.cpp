#include "DrawUtils.h"
#include <vector>
void DrawUtils::drawTriangle(SDL_Renderer* renderer,SDL_Point points[],SDL_Color colors[]){
    const std::vector< SDL_Vertex > triangleInfo =
    {
        { SDL_FPoint{ (float)points[0].x, (float)points[0].y}, colors[0], SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[1].x, (float)points[1].y}, colors[1], SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[2].x, (float)points[2].y}, colors[2], SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry( renderer, nullptr, triangleInfo.data(), triangleInfo.size(), nullptr, 0 );
} 

void DrawUtils::drawQuadrilateral(SDL_Renderer* renderer,SDL_Point points[],SDL_Color colors[]){
    const std::vector< SDL_Vertex > gourdRightVert =
    {
        { SDL_FPoint{ (float)points[1].x, (float)points[1].y}, colors[1], SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[2].x, (float)points[2].y}, colors[2], SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[3].x, (float)points[3].y}, colors[3], SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry( renderer, nullptr, gourdRightVert.data(), gourdRightVert.size(), nullptr, 0 );
    const std::vector< SDL_Vertex > gourdLeftVert =
    {
        { SDL_FPoint{ (float)points[1].x, (float)points[1].y}, colors[1], SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[0].x, (float)points[0].y}, colors[0], SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)points[3].x, (float)points[3].y}, colors[3], SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry( renderer, nullptr, gourdLeftVert.data(), gourdLeftVert.size(), nullptr, 0 );
}

SDL_Color DrawUtils::overlayColors(SDL_Color colorA, SDL_Color colorB){
    // Uint8 r = (1 - colorB.a) * colorA.r + (colorB.a * colorB.r);
    // Uint8 g = (1 - colorB.a) * colorA.g + (colorB.a * colorB.g);
    // Uint8 b = (1 - colorB.a) * colorA.b + (colorB.a * colorB.b);
    // Uint8 a = colorA.a + (colorB.a * (255 - colorA.a)) / 255;

    // Uint8 r = (colorA.r * colorB.r) / 255;
    // Uint8 g = (colorA.g * colorB.g) / 255;
    // Uint8 b = (colorA.b * colorB.b) / 255;
    // Uint8 a = std::max(colorA.b, colorB.b);

    Uint8 r = colorA.r * (colorA.a + colorB.a * (1 - colorA.a)) / 255;
    Uint8 g = colorA.g * (colorA.a + colorB.a * (1 - colorA.a)) / 255;
    Uint8 b = colorA.b * (colorA.a + colorB.a * (1 - colorA.a)) / 255;
    Uint8 a = colorA.a + colorB.a * (1 - colorA.a);

    return {r, g, b, a};
}