#include "TextRender.h"

TextRender::TextRender(SDL_Renderer* renderer) {
    mRenderer = renderer;
    loadAssets();
}

void TextRender::loadAssets() {
	mFont = FC_CreateFont();
	#ifdef SDL_GPU_VERSION_MAJOR
		FC_LoadFont(mFont, "assets/SmileySans-Oblique.ttf", 20, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);
	#else
		FC_LoadFont(mFont, mRenderer, "assets/SmileySans-Oblique.ttf", 25, FC_MakeColor(255,0,0,255), TTF_STYLE_NORMAL);
	#endif
}

void TextRender::loadAssets(int fontSize) {
	mFont = FC_CreateFont();
	#ifdef SDL_GPU_VERSION_MAJOR
		FC_LoadFont(mFont, "assets/SmileySans-Oblique.ttf", fontSize, FC_MakeColor(color.r,color.g,color.b,color.a), TTF_STYLE_NORMAL);
	#else
		FC_LoadFont(mFont, mRenderer, "assets/SmileySans-Oblique.ttf", fontSize, FC_MakeColor(mFontColor.r,mFontColor.g,mFontColor.b,mFontColor.a), TTF_STYLE_NORMAL);
	#endif
}

void TextRender::drawText(std::string str,int x, int y) {
    FC_Rect rect = FC_Draw(mFont, mRenderer, x, y, str.c_str());
	rect.y += rect.h;
	rect.w *= 2;
	rect.h *= 2;
    FC_DrawColor(mFont, mRenderer, x, y, mFontColor, str.c_str());
	FC_SetDefaultColor(mFont,FC_MakeColor(255,255,0,255));
	FC_DrawBoxScale(mFont, mRenderer, rect , FC_MakeScale(2,2) , str.c_str());
}

TextRender::~TextRender() {
    FC_FreeFont(mFont);
}
