/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#ifndef MF_UTILS_H
#define MF_UTILS_H

#include <string>  // std::string

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

class RandomGenerator {
private:
    unsigned int _seed;

public:
    void setSeed(int seed);
    double next();
    int nextInt(int maximum);
    int getArrayRandomElement(int intArray[], int amount);
};

extern const char *HexToStringLookup[256];

class MD5obj {
private:
    uint32_t h[4]; // These vars will contain the hash (little-endian)
    uint32_t r[64] = { // r specifies the per-round shift amounts
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    uint32_t k[64] = { // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    void MD5(uint8_t *initial_msg, size_t initial_len); // https://gist.github.com/creationix/4710780

public:
    void calculate(const std::string srcStr);
    void calculate(const char *srcStr);
    std::string getHashString(); // 效能不高的函數，盡量少用
    int getDigestInt(int index);
};

class MD5RandomGenerator : public RandomGenerator, private MD5obj {
public:
    void setSeed(const std::string &code, int randomSeed); // randomSeed >= 0 && randomSeed <= 99
};

class NormalDistribution {
private:
    double _mean, _deviation;

public:
    void setValue(double mean, double deviation);
    double random(RandomGenerator &srcRG);
};

#endif // MF_UTILS_H
