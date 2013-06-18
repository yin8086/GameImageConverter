#include <QtCore>
#include <QImage>
#include "PNGInParser.h"
#include "BaseDef.h"
QString PNGInParser::getPixels(unsigned char *&rpDst) {
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

void PNGInParser::parsePixels(unsigned char *, unsigned char*, const QString&) {
}

void PNGInParser::getPals(unsigned char *&) {

}
