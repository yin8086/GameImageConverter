#ifndef RGB888BUFPARSER_H
#define RGB888BUFPARSER_H
#include "BufferParser.h"
class RGB888BufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
    void invParse(unsigned char *pSrc,
                  unsigned char *&rpDst,
                  int width,
                  int height);
};
#endif // RGB8888BUFPARSER_H
