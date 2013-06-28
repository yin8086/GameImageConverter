#ifndef ALPHABUFPARSER_H
#define ALPHABUFPARSER_H
#include "BufferParser.h"
class AlphaBufParser: public AbstractBufferParser {
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

#endif // ALPHABUFPARSER_H
