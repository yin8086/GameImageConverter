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
    virtual QString getPixels(unsigned char *&rpDst) ;
    virtual void setPixels(unsigned char *pSrc);
    virtual void parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString&);
    virtual void invParsePixels(unsigned char *pSrc, unsigned char *&rpDst, const QString&);

    virtual void parsePals(unsigned char *&rpDst,
                           unsigned char *pSrc,
                           unsigned char *pPal,
                           const QString& );
    virtual QString exportName(const QString& origName, QString& mode) const;
    virtual void getPals(unsigned char *&rpDst);
private:
    void GzipUncomp(const char *inBuf, char* &outBuf, uint32_t *pSize);
};
#endif // GZIPGIMIOPARSER_H
