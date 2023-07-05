#ifndef __TEXT__H__
#define __TEXT__H__
#include <string>
class Text {
    private:
        std::string mStr;
    public:
        Text(std::string str);
        std::string getStr();
        void setStr(std::string str);
        ~Text();
};
#endif