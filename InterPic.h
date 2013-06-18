#ifndef INTERPIC_H
#define INTERPIC_H
#include <QtCore>
#include "InParse.h"
#include "AbstractFilter.h"
#include "OutParser.h"
class InterPic {

    unsigned char *m_pcPixelBuf;
    unsigned char *m_pcPalBuf;

    int m_iWidth;
    int m_iHeight;
    bool m_bIndex;
    QString m_sMode;

    AbstractInParser *m_ptInParser;
    AbstractOutParser *m_ptOutParser;
    AbstractImageFilter *m_ptFilter;

public:
    InterPic(){}

    void setInParser(AbstractInParser *rhs) {m_ptInParser = rhs;}
    void setFilter(AbstractImageFilter *rhs) {m_ptFilter = rhs;}
    void setOutParser(AbstractOutParser *rhs) {m_ptOutParser =rhs;}
    int construct(const QString& fName);
    int filter();
    int output(const QString& fName);
    ~InterPic();
private:
    int errDeal();
};

#endif // INTERPIC_H
