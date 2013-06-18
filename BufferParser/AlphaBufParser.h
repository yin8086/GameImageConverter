#ifndef ALPHABUFPARSER_H
#define ALPHABUFPARSER_H
#include "BufferParser.h"
class AlphaBufParser: public AbstractBufferParser {
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

#endif // ALPHABUFPARSER_H
