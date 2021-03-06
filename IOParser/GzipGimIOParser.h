#ifndef GZIPGIMIOPARSER_H
#define GZIPGIMIOPARSER_H
#include "IOParser.h"

struct ChunkDesc {
    uint32_t start;
    uint32_t end;
    uint32_t decomLen;
};

class GzipGimIOParser: public AbstractIOParser {
public:
    GzipGimIOParser();
    virtual QString getPixels(uint8_t *&rpDst) ;
    virtual void setPixels(uint8_t *pSrc);
    virtual void parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString&);
    virtual void invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString&);
    virtual QString exportName(const QString& origName, QString& mode) const;
    virtual void fromIndexed(uint8_t *&rpDst, uint8_t *pSrc);
    virtual void fromMapped(uint8_t *pDst, uint8_t *pSrc);
    virtual void toIndexed(uint8_t *&rpDst, uint8_t *pSrc);
    virtual void toMapped(uint8_t *pDst, uint8_t *pSrc);
private:
    void GzipUncomp(const uint8_t *inBuf, uint32_t inSize, uint8_t *&outBuf, uint32_t *pSize);
};
#endif // GZIPGIMIOPARSER_H
