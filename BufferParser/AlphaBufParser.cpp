#include <QtCore>
#include <QString>
#include "BaseDef.h"
#include "AlphaBufParser.h"


QString AlphaBufParser::parse(const uint8_t *pSrc, uint8_t *pDst, int width, int height) {
    for(int i = 0, j = 0; i < width * height; i++, j += 4) {
        pDst[j] = 0;
        pDst[j + 1] = 0;
        pDst[j + 2] = 0;
        pDst[j + 3] = pSrc[i];
    }
    return "ALPHA8";
}

void AlphaBufParser::invParse(const uint8_t *pSrc,
                              uint8_t *&rpDst,
                              int width, int height) {
    rpDst = new uint8_t [width*height];
    for(int i = 0, j = 0; i < width * height; i++, j += 4) {
        rpDst[i] = pSrc[j+3];
    }

}
