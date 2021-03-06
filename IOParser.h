#ifndef IOPARSER_H
#define IOPARSER_H
class AbstractIOParser {
protected:
    QFile m_ptOrigF;
    int m_iWidth;
    int m_iHeight;
    int m_iState;
    bool m_bIndexed;
    bool m_bMapped;
public:
    AbstractIOParser();
    void openFile(const QString& fName);
    void closeFile();
    void reset();
    int state();
    void getWH(int &width, int &height) const;
    void setWH(int width, int height)
    {m_iHeight = height; m_iWidth = width;}

    QString toARGB32(uint8_t *&rpDst);
    void fromARGB32(uint8_t *pSrc, const QString& mode);

    virtual QString getPixels(uint8_t *&rpDst) = 0;
    virtual void setPixels(uint8_t *pSrc) = 0;
    virtual void parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString& mode) = 0;
    virtual void invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString& mode) = 0;
    virtual QString exportName(const QString& origName, QString& mode) const = 0;
    virtual void fromIndexed(uint8_t *&rpDst, uint8_t *pSrc) = 0;
    virtual void fromMapped(uint8_t *pDst, uint8_t *pSrc) = 0;
    virtual void toIndexed(uint8_t *&rpDst, uint8_t *pSrc) = 0;
    virtual void toMapped(uint8_t *pDst, uint8_t *pSrc) = 0;
    virtual ~AbstractIOParser(){}
};
#endif // IOPARSER_H
