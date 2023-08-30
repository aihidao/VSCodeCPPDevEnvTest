#include "GridCoordinateConverterUtils.h"
#include "GameStage.h"
#include "Game.h"
SDL_Point GridCoordinateConverterUtils::convertToDraw(SDL_Point position) {
    SDL_Point result;
    result.x = (position.x - position.y);
    result.y = (position.x + position.y) / 2;
    return result;
}

SDL_Point GridCoordinateConverterUtils::convertToReal(SDL_Point position) {
    SDL_Point result;
    // result.x = ((- GameStage::STAGE_POSITION_X -  2 * GameStage::STAGE_POSITION_Y + position.x + 2 * position.y) / 2);
    // result.y = ((  GameStage::STAGE_POSITION_X - 2 * GameStage::STAGE_POSITION_Y - position.x + 2 * position.y) / 2);
    result.x = ((- GameStage::STAGE_POSITION_X -   2 * GameStage::STAGE_POSITION_Y + (position.x + 2 * position.y) / GameStage::GAME_MAP_SCALE) / 2);
    result.y = ((  GameStage::STAGE_POSITION_X -  2 * GameStage::STAGE_POSITION_Y + (- position.x + 2 * position.y) / GameStage::GAME_MAP_SCALE) / 2);
    return result;
}

// SDL_Point GridCoordinateConverterUtils::getTopRightCellInRealForDraw(SDL_Point position) {
//     SDL_Point result;
//     result.x = (- GameStage::STAGE_POSITION_X -  2 * GameStage::STAGE_POSITION_Y + position.x + 2 * position.y) / 2;
//     result.y = (  GameStage::STAGE_POSITION_X - 2 * GameStage::STAGE_POSITION_Y - position.x + 2 * position.y) / 2;
//     return result;
// }