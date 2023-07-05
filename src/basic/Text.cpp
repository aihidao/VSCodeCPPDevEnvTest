#include "Text.h"

Text::Text(std::string str) {
    mStr = str;
}

std::string Text::getStr() {
    return mStr;
}

void Text::setStr(std::string str) {
    mStr = str;
}

Text::~Text() {
}

