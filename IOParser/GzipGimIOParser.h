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
    virtual QString getPixels(uint8_t *&rpDst) ;
    virtual void setPixels(uint8_t *pSrc);
    virtual void parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString&);
    virtual void invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString&);

    virtual void parsePals(uint8_t *&rpDst,
                           uint8_t *pSrc,
                           uint8_t *pPal,
                           const QString& );
    virtual QString exportName(const QString& origName, QString& mode) const;
    virtual void getPals(uint8_t *&rpDst);
private:
    void GzipUncomp(const uint8_t *inBuf, uint8_t *&outBuf, uint32_t *pSize);
};
#endif // GZIPGIMIOPARSER_H
