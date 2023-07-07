#include "DebugInfoBox.h"

DebugInfoBox::DebugInfoBox(SDL_Renderer* renderer) {
    mRenderer = renderer;
    mTextRender = new TextRender(renderer);
    textList = std::vector<Text>();
}

void DebugInfoBox::push(Text text) {
    textList.push_back(text);
}

void DebugInfoBox::draw() {
    int x = 0;
    int y = 0;
    for (Text text : textList) {
        //mTextRender->drawText(text.getStr(), x, y);
        y += 20;
    }
}

DebugInfoBox::~DebugInfoBox() {
    delete mTextRender;
}

