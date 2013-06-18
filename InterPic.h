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

    int m_iState;

    AbstractInParser *m_ptInParser;
    AbstractOutParser *m_ptOutParser;
    AbstractImageFilter *m_ptFilter;

public:
    InterPic():m_pcPixelBuf(NULL), m_pcPalBuf(NULL),
        m_iWidth(-1), m_iHeight(-1), m_bIndex(false),
        m_iState(0){}

    void setInParser(AbstractInParser *rhs) {m_ptInParser = rhs;}
    void setFilter(AbstractImageFilter *rhs) {m_ptFilter = rhs;}
    void setOutParser(AbstractOutParser *rhs) {m_ptOutParser =rhs;}
    void construct(const QString& fName);
    void filter();
    void output(const QString& fName);
    int state() const {return m_iState;}
    ~InterPic();
};

#endif // INTERPIC_H
