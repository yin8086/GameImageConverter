#include <QtCore>
#include "squish.h"
#include "DXTBufParser.h"

QString DXTBufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {

    squish::DecompressImage(pDst, width, height, pSrc, squish::kDxt5);
    quint8 tmpVal;
    for(int i = 0; i < width*height*4; i+=4) {
        tmpVal = pDst[i];
        pDst[i] = pDst[i+2];
        pDst[i+2] = tmpVal;
    }

    return "DXT5";
}



