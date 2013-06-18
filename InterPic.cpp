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
    m_sMode = m_ptInParser->getPixels(tmpBuf);
    m_ptInParser->getPals(m_pcPalBuf);
    m_ptInParser->parsePixels(tmpBuf, m_pcPixelBuf, m_sMode);
    m_ptInParser->getWH(m_iWidth, m_iHeight);

    if(!m_pcPalBuf)
        m_bIndex = false;
    else
        m_bIndex = true;
    return errDeal();
}

int InterPic::filter() {
    uchar* tarBuf = NULL;
    return m_ptFilter->filter(tarBuf, m_pcPixelBuf, m_iWidth, m_iHeight);
}

int InterPic::output(const QString& fName) {
    return m_ptOutParser->write(fName + m_sMode + ".png", m_pcPixelBuf, m_iWidth, m_iHeight);
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


