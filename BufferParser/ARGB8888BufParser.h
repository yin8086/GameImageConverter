#ifndef ARGB8888BUFPARSER_H
#define ARGB8888BUFPARSER_H
#include "BufferParser.h"
class ARGB8888BufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
//    void invParse(unsigned char *pSrc,
//                  unsigned char *pDst,
//                  int width,
//                  int height,
//                  const QString& mode);
};
#endif // ARGB8888BUFPARSER_H
