#ifndef INTERPIC_H
#define INTERPIC_H
#include <QtCore>
class InterPic {

    unsigned char *m_pcPixelBuf;
    unsigned char *m_pcPalBuf;

    int m_iWidth;
    int m_iHeight;
    bool m_bIndex;

    FileInParser *m_ptInParser;
    FileOutParser *m_ptOutParser;
    ImageFilter *m_ptFilter;

public:
    InterPic(int w, int h, uchar *pix, uchar *pal);
    int process(const QString& inFile);
    ~InterPic();

private:


};

#endif // INTERPIC_H
