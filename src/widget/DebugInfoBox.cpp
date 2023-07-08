#include "DebugInfoBox.h"
#include "Game.h"
DebugInfoBox::DebugInfoBox(SDL_Renderer* renderer) {
    mRenderer = renderer;
    mTextRender = new TextRender(renderer, 15, {0, 255, 0, 255});
    textList = std::vector<Text*>();
}

void DebugInfoBox::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION) {
        int x = e->button.x;
        int y = e->button.y;
        if(mPos == 0){
            if (x >= 0 && x <= mWidth && y >= 0 && y <= mHeight) {
                mPos = 1;
            }
        }else{
            if (x >= Game::SCREEN_WIDTH - mWidth && y >= 0 && y <= mHeight) {
                mPos = 0;
            }
        }

    }
}

void DebugInfoBox::push(Text* text) {
    textList.push_back(text);
}

void DebugInfoBox::draw() {
    int x = 0;
    int y = 0;
    if(mPos == 1){
        x = Game::SCREEN_WIDTH - mWidth;
    }

    const SDL_Rect rect = {x, y, mWidth, mHeight};
    SDL_SetRenderDrawColor(mRenderer,0,0,0,255);
    SDL_RenderFillRect(mRenderer, &rect);

    //int maxWidth = mWidth;
    for (Text* text : textList) {
        mTextRender->drawText(text, x + 10, y + 10,TextRender::RENDER_TYPE_NOMAL);
        // if(maxWidth < text->getRect().w){
        //     maxWidth = text->getRect().w;
        // }
        y += text->getRect().h;
       
    }
    //mWidth = maxWidth;
    mHeight = y + 20;
}

DebugInfoBox::~DebugInfoBox() {
    delete mTextRender;
}

