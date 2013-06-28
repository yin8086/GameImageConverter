#ifndef IOPARSER_H
#define IOPARSER_H
#include <QtCore>
class AbstractIOParser {
protected:
    QFile m_ptOrigF;
    int m_iWidth;
    int m_iHeight;
    int m_iState;
public:
    AbstractIOParser();
    void openFile(const QString& fName);
    void closeFile();
    int state();
    void getWH(int &width, int &height) const;
    void setWH(int width, int height)
    {m_iHeight = height; m_iWidth = width;}
    QString toARGB32(unsigned char *&rpDst);
    void fromARGB32(unsigned char *pSrc, const QString& mode);

    virtual QString getPixels(unsigned char *&rpDst) = 0;
    virtual void setPixels(unsigned char *pSrc) = 0;
    virtual void parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString& mode) = 0;
    virtual void invParsePixels(unsigned char *pSrc, unsigned char *&rpDst, const QString& mode) = 0;

    virtual QString exportName(const QString& origName, QString& mode) const = 0;
    virtual void getPals(unsigned char *&rpDst) = 0;
    virtual ~AbstractIOParser(){}
};
#endif // IOPARSER_H
