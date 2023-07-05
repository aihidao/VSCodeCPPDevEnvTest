#ifndef __DEBUG_INFO_BOX__H__
#define __DEBUG_INFO_BOX__H__
#include <SDL.h>
#include "TextRender.h"
#include <string>
#include "Text.h"
#include <vector>
class DebugInfoBox {
    private:
        SDL_Renderer* mRenderer = NULL;
        TextRender* mTextRender = NULL;
        std::vector<Text> textList;
    public:
        DebugInfoBox(SDL_Renderer* renderer);
        void push(Text text);
        void draw();
        ~DebugInfoBox();
};
#endif