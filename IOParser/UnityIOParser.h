#ifndef UNITYIOPARSER_H
#define UNITYIOPARSER_H
#include "IOParser.h"
#include "BufParFactory.h"
#include "BufferParser.h"

class UnityIOParser: public AbstractIOParser {
    AbstractBufParseFactory *m_ptBufFac;
    AbstractBufferParser *m_ptParser;
    int m_iDefault16bpp;
    uint8_t *m_ptOriBuf;

    static uint32_t getImageSize(uint32_t width, uint32_t height, uint32_t pixelType);

    qint64 getDataOffset(qint64 header_end_pos, uint32_t imageDataSize);
    QString getImageTypeStr(uint32_t pixelType);
public:
    UnityIOParser();

    virtual QString getPixels(uint8_t *&rpDst);
    virtual void setPixels(uint8_t *pSrc);
    virtual void parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString& mode);
    virtual void invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString& mode);
    virtual QString exportName(const QString& origName, QString& mode) const;
    virtual void fromIndexed(uint8_t *&, uint8_t *){}
    virtual void fromMapped(uint8_t *pDst, uint8_t *pSrc);
    virtual void toIndexed(uint8_t *&, uint8_t *){}
    virtual void toMapped(uint8_t *pDst, uint8_t *pSrc);
    ~UnityIOParser();
};
#endif // UNITYIOPARSER_H
