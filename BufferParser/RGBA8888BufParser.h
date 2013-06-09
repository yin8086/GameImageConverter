#ifndef RGBA8888BUFPARSER_H
#define RGBA8888BUFPARSER_H
#include "BufferParser.h"
class RGBA8888BufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
};
#endif // RGBA8888BUFPARSER_H
