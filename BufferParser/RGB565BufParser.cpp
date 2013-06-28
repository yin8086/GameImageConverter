#include <QtCore>
#include <QString>
#include "RGB565BufParser.h"


QString RGB565BufParser::parse(const unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        quint16 tmpData=*(quint16 *)(pSrc + i);
        pDst[j]     = ( (tmpData & 0x1f) * 255 + 15) / 31; //b
        pDst[j + 1]   = ( ( (tmpData & 0x7e0) >> 5) * 255 + 31) / 63; //g
        pDst[j + 2]   = ( ( (tmpData & 0xf800) >> 11) * 255 + 15) / 31; //r
        pDst[j + 3]   = 0xff; //a
    }
    return "RGB565";
}

void RGB565BufParser::invParse(const unsigned char *pSrc, unsigned char *&rpDst, int width, int height) {
    quint16 pixelVal = 0;
    quint16 r,g,b;
    rpDst = new unsigned char [(width * height) << 1];
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        r = (pSrc[j+2]   * (31*2) + 255) / (255*2);
        g = (pSrc[j+1] * 63 + 127) / 255;
        b = (pSrc[j]  * 31 + 127) / 255;
        pixelVal = (r << 11) | (g <<  5) | b;
        *(quint16*)(rpDst+i) = pixelVal;
    }

}
