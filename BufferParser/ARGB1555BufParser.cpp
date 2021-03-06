#include <QtCore>
#include <QString>
#include "BaseDef.h"
#include "ARGB1555BufParser.h"


QString ARGB1555BufParser::parse(const uint8_t *pSrc, uint8_t *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        uint16_t tmpData=*(uint16_t *)(pSrc + i);
        pDst[j]     = ( (tmpData & 0x1f) * 255 + 15) / 31; //b
        pDst[j + 1]   = ( ( (tmpData & 0x3e0) >> 5) * 255 + 15) / 31; //g
        pDst[j + 2]   = ( ( (tmpData & 0x7c00) >> 10) * 255 + 15) / 31; //r
        pDst[j + 3]   = (tmpData >> 15) * 0xff; //a
    }
    return "ARGB1555";
}

void ARGB1555BufParser::invParse(const uint8_t *pSrc, uint8_t *&rpDst, int width, int height) {
    uint16_t pixelVal = 0;
    uint16_t r,g,b,a;
    rpDst = new uint8_t [(width * height) << 1];
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        r = (pSrc[j+2]   * 31 + 127) / 255;
        g = (pSrc[j+1] * 31 + 127) / 255;
        b = (pSrc[j]  * 31 + 127) / 255;
        a = (pSrc[j+3]/0xff);
        pixelVal=(a<<15)|(r<<10)|(g<<5)|b;
        *(uint16_t*)(rpDst+i) = pixelVal;
    }

}
