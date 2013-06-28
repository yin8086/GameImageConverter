#include <QtCore>
#include <QString>
#include "RGBA8888BufParser.h"


QString RGBA8888BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 2; i += 4, j += 4) {
        pDst[j]     = pSrc[i+2]; //b
        pDst[j+1]   = pSrc[i+1]; //g
        pDst[j+2]   = pSrc[i]; //r
        pDst[j+3]   = pSrc[i+3]; //a
    }
    return "RGBA8888";
}


void RGBA8888BufParser::invParse(unsigned char *pSrc, unsigned char *&rpDst, int width, int height) {
    rpDst = new unsigned char [(width * height) << 2];
    for(int i = 0, j = 0; i < (width * height) << 2; i += 4, j += 4) {
        rpDst[i]     = pSrc[j+2];
        rpDst[i+1]   = pSrc[j+1];
        rpDst[i+2]   = pSrc[j];
        rpDst[i+3]   = pSrc[j+3];
    }
}
