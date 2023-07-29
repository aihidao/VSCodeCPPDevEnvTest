#ifndef __CELL_CHUNK__H__
#define __CELL_CHUNK__H__
class CellChunk{
    private:
        int mWidth;
        int mHeight;
        int mX;
        int mY;
        int mAltitude;
        int mAltitudeMap[];
    public:
        CellChunk(int width,int height,int x,int y,int altitude);
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        int getAltitude();
        int getAltitudeMap();
        ~CellChunk();
};
#endif