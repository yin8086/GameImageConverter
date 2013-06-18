#include <QtCore>
#include "InterPic.h"
#include "BaseDef.h"

int InterPic::errDeal() {
    m_ptInParser->closeFile();
    return m_ptInParser->state();
}

int InterPic::construct(const QString &fName) {
    m_ptInParser->openFile(fName);
    uchar* tmpBuf = NULL;
    QString mode = m_ptInParser->getPixels(tmpBuf);
    m_ptInParser->getPals(m_pcPalBuf);
    m_ptInParser->parsePixels(tmpBuf, m_pcPixelBuf, mode);
    m_ptInParser->getWH(m_iWidth, m_iHeight);

    if(!m_pcPalBuf)
        m_bIndex = false;
    else
        m_bIndex = true;
    return errDeal();
}

int parse();
int output();

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


