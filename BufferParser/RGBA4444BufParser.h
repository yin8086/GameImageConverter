#ifndef RGBA4444BUFPARSER_H
#define RGBA4444BUFPARSER_H
#include "BufferParser.h"
class RGBA4444BufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
    void invParse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
};
#endif // RGBA4444BUFPARSER_H
