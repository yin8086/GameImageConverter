#include<QtCore>
#include<QImage>
#include "BaseDef.h"
#include "PNGIOParser.h"



void PNGIOParser::invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString&) {
    if(m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else {
        rpDst = new uint8_t[m_iWidth*m_iHeight*4];
        memcpy(rpDst, pSrc, sizeof(char) * m_iWidth * m_iHeight * 4);
        m_iState = SUCC_STATUS;
    }
}
void PNGIOParser::setPixels(uint8_t *pSrc) {
    if(m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else {
        QImage im(pSrc, m_iWidth, m_iHeight, QImage::Format_ARGB32);
        im.save(&m_ptOrigF, "PNG");
        m_iState = SUCC_STATUS;
    }
}

QString PNGIOParser::getPixels(uint8_t *&rpDst) {
    if(m_iState != SUCC_STATUS)
        return "";
    QImage im;
    im.load(&m_ptOrigF, "PNG");
    if(!im.isNull()) {
        if(im.format() != QImage::Format_ARGB32)
            im = im.convertToFormat(QImage::Format_ARGB32);
        m_iWidth = im.width();
        m_iHeight = im.height();
        rpDst = new uint8_t [m_iWidth * m_iHeight * 4];
        memcpy(rpDst, im.bits(), m_iWidth * m_iHeight * 4);
        m_iState = SUCC_STATUS;

    }
    else
        m_iState = ERR_NOT_EXIST;
    return "";
}

void PNGIOParser::parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString &mode) {
    if(m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else
        memcpy(pDst, pSrc, m_iWidth*m_iHeight*4);
}

void PNGIOParser::getPals(uint8_t *&) {

}

QString PNGIOParser::exportName(const QString &origName, QString &mode) const {
    return QObject::tr("%1.%2.png").arg(origName).arg(mode);
}


void PNGIOParser::parsePals(uint8_t *&,
                                 uint8_t *,
                                 uint8_t *,
                                 const QString& ) {

}
