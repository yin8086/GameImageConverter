#include<QtCore>
#include<QImage>
#include "PNGIOParser.h"
#include "BaseDef.h"


void PNGIOParser::invParsePixels(unsigned char *pSrc, unsigned char *&rpDst, const QString &mode) {
    return;
}
void PNGIOParser::setPixels(unsigned char *pSrc) {
    QImage im(pSrc, m_iWidth, m_iHeight, QImage::Format_ARGB32);
    im.save(m_ptOrigF.fileName());
    m_iState = SUCC_STATUS;
}

QString PNGIOParser::getPixels(unsigned char *&rpDst) {
    QImage im;
    im.load(&m_ptOrigF, "PNG");
    if(!im.isNull()) {
        if(im.format() != QImage::Format_ARGB32)
            im = im.convertToFormat(QImage::Format_ARGB32);
        m_iWidth = im.width();
        m_iHeight = im.height();
        rpDst = im.bits();
        m_iState = SUCC_STATUS;
    }
    else
        m_iState = ERR_NOT_EXIST;
    return "";
}

void PNGIOParser::parsePixels(unsigned char *, unsigned char*, const QString&) {
}

void PNGIOParser::getPals(unsigned char *&) {

}
