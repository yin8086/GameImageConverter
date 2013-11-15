#ifndef INTERPIC_H
#define INTERPIC_H
#include "BaseDef.h"
#include "IOParser.h"
class InterPic {

    uint8_t *m_pcPixelBuf;
    //uint8_t *m_pcPalBuf;

    int m_iWidth;
    int m_iHeight;
    //bool m_bIndex;
    QString m_sMode;

    int m_iState;

    AbstractIOParser *m_ptInParser;
    AbstractIOParser *m_ptOutParser;

public:
    InterPic():m_pcPixelBuf(NULL), /*m_pcPalBuf(0),*/
        m_iWidth(-1), m_iHeight(-1), /*m_bIndex(false),*/
        m_iState(0){}

    void setInParser(AbstractIOParser *rhs) {m_ptInParser = rhs;}
    void setOutParser(AbstractIOParser *rhs) {m_ptOutParser =rhs;}
    void construct(const QString& fName);
    void output(const QString& fName);
    int state() const {return m_iState;}
    ~InterPic();
};

#endif // INTERPIC_H
