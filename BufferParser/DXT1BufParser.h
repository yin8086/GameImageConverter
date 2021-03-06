#ifndef DXT1BUFPARSER_H
#define DXT1BUFPARSER_H
#include "BufferParser.h"
class DXT1BufParser: public AbstractBufferParser {
public:
    QString parse(const uint8_t *pSrc,
                  uint8_t *pDst,
                  int width,
                  int height);
    void invParse(const uint8_t *pSrc,
                  uint8_t *&rpDst,
                  int width,
                  int height);

};
#endif // DXT1BUFPARSER_H
