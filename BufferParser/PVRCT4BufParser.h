#ifndef PVRCT4BUFPARSER_H
#define PVRCT4BUFPARSER_H
#include "BufferParser.h"
class PVRCT4BufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
};
#endif // PVRCT4BUFPARSER_H
