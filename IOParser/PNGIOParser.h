#ifndef PNGIOPARSER_H
#define PNGIOPARSER_H
#include "IOParser.h"

class PNGIOParser: public AbstractIOParser {
public:
    virtual QString getPixels(unsigned char *&rpDst) ;
    virtual void setPixels(unsigned char *pSrc);
    virtual void parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString& mode);
    virtual void invParsePixels(unsigned char *pSrc, unsigned char *&rpDst, const QString& mode);

    virtual void getPals(unsigned char *&rpDst);
};
#endif // PNGIOPARSER_H
