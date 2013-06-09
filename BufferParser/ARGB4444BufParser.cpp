#include <QtCore>
#include <QString>
#include "ARGB4444BufParser.h"


QString ARGB4444BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 1; i += 2, j += 4) {
        quint16 tmpData=*(quint16 *)(pSrc + i);        
        pDst[j]   = ( (tmpData & 0xf) * 255 + 7) / 15; //b
        pDst[j+1]     = ( ( (tmpData & 0xf0) >> 4) * 255 + 7) / 15; //g
        pDst[j+2]   = ( ( (tmpData & 0xf00) >> 8) * 255 + 7) / 15; //r
        pDst[j+3]   = ( ( (tmpData & 0xf000) >> 12) * 255 + 7) / 15; //a
    }
    return "ARGB4444";
}

