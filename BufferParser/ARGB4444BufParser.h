#ifndef ARGB4444BUFPARSER_H
#define ARGB4444BUFPARSER_H
#include "BufferParser.h"
class ARGB4444BufParser: public AbstractBufferParser {
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
#endif // ARGB4444BUFPARSER_H
