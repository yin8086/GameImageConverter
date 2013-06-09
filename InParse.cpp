#include <QtCore>
#include <QFile>
#include "InParse.h"
#include "InterPic.h"


AbstractInParser::~AbstractInParser(){
    if(m_ptOrigF.isOpen())
        m_ptOrigF.close();
}

InterPic* AbstractInParser::createInterPic(const QString& fName) {
    m_ptOrigF.setFileName(fName);
    m_iState = 0;
    if(m_ptOrigF.open(QIODevice::ReadOnly)) {
        uchar *pixelTab = NULL, *palTab = NULL;
        QString type = getPixels(pixelTab);
        getPals(palTab);
        uchar *tarTab = new uchar[m_iWidth * m_iHeight];
        parsePixels(pixelTab, tarTab, type);
        delete pixelTab;
        return new InterPic(m_iWidth, m_iHeight, tarTab, palTab);
    }
    else
        return NULL;
}


