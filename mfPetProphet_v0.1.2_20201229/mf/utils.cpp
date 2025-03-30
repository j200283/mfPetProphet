/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#include <cmath>         // abs, log, sqrt
#include <cstdio>        // sprintf
#include <cstring>       // strcat, strcpy
#include <iomanip>       // std::setfill, std::setw
#include <ios>           // std::hex
#include <sstream>       // std::stringstream
#include <string>        // std::string

#include "utils.h"

void RandomGenerator::setSeed(int seed) {
    _seed = abs(seed);
}

double RandomGenerator::next() {
    if(_seed == 0) {
        _seed = 14748364;
        return 0.0;
    }

    _seed = (unsigned int)(((unsigned long long int)(_seed) * 16807) % 2147483647);
    return (double)(_seed) / 2147483647.0;
}

int RandomGenerator::nextInt(int maximum) {
    return (int)(floor((double)(maximum + 1) * next()));
}

int RandomGenerator::getArrayRandomElement(int intArray[], int amount) {
    if(amount > 0) {
        return intArray[nextInt(amount - 1)];
    }

    return 0;
}

const char *HexToStringLookup[256] = {
    "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
    "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
    "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
    "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
    "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
    "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
    "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
    "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
    "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
    "c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
    "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db", "dc", "dd", "de", "df",
    "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
    "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
};

void MD5obj::MD5(uint8_t *initial_msg, size_t initial_len) {
    // Message (to prepare)
    uint8_t *msg = NULL;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

    // r specifies the per-round shift amounts
    /* uint32_t r[] define in mfPetTester.h, initialize in constructor of mfPetTester class */

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    /* uint32_t k[] define in mfPetTester.h, initialize in constructor of mfPetTester class */

    h[0] = 0x67452301;
    h[1] = 0xefcdab89;
    h[2] = 0x98badcfe;
    h[3] = 0x10325476;

    // Pre-processing: adding a single 1 bit
    //append "1" bit to message
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */

    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message

    int new_len;
    for(new_len = initial_len*8 + 1; new_len%512!=448; new_len++);
    new_len /= 8;

    msg = (uint8_t*)calloc(new_len + 64, 1); // also appends "0" bits
    // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit

    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer

    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {

        // break chunk into sixteen 32-bit words w[j], 0 ? j ? 15
        uint32_t *w = (uint32_t *) (msg + offset);

        // Initialize hash value for this chunk:
        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];

        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {

            uint32_t f, g;

            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;

        }

        // Add this chunk's hash to result so far:

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;

    }

    // cleanup
    free(msg);
}

void MD5obj::calculate(const std::string srcStr) {
    MD5((uint8_t*)srcStr.c_str(), srcStr.length());
}

void MD5obj::calculate(const char *srcStr) {
    MD5((uint8_t*)srcStr, strlen(srcStr));
}

std::string MD5obj::getHashString() {
    std::stringstream ss;
    unsigned int temp;

    for(int a = 0; a < 4; a++) { // Convert hash value (little-endian) to string
        temp = h[a];
        temp = ((temp & 0x000000FF) << 24) | ((temp & 0x0000FF00) << 8) | ((temp & 0x00FF0000) >> 8) | ((temp & 0xFF000000) >> 24);
        ss << std::setw(8) << std::setfill('0') << std::hex << temp;
    }

    return ss.str();
}

int MD5obj::getDigestInt(int index) {

    if(index >= 0 && index < 4) {
        return h[index];
    } else {
        return 0;
    }
}

void MD5RandomGenerator::setSeed(const std::string &code, int randomSeed) {
    char temp[code.length() + 5];
    char buf[5]; // "+" (1 char) + randomSeed (1~2 char) + ":" (1 char) + "\0" (1 char) = (4~5 char)

    temp[0] = '\0';
    strcpy(temp, code.c_str());
    sprintf(buf, "+%d:", randomSeed);
    strcat(temp, buf);
    calculate(temp);
    RandomGenerator::setSeed(getDigestInt(randomSeed % 4));
}

void NormalDistribution::setValue(double mean, double deviation) {
    _mean = mean;
    _deviation = deviation;
}

double NormalDistribution::random(RandomGenerator &srcRG) {
    double a, b, c;

    do {
        a = srcRG.next() * 2 - 1;
        b = srcRG.next() * 2 - 1;
        c = a * a + b * b;
    } while(c >= 1 || c == 0);

    c = sqrt(-2 * log(c) / c);

    return a * c * _deviation + _mean;
}
