#ifndef DXTBUFPARSER_H
#define DXTBUFPARSER_H
#include <QtCore>
#include "BufferParser.h"
class DXTBufParser: public AbstractBufferParser {
public:
    QString parse(const unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
    void invParse(const unsigned char *pSrc,
                  unsigned char *&rpDst,
                  int width,
                  int height);

};
#endif // DXTBUFPARSER_H
