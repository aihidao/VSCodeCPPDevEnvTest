#include "TextRender.h"

TextRender::TextRender(SDL_Renderer* renderer) {
    mRenderer = renderer;
    loadAssets();
}

TextRender::TextRender(SDL_Renderer* renderer, int fontSize, SDL_Color fontColor) {
    mRenderer = renderer;
    loadAssets(fontSize, fontColor);
}

void TextRender::loadAssets() {
	mFont = FC_CreateFont();
	#ifdef SDL_GPU_VERSION_MAJOR
		FC_LoadFont(mFont, "assets/SmileySans-Oblique.ttf", 20, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);
	#else
		FC_LoadFont(mFont, mRenderer, "assets/SmileySans-Oblique.ttf", 25, FC_MakeColor(255,0,0,255), TTF_STYLE_NORMAL);
	#endif
}

void TextRender::loadAssets(int fontSize, SDL_Color fontColor) {
	if(mFont != NULL){
		FC_FreeFont(mFont);
	}

	if(!(fontColor.r == 0 && fontColor.g == 0 && fontColor.b == 0 && fontColor.a == 0)){
		mFontColor.r = fontColor.r;
		mFontColor.g = fontColor.g;
		mFontColor.b = fontColor.b;
		mFontColor.a = fontColor.a;
	}
	mFont = FC_CreateFont();
	#ifdef SDL_GPU_VERSION_MAJOR
		FC_LoadFont(mFont, "assets/SmileySans-Oblique.ttf", fontSize, FC_MakeColor(color.r,color.g,color.b,color.a), TTF_STYLE_NORMAL);
	#else
		FC_LoadFont(mFont, mRenderer, "assets/SmileySans-Oblique.ttf", fontSize, FC_MakeColor(mFontColor.r,mFontColor.g,mFontColor.b,mFontColor.a), TTF_STYLE_NORMAL);
	#endif
}

void TextRender::drawText(Text* text,int x, int y,int renderMode) {
	int renderModeX = x;
	int renderModeY = y;
	if((renderMode & TextRender::RENDER_TYPE_W_CENTER) == TextRender::RENDER_TYPE_W_CENTER){
		renderModeX -= text->getRect().w / 2;
	}

	if((renderMode & TextRender::RENDER_TYPE_H_CENTER) == TextRender::RENDER_TYPE_H_CENTER){
		renderModeY -= text->getRect().h / 2;
	}

    FC_Rect rect = FC_DrawColor(mFont, mRenderer, renderModeX, renderModeY, mFontColor, text->getStr().c_str());
	rect.x = x;
	rect.y = y;
	text->setRect(rect);
}

void TextRender::drawString(std::string str,int x, int y) {
    FC_Rect rect = FC_Draw(mFont, mRenderer, x, y, str.c_str());
    FC_DrawColor(mFont, mRenderer, x, y, mFontColor, str.c_str());
}

TextRender::~TextRender() {
    FC_FreeFont(mFont);
}
