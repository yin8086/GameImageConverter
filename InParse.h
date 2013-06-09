#ifndef INPARSE_H
#define INPARSE_H
#include <QtCore>
#include "InterPic.h"
class AbstractInParser {
protected:
    QFile m_ptOrigF;
    int m_iWidth;
    int m_iHeight;
    int m_iState;
public:
    int openFile(const QString& fName);
    int closeFile();
    int state();
    void getWH(int &width, int &height);
    virtual QString getPixels(unsigned char *&rpDst) = 0;
    virtual int parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString& mode) = 0;
    virtual int getPals(unsigned char *&rpDst) = 0;
};


#endif // INPARSE_H
