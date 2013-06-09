#include <QtCore>
#include <QString>
#include "ARGB1555BufParser.h"


QString ARGB1555BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        quint16 tmpData=*(quint16 *)(pSrc + i);
        pDst[j]     = ( (tmpData & 0x1f) * 255 + 15) / 31; //b
        pDst[j + 1]   = ( ( (tmpData & 0x3e0) >> 5) * 255 + 15) / 31; //g
        pDst[j + 2]   = ( ( (tmpData & 0x7c00) >> 10) * 255 + 15) / 31; //r
        pDst[j + 3]   = (tmpData >> 15) * 0xff; //a
    }
    return "ARGB1555";
}

