#ifndef INTERPIC_H
#define INTERPIC_H
#include <QtCore>
#include "InParse.h"
class InterPic {

    unsigned char *m_pcPixelBuf;
    unsigned char *m_pcPalBuf;

    int m_iWidth;
    int m_iHeight;
    bool m_bIndex;

    AbstractInParser *m_ptInParser;
    FileOutParser *m_ptOutParser;
    ImageFilter *m_ptFilter;

public:
    InterPic(){}
    int process(const QString& inFile);
    int construct(const QString& fName);
    int parse();
    int output();
    ~InterPic();
private:
    int errDeal();



};

#endif // INTERPIC_H
