#include "Text.h"

Text::Text() {
}

Text::Text(const std::string& str) {
    mStr = str;
}

std::string Text::getStr() const {
    //printf("getStr:%s\n",mStr.c_str());
    return mStr;
}

void Text::setStr(const std::string& str) {
    mStr = str;
}

SDL_Rect Text::getRect() {
    return mRect;
}

void Text::setRect(SDL_Rect rect) {
    mRect = rect;
}

Text::~Text() {
}

