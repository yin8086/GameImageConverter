#ifndef DXTBUFPARSER_H
#define DXTBUFPARSER_H
#include <QtCore>
#include "BufferParser.h"
class DXTBufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);



};
#endif // DXTBUFPARSER_H
