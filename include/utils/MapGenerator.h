#ifndef __MAP__GENRERATOR__H__
#define __MAP__GENRERATOR__H__
#include <iostream>
#include <vector>
#include <cmath>


class MapGenerator {
    public:
        int* mAltitudeMap = NULL;
        int mWidth = 0;
        int mHeight = 0;
        static double perlinNoise(double x, double y, double z);
        MapGenerator(int width, int height, int seed);
        void addOctaves(int minAltitude, int maxAltitude,double scale);
        void addCircle(int x, int y,int centerAltitude,double radius);
        void flat();
        int getAltitude(int x, int y);
        ~MapGenerator();
};



#endif