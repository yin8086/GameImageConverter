#include<QtCore>
#include<QImage>
#include "PNGOutParser.h"
#include "BaseDef.h"

int PNGOutParser::write(const QString &fName, uchar* pSrc, int width, int height) {
    QImage im(pSrc, width, height, QImage::Format_ARGB32);
    im.save(fName);
    return SUCC_STATUS;
}
