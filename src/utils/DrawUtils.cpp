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