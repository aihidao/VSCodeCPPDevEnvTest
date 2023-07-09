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
        int mWidth = 200;
        int mHeight = 0;
        // 0 表示左边 1 表示右边
        int mPos = 0;
        std::vector<Text*> textList;
    public:
        DebugInfoBox(SDL_Renderer* renderer);
        DebugInfoBox(SDL_Renderer* renderer, TextRender* mTextRender);
        void handleEvent(SDL_Event* e);
        void push(Text* text);
        void draw();
        ~DebugInfoBox();
};
#endif