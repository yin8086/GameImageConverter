#ifndef PNGIOPARSER_H
#define PNGIOPARSER_H
#include "IOParser.h"

class PNGIOParser: public AbstractIOParser {
public:
    virtual QString getPixels(uint8_t *&rpDst) ;
    virtual void setPixels(uint8_t *pSrc);
    virtual void parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString& mode);
    virtual void invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString&);
    virtual QString exportName(const QString& origName, QString& mode) const;
    virtual void fromIndexed(uint8_t *, uint8_t *){}
    virtual void fromMapped(uint8_t *, uint8_t *){}
    virtual void toIndexed(uint8_t *&, uint8_t *){}
    virtual void toMapped(uint8_t *, uint8_t *){}
};
#endif // PNGIOPARSER_H
