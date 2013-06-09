#include <QtCore>
#include <QString>
#include "ARGB8888BufParser.h"


QString ARGB8888BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 2; i += 4, j += 4) {
        pDst[j]     = pSrc[i + 3]; //b
        pDst[j + 1]   = pSrc[i + 2]; //g
        pDst[j + 2]   = pSrc[i + 1]; //r
        pDst[j + 3]   = pSrc[i]; //a
    }
    return "ARGB8888";
}
