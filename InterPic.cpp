#include <QtCore>
#include "InterPic.h"

InterPic::InterPic(int w, int h, uchar *pix, uchar *pal)
    :m_iWidth(w), m_iHeight(h), m_pcPixelBuf(pix), m_pcPalBuf(pal) {
    if(m_pcPalBuf == NULL)
        m_bIndex = false;
    else
        m_bIndex = true;
}

int InterPic::process(const QString& inFile) {

}

InterPic::~InterPic() {
    if(!m_pcPalBuf) {
        delete [] m_pcPalBuf;
        m_pcPalBuf = NULL;
    }
    if(!m_pcPixelBuf) {
        delete [] m_pcPixelBuf;
        m_pcPixelBuf = NULL;
    }
}


