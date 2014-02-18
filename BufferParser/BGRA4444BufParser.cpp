#include <QtCore>
#include <QString>
#include "BaseDef.h"
#include "BGRA4444BufParser.h"


QString BGRA4444BufParser::parse(const uint8_t *pSrc, uint8_t *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        uint16_t tmpData=*(uint16_t *)(pSrc + i);
        pDst[j]   = ( (tmpData & 0xf) * 255 + 7) / 15; //b
        pDst[j+1]     = ( ( (tmpData & 0xf0) >> 4) * 255 + 7) / 15; //g
        pDst[j+2]   = ( ( (tmpData & 0xf00) >> 8) * 255 + 7) / 15; //r
        pDst[j+3]   = ( ( (tmpData & 0xf000) >> 12) * 255 + 7) / 15; //a
    }
    return "ARGB4444";
}

void BGRA4444BufParser::invParse(const uint8_t *pSrc, uint8_t *&rpDst, int width, int height) {
    uint16_t pixelVal = 0;
    uint16_t r,g,b,a;
    rpDst = new uint8_t [(width * height) << 1];
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        r = (pSrc[j+2]   * 15 + 127) / 255;
        g = (pSrc[j+1] * 15 + 127) / 255;
        b = (pSrc[j]  * 15 + 127) / 255;
        a = (pSrc[j+3] * 15 + 127) / 255;
        pixelVal = (a << 12) | (r << 8) | (g << 4) | b;
        *(uint16_t*)(rpDst+i) = pixelVal;
    }

}
