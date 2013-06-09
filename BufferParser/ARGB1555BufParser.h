#ifndef ARGB1555BUFPARSER_H
#define ARGB1555BUFPARSER_H
#include "BufferParser.h"
class ARGB1555BufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);
};

#endif // ARGB1555BUFPARSER_H
