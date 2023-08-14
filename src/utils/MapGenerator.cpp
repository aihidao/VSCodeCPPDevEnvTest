#include "MapGenerator.h"
MapGenerator::MapGenerator(int width,int height,int seed) {
    // TODO
    // mAltitudeMap = new int*[width];
    // for (int i = 0; i < width; i++) {
    //     mAltitudeMap[i] = new int[height];
    // }
    mWidth = width;
    mHeight = height;
    mAltitudeMap = new int[mWidth * mHeight];
    for (int i = 0; i < mWidth * mHeight; i++) {
        int gridX = i % mWidth;
		int gridY = i / mWidth;
        mAltitudeMap[i] = 0;
    }
    addOctaves(-300,300,0.05);
    addOctaves(-300,300,0.005);
    addCircle(250,250,300,150);
    addCircle(100,100,300,150);
    flat();
    printf("stop\n");
}

void MapGenerator::addOctaves(int minAltitude, int maxAltitude,double scale) {
    int altitudeDiff = maxAltitude - minAltitude;
    for (int i = 0; i < mWidth * mHeight; i++) {
        int gridX = i % mWidth;
		int gridY = i / mWidth;
        mAltitudeMap[i] += minAltitude + std::round(MapGenerator::perlinNoise(gridX * scale, gridY * scale, 0)  * altitudeDiff);
    }
}

void MapGenerator::addCircle(int x, int y,int centerAltitude,double radius){
    for (int i = 0; i < mWidth * mHeight; i++) {
        int gridX = i % mWidth;
		int gridY = i / mWidth;

        //到中心越远，高度越低
        double distance = std::sqrt(std::pow(gridX - x, 2) + std::pow(gridY - y, 2));
        if(distance > radius){
            continue;
        }
        double altitudeDiff = centerAltitude * (1 - distance / radius);
        mAltitudeMap[i] += std::round(altitudeDiff);
        //mAltitudeMap[i] += ;
    }
}

void MapGenerator::flat(){
    for (int i = 0; i < mWidth * mHeight; i++) {
        int gridX = i % mWidth;
		int gridY = i / mWidth;
        int sumAltitude = mAltitudeMap[i];
        sumAltitude += getAltitude( gridX - 1, gridY - 1);
        sumAltitude += getAltitude( gridX - 0, gridY - 1);
        sumAltitude += getAltitude( gridX + 1, gridY - 1);
        sumAltitude += getAltitude( gridX - 1, gridY - 0);
        sumAltitude += getAltitude( gridX - 0, gridY - 0);
        sumAltitude += getAltitude( gridX + 1, gridY - 0);
        sumAltitude += getAltitude( gridX - 1, gridY + 1);
        sumAltitude += getAltitude( gridX - 0, gridY + 1);
        sumAltitude += getAltitude( gridX + 1, gridY + 1);
        mAltitudeMap[i] = sumAltitude / 9;
    }
}

int MapGenerator::getAltitude(int x, int y) {
    if(x < 0){
        x = 0;
    }

    if(x > mWidth - 1){
        x = mWidth - 1;
    }

    if(y < 0){
        y = 0;
    }

    if(y > mHeight - 1){
        y = mHeight - 1;
    }
    return mAltitudeMap[y * mWidth + x];
}

// 生成柏林噪声
double MapGenerator::perlinNoise(double x, double y, double z) {
    int p[512];
    int permutation[] = {
        151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 
        69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252,
        219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68,
        175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230,
        220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
        187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 
        52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16,
        58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155,
        167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246,
        97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
        49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236,
        205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
    };

    for (int i = 0; i < 256; i++) {
        p[256 + i] = p[i] = permutation[i];
    }

    #define fade(t) (t * t * t * (t * (t * 6 - 15) + 10))
    #define lerp(t, a, b) ((a) + (t) * ((b) - (a)))
    #define grad(hash, x, y, z) (((hash) & 1) == 0 ? (x) : -(x)) + (((hash) & 2) == 0 ? (y) : -(y)) + (((hash) & 4) == 0 ? (z) : -(z))

    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);
    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

    double result = lerp(
        w,
        lerp(
            v,
            lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
            lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))
        ),
        lerp(
            v,
            lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
            lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))
        )
    ) / 2.0 + 0.5;

    //#undef fade
    //#undef lerp
    //#undef grad

    // double result_0_to_minus_1 = (result + 1.0) / 2.0; // Scale from (-1 to 1) to (0 to 1)
    // result_0_to_minus_1 = 1.0 - result_0_to_minus_1; 

    return result;
}

MapGenerator::~MapGenerator() {
    // TODO
    delete mAltitudeMap;
}