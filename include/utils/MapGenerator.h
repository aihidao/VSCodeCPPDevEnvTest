#ifndef __MAP__GENRERATOR__H__
#define __MAP__GENRERATOR__H__
#include <iostream>
#include <vector>
#include <cmath>

class MapGererator {
    public:
        int** altitudeMap = NULL;
        static double perlinNoise(double x, double y, double z);
    private:
        MapGererator(int width, int height, int seed);
};



#endif