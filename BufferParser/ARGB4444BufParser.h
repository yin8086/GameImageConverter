#ifndef ARGB4444BUFPARSER_H
#define ARGB4444BUFPARSER_H
#include "BufferParser.h"
class ARGB4444BufParser: public AbstractBufferParser {
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
#endif // ARGB4444BUFPARSER_H
