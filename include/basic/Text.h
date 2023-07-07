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
        Text(const std::string& str);
        std::string getStr() const;
        void setStr(const std::string& str);
        SDL_Rect getRect() ;
        void setRect(SDL_Rect rect);
        ~Text();
};
#endif