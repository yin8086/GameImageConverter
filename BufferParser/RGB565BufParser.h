#ifndef RGB565BUFPARSER_H
#define RGB565BUFPARSER_H
#include "BufferParser.h"
class RGB565BufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
};
#endif // RGB565BUFPARSER_H
