#include <QtCore>
#include "InterPic.h"
#include "BaseDef.h"


void InterPic::construct(const QString &fName) {
    m_ptInParser->openFile(fName);

    m_sMode = m_ptInParser->toARGB32(m_pcPixelBuf);
    m_ptInParser->getPals(m_pcPalBuf);
    m_ptInParser->getWH(m_iWidth, m_iHeight);

    if(!m_pcPalBuf)
        m_bIndex = false;
    else
        m_bIndex = true;

    m_ptInParser->closeFile();
    m_iState = m_ptInParser->state();
}

void InterPic::filter() {
    if(m_iState != SUCC_STATUS)
        return;
    uchar* tarBuf = NULL;
    m_iState = m_ptFilter->filter(tarBuf, m_pcPixelBuf, m_iWidth, m_iHeight);
}

void InterPic::output(const QString& fName) {
    if(m_iState != SUCC_STATUS)
        return;
    QString newName = m_ptOutParser->exportName(fName, m_sMode);
    m_ptOutParser->openFile(newName);
    m_ptOutParser->setWH(m_iWidth, m_iHeight);
    m_ptOutParser->fromARGB32(m_pcPixelBuf, m_sMode.toUpper());
    m_ptOutParser->closeFile();
    m_iState = m_ptOutParser->state();
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


