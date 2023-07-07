#ifndef __TEXT__H__
#define __TEXT__H__
#include <string>
#include <SDL.h>
class Text {
    private:
        std::string mStr;
        SDL_Rect mRect;
    public:
        Text();
        Text(std::string str);
        std::string getStr();
        void setStr(std::string strr);
        SDL_Rect getRect() ;
        void setRect(SDL_Rect rect);
        ~Text();
};
#endif