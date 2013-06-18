#ifndef PNGOUTPARSER_H
#define PNGOUTPARSER_H
#include "OutParser.h"

class PNGOutParser: public AbstractOutParser {
public:
    int write(const QString &fName, uchar* pSrc, int width, int height);
};

#endif // PNGOUTPARSER_H
