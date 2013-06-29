#ifndef DXT1BUFPARSER_H
#define DXT1BUFPARSER_H
#include <QtCore>
#include "BufferParser.h"
class DXT1BufParser: public AbstractBufferParser {
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
#endif // DXT1BUFPARSER_H
